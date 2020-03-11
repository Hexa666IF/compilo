#include "IR.h"

using namespace std;

// ========================= IRInstr =========================================

// ====== IRInstr class related stuff ======

// === Constructor ===

IRInstr::IRInstr(BasicBlock * bb) : bb(bb)
{

}

IRInstr::~IRInstr()
{

}


// ====== IRInstr1op class related stuff ======

IRInstr1op::IRInstr1op(	BasicBlock * bb,
						Operation1op op,
						string a
					)
: IRInstr(bb), operation(op), arg(a)
{

}

IRInstr1op::~IRInstr1op()
{

}

void IRInstr1op::gen_asm(ostream &o) const
{
	static const string instructions [] = {"pushq", "popq"};
	o <<  instructions[operation] << " " << arg << endl;
}

// ====== IRInstr2op class related stuff ======

IRInstr2op::IRInstr2op(	BasicBlock * bb,
						Operation2op op,
						string a1,
						string a2
					)
: IRInstr(bb), operation(op), arg1(a1), arg2(a2)
{

}

void IRInstr2op::gen_asm(ostream &o) const
{
	static const string instructions [] = { "copy", "ldconst", "rmem", "wmem", "movq", "movl"};
	o << instructions[operation] << " " << arg1 << ", " << arg2 << endl;
}

// ====== IRInstr3op class related stuff ======

IRInstr3op::IRInstr3op(	BasicBlock * bb,
						Operation3op op,
						string a1,
						string a2,
						string a3
					)
: IRInstr(bb), operation(op), arg1(a1), arg2(a2), arg3(a3)
{

}

void IRInstr3op::gen_asm(ostream &o) const
{
	static const string instructions [] = { "add", "sub", "mul", "cmp_eq", "cmp_lt", "cmp_le"};
	o << instructions[operation] << " "  << arg1 << ", " << arg2 << ", " << arg3 << endl;
	// TODO : handle conditionnal jump ?
}

// ====== IRInstrSpecial class related stuff ======

IRInstrSpecial::IRInstrSpecial(	BasicBlock * bb,
								OperationSpe op,
								vector<string> av
							)
: IRInstr(bb), operation(op), args(av)
{

}

void IRInstrSpecial::gen_asm(ostream &o) const
{
	o << "call";
	for ( string arg : args )
	{
		o << ", " << arg;
	}
	o << endl;
}

// ============================= BasicBlock =================================

// === Constructor / Destructor  ===

BasicBlock::BasicBlock(CFG * c, string entry_label)
: exit_true(nullptr), exit_false(nullptr), label(entry_label), cfg(c)
{

}

// === public methods ===

void BasicBlock::gen_asm(ostream &o)
{
	o << ".global main" << endl
		<< "main:" << endl;
	for( IRInstr * instr : instrs )
	{
		instr->gen_asm(o);
	}

	o << "ret" << endl;
	// Don't forget to handle exit_true and exit_false modification !
}

/*
void BasicBlock::add_instr(IRInstr * instr)
{
	instrs.push_back(instr);
	// TODO : updates if the instruction is a conditionnal jump ?
}
*/

void BasicBlock::add_instr(IRInstr1op::Operation1op op, string arg)
{
	IRInstr1op * instr = new IRInstr1op(this, op, arg);
	instrs.push_back(instr);
}

void BasicBlock::add_instr(IRInstr2op::Operation2op op, string arg1, string arg2)
{
	IRInstr2op * instr = new IRInstr2op(this, op, arg1, arg2);
	instrs.push_back(instr);
}

void BasicBlock::add_instr(IRInstr3op::Operation3op op, string arg1, string arg2, string arg3)
{
	IRInstr3op * instr = new IRInstr3op(this, op, arg1, arg2, arg3);
	instrs.push_back(instr);
}

void BasicBlock::add_instr(IRInstrSpecial::OperationSpe op, vector<string> args)
{
	IRInstrSpecial * instr = new IRInstrSpecial(this, op, args);
	instrs.push_back(instr); 
}

string BasicBlock::getLabel() const
{
	return label;
}

// ================================ CFG =====================================

// === Constructor / Destructor ===

CFG::CFG(Ast * tree)
: ast(tree)
{
	current_bb = new BasicBlock(this, "main");
	bbs.push_back(current_bb);
	// TODO : complete the initialisation of other attributes !
}

// === public methods ===

void CFG::add_bb(BasicBlock * bb)
{
	bbs.push_back(bb);
	current_bb = bb;

	// not sure about this increment, but seems like the right thing to do with
	// it...
	++nextBBnumber;	
}

void CFG::add_instr(IRInstr1op::Operation1op op, string arg)
{
	current_bb->add_instr(op, arg);	
}

void CFG::add_instr(IRInstr2op::Operation2op op, string arg1, string arg2)
{
	current_bb->add_instr(op, arg1, arg2);
}

void CFG::add_instr(IRInstr3op::Operation3op op, string arg1, string arg2, string arg3)
{
	current_bb->add_instr(op, arg1, arg2, arg3);
}

void CFG::add_instr(IRInstrSpecial::OperationSpe op, vector<string> args)
{
	current_bb->add_instr(op, args);
}


void CFG::gen_asm(ostream& o)
{
	for(BasicBlock * b : bbs)
	{
		b->gen_asm(o);
	}
}

void CFG::gen_asm_prologue(ostream& o)
{
	// TODO : use IRInstr1op instead of printing hardcoded assembly code ?
	o << "pushq %rbp" << endl
	  << "movq %rsp, rbp" << endl;

	// TODO : allocate memory on the stack
}

void CFG::gen_asm_epilogue(ostream& o)
{
	// TODO : use IRInstr1op instead of printing hardcoded assembly code ?
	o << "popq %rbp" << endl
	  << "ret" << endl;
}
// = symbol table methods =

void CFG::add_to_symbol_table(string name)
{
	// TODO : handle multiple declaration errors.
	pair<string, int> p = make_pair(name, nextFreeSymbolIndex);
	SymbolIndex.insert(p);
	nextFreeSymbolIndex += 4;
}

string CFG::create_new_tempvar()
{
	// TODO : correctly handle declaration of an existant variable name but in a sub-block...
	string varName = "tmp" + to_string(nextFreeSymbolIndex);
	pair<string, int> p = make_pair(varName, nextFreeSymbolIndex);
	SymbolIndex.insert(p);
	nextFreeSymbolIndex += 4;

	return varName;
}

int CFG::get_var_index(string name)
{
	map<string, int>::iterator it = SymbolIndex.find(name);
	return it->second;
}

string CFG::new_BB_name() const
{
	return current_bb->getLabel();
}

