#include "IR.h"

using namespace std;

// ========================= IRInstr =========================================

// ====== IRInstr class related stuff ======

// === Constructor ===

IRInstr::IRInstr(BasicBlock * bb) : bb(bb)
{

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
	// TODO: implement code generation for IRInstr2op
	// o << "Ope" << " " << arg1 << ", " << arg2 << ", " << endl;
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
	// TODO: implement code generation for IRInstr3op
	// o << "Ope" << " "  << arg1 << ", " << arg2 << ", " << arg3 << ", " << endl;
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
	// TODO: implement code generation for IRInstrSpecial.
	// o << "Ope";
	// for ( string arg : args )
	// {
	// 		o << " " << arg;
	// }
	// o << endl;
}

// ============================= BasicBlock =================================

// === Constructor / Destructor  ===

BasicBlock::BasicBlock(CFG * c, string entry_label)
: exit_true(nullptr), exit_false(nullptr), label(entry_label), cfg(c)
{

}

void BasicBlock::gen_asm(ostream &o)
{
	// TODO: implement code generation for BasicBlock.
	// for( IRInstr * instr : instrs )
	// {
	// 		instr->gen_asm(o);
	// }
	//
	// Don't forget to handle exit_true and exit_false modification !
}

void BasicBlock::add_instr(IRInstr * instr)
{
	instrs.push_back(instr);
	// TODO : updates if the instruction is a conditionnal jump ?
}

// ================================ CFG =====================================

// === Constructor / Destructor ===

CFG::CFG(Ast * tree)
: ast(tree), current_bb(nullptr)
{
	// TODO : complete the initialisation of other attributes !
}

// === public methods ===

void CFG::add_instr(IRInstr * instr)
{
	current_bb->add_instr(instr);
}

// = symbol table methods =

void CFG::add_to_symbol_table(string name)
{
	pair<string, int> p = make_pair(name, nextFreeSymbolIndex);
	SymbolIndex.insert(p);
	++nextFreeSymbolIndex;
}

string CFG::create_new_tempvar()
{
	// TODO: is it what create_new_tempvar is supposed to do ?
	string varName = "tmp" + to_string(nextFreeSymbolIndex);
	pair<string, int> p = make_pair(varName, nextFreeSymbolIndex);
	SymbolIndex.insert(p);
	++nextFreeSymbolIndex;

	return varName;
}

int CFG::get_var_index(string name)
{
	map<string, int>::iterator it = SymbolIndex.find(name);
	return it->second;
}
