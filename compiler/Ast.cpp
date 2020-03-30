/*******************************************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
*******************************************************************************************/

#include "Ast.h"

using namespace std;


// ========================== Ast related stuff ================================
//------------- public methods -------------------------------------------------

// void Ast::gen_instr() const
// {
//	if(root->isValue == false)
//		gen_instr(root);
//	else
//		cfg->add_instr(IRInstr2op::ldconst, root->val, destination);	
// }

// string Ast::get_tmp_var()
// {
// 	string name;
// 	if(n_tmp_var == 0)
//	// n_tmp_var == 0 => we are creating the root calculation.
//	// So the destination of the root calculation must be the destination of
//	// the whole computation (stored into Ast::destination).
//	{
//		name = destination;
//	}
//	else 
//	{
//		name = "!tmp" + to_string(n_tmp_var);
//		cfg->add_to_symbol_table(name);
//	}
//	++n_tmp_var;
//	
//	return name;
// }

// void Ast::set_root(node_s * node)
// {
// 	root = node;
// }

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
	unordered_set<string>::const_iterator cit = unuseds.find(variable);
	if(cit != unuseds.cend())
		declared = true;
	
	return declared;
}

map<string, int> Ast::getSymbolIndex() const
{
	return symbolIndex;
}

//------------- Constructor - Destructor ------------------------------------

Ast::Ast()
: childs(), symbolIndex(), next_index(4)
{

}

Ast::~Ast()
{
	// uproot_node(root);	
}

//------------- protected methods -----------------------------------------------

// void Ast::gen_instr(node_s * node) const
// {
//	if(node->left->isValue == false)
//			gen_instr(node->left);
//
//	if(node->right->isValue == false)
//			gen_instr(node->right);
//
//	switch(node->op)
//	{
//			case IRInstr3op::add:
//				cfg->add_instr(	IRInstr3op::add, 
//								node->left->val, 
//								node->right->val, 
//								node->val);
//				break;
//			
//			case IRInstr3op::sub:
//				cfg->add_instr(	IRInstr3op::sub, 
//								node->left->val, 
//								node->right->val, 
//								node->val);
//				break;
//
//			case IRInstr3op::mul:
//				cfg->add_instr(	IRInstr3op::mul, 
//								node->left->val, 
//								node->right->val, 
//								node->val);
//				break;
//
//			default:
//				break;
//	}
// }

// ================= Node Related stuff ========================

// ----- Constructors - Destructor ------

Node::Node(Ast * ast)
: parentTree(ast)
{

}

// Node::~Node()
// {
// 	delete sub_nodes;
// }

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
}

// ----- public methods -----

string Variable::getValue() const
{
	parentTree->removeFromUnuseds(name);
	return name;
}

void Variable::gen_instr(CFG * cfg) const
{
	// TODO : find a way that doesn't use this blank function !
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
	
	cfg->add_instr(IRInstr2op::ldconst, retvalue->getValue(), "%retval");
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
