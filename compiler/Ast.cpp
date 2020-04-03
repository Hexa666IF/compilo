/*******************************************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
*******************************************************************************************/

#include "Ast.h"
#include "reg.h"

using namespace std;

// ================= Node Related stuff ========================

// ----- Constructors - Destructor ------

Node::Node(Ast * ast)
: parentTree(ast)
{

}

// ----- Public methods ------

void Node::setParent(Ast * ast)
{
	parentTree = ast;
}

// ================== RValue related stuff ========================

// Constructor

RValue::RValue(Ast * ast)
: Node(ast)
{

}

// Public Methods 

// ================== Constant related stuff ======================

// ----- Constructor -----

Constant::Constant(int val, Ast * ast)
: RValue(ast), value(val)
{

}

Constant::Constant(string val, Ast * ast)
: RValue(ast), value(atoi(val.c_str()))
{

}

// ----- public methods -----

string Constant::getValue() const
{
	return to_string(value);
}

void Constant::gen_instr(CFG * cfg) const
{
	// TODO : find a way that doesn't use this blank function !
}

// ================== Variable related stuff ======================

// ----- Constructor -----

Variable::Variable(string variable, Ast * ast)
: RValue(ast), name(variable)
{
	if(parentTree->isDeclared(name) == false)
	{
		Errors::addError(name, notDeclared);
		throw notDeclared;
	}
	else
	{
		parentTree->removeFromUnuseds(name);
	}
}

// ----- public methods -----

string Variable::getValue() const
{
	return name;
}

void Variable::gen_instr(CFG * cfg) const
{
	// TODO : find a way that doesn't use this blank function !
}


// ================== functionCall related stuff ======================

// ----- Constructor -----

FunctionCall::FunctionCall(string functionName, vector<RValue *> args, Ast * ast)
: RValue(ast), arguments(args), name(functionName)
{
	
}

// ----- public methods -----

string FunctionCall::getValue() const
{
	return RETVALD;
}

void FunctionCall::gen_instr(CFG * cfg) const
{
	vector<string> args;
	args.push_back(name);

	//TODO : faire une enum des %
	for(int i = 0; i < arguments.size() ; i++)
	{
		arguments[i]->gen_instr(cfg);
		string value = arguments[i]->getValue();
		args.push_back(value);
	}

	cfg->add_instr(IRInstrSpecial::call, args);
}

// ================== Operation related stuff =====================

// ----- Constructor - Destructor -----

Operation::Operation(	IRInstr3op::Operation3op op, 
						RValue * l, 
						RValue * r,
						Ast * ast
					)
: RValue(ast), left(l), right(r), operation(op), tmp_var(get_tmp_var())
{

}

Operation::~Operation()
{
	delete left;
	delete right;
}

// ----- public methods -----

string Operation::getValue() const
{
	return tmp_var;
}

string Operation::get_tmp_var()
{
	static unsigned int next_tmp = 0;
	return "!tmp" + to_string(next_tmp++);
}

void Operation::gen_instr(CFG * cfg) const
{
	// TODO: perform check to avoid calling functions that don't need to.
	left->gen_instr(cfg);
	right->gen_instr(cfg);

	cfg->add_to_symbol_table(tmp_var);
	cfg->add_instr(operation, left->getValue(), right->getValue(), tmp_var);
}

// ================== Return Related stuff ========================

// ----- Constructor -----

Return::Return(RValue * retval, Ast * ast)
: Node(ast), retvalue(retval)
{
	// TODO : perform checks.
}

// ----- public methods ------

void Return::gen_instr(CFG * cfg) const
{
	// TODO: perform check to avoid calling methods that doesn't need to.
	retvalue->gen_instr(cfg);
	
	cfg->add_instr(IRInstr2op::ldconst, retvalue->getValue(), RETVAL);
}

// ================== Assign related stuff ========================

// ----- Constructor -----

Assign::Assign(Variable * dest, RValue * rval, Ast * ast)
: Node(ast), lvalue(dest), rvalue(rval)
{

}
// ----- public methods -----
void Assign::gen_instr(CFG * cfg) const
{
	rvalue->gen_instr(cfg);
	cfg->add_instr(IRInstr2op::ldconst, rvalue->getValue(), lvalue->getValue());
}

// ================== Condition Related stuff =====================

// ----- Constructor -----

Condition::Condition(RValue * l, Comparison comp, RValue * r)
: left(l), right(r), comparison(comp)
{
	
}

// ----- public methods -----

void Condition::gen_instr(CFG * cfg) const
{
	string jLabel = BasicBlock::getNextLabel();
	switch(comparison)
	// Because of Assembly code instructions, few instructions generated here can
	// look like they're wrong. It is not the case.
	// Checking that a > b in assembly code is equivalent to : 
	// 		"Don't jump if a <= b"
	// This is why left and right are swapped sometimes, and why a "than" becomes
	// an "equal" and vice versa.
	{
		case gt:
			cfg->add_instr(	IRInstr3op::cmp_le, 
							left->getValue(), 
							right->getValue(),
							jLabel);
			break;

		case ge:
			cfg->add_instr(	IRInstr3op::cmp_lt,
							left->getValue(), 
							right->getValue(),
							jLabel);
			break;

		case lt:
			cfg->add_instr(	IRInstr3op::cmp_le, 
							right->getValue(), 
							left->getValue(),
							jLabel);
			break;

		case le:
			cfg->add_instr(	IRInstr3op::cmp_lt, 
							right->getValue(), 
							left->getValue(),
							jLabel);
			break;

		case eq:
			cfg->add_instr(	IRInstr3op::cmp_eq, 
							left->getValue(), 
							right->getValue(),
							jLabel);
			break;
	}
}

// ==================   If   related stuff   ========================

// ----- Constructor -----

If::If(Condition * c, vector<Node *> content)
: condition(c), sub_nodes(content)
{
	
}

// ----- public methods -----

void If::gen_instr(CFG * cfg) const
{
	// This bb is the place where the code inside the if will be placed.
	// It is important to create it before entering into the Condition,
	// Because of BasicBlock::getNextLabel().
	BasicBlock * ifBlock = new BasicBlock(cfg);
	
	condition->gen_instr(cfg);	
	
	cfg->add_bb(ifBlock);
	for(Node * node : sub_nodes)
		node->gen_instr(cfg);
	
	BasicBlock * nextBlock = new BasicBlock(cfg);
	cfg->add_bb(nextBlock);
}


// ========================== Ast related stuff ================================

//------------- public methods -------------------------------------------------

void Ast::addNode(Node * node)
{
	childs.push_back(node);	
}

void Ast::addSymbol(string symbol)
{
	if(symbolIndex.find(symbol) != symbolIndex.end())
	{
			Errors::addError(symbol, multipleDeclaration);
			throw multipleDeclaration;
	}

	pair<string, int> p = make_pair(symbol, next_index);
	symbolIndex.insert(p);
	next_index += 4;

	unuseds.insert(symbol);	
}

void Ast::gen_instr(CFG * cfg) const
{
	for(Node * node : childs)
	{
		node->gen_instr(cfg);
	}
}

void Ast::removeFromUnuseds(string variable)
{
	unordered_set<string>::iterator it = unuseds.find(variable);
	if(it != unuseds.end())
			unuseds.erase(it);
}

bool Ast::isDeclared(string variable) const
{
	bool declared = false;
	map<string, int>::const_iterator cit = symbolIndex.find(variable);
	if(cit != symbolIndex.cend())
		declared = true;
	
	return declared;
}

map<string, int> & Ast::getSymbolIndex()
{
	return symbolIndex;
}

int & Ast::getNextIndex()
{
	return next_index;
}

const unordered_set<string> & Ast::getUnuseds() const
{
	return unuseds;
}

//------------- Constructor - Destructor ------------------------------------

Ast::Ast()
: childs(), symbolIndex(), next_index(4)
{

}

Ast::~Ast()
{
	
}

//------------- protected methods -----------------------------------------------


