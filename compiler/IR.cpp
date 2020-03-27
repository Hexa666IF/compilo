#include "IR.h"
#include <algorithm>

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
// This class is not used anymore !

// IRInstr1op::IRInstr1op(	BasicBlock * bb,
// 						Operation1op op,
// 						string a
// 					)
// : IRInstr(bb), operation(op), arg(a)
// {
//
// }
//
// IRInstr1op::~IRInstr1op()
// {
//
// }
//
// void IRInstr1op::gen_asm(ostream &o) const
// {
// 	static const string instructions [] = {"pushq", "popq"};
// 	o <<  instructions[operation] << " " << arg << endl;
// }
//

// ====== IRInstr2op class related stuff ======

IRInstr2op::IRInstr2op(	BasicBlock * bb,
						Operation2op op,
						string a1,
						string a2
					)
: IRInstr(bb), operation(op), arg1(a1), arg2(a2)
{

}

void IRInstr2op::gen_asm(Asm &toasm) const
{
	// for now, only ldconst is implemented.
	toasm.ldconst(arg1, arg2);	
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

void IRInstr3op::gen_asm(Asm &toasm) const
{
	switch(operation)
	{
		case add:
				toasm.add(arg1, arg2, arg3);
				break;
		
		case sub:
				toasm.sub(arg1, arg2, arg3);
				break;

		case mul:
				toasm.mul(arg1, arg2, arg3);
				break;

		default:
				break;
	}	
}

// ====== IRInstrSpecial class related stuff ======

IRInstrSpecial::IRInstrSpecial(	BasicBlock * bb,
								OperationSpe op,
								vector<string> av
							)
: IRInstr(bb), operation(op), args(av)
{

}

void IRInstrSpecial::gen_asm(Asm &toasm) const
{
	// o << "call";
	// for ( string arg : args )
	// {
	// 	o << ", " << arg;
	// }
	// o << endl;
}

// ============================= BasicBlock =================================

// === Constructor / Destructor  ===

BasicBlock::BasicBlock(CFG * c, string entry_label)
: exit_true(nullptr), exit_false(nullptr), label(entry_label), cfg(c)
{

}

// === public methods ===

void BasicBlock::gen_asm(Asm &toasm)
{
	for( IRInstr * instr : instrs )
	{
		instr->gen_asm(toasm);
	}
}

/*
void BasicBlock::add_instr(IRInstr * instr)
{
	instrs.push_back(instr);
	// TODO : updates if the instruction is a conditionnal jump ?
}
*/

// Not used anymore.
// void BasicBlock::add_instr(IRInstr1op::Operation1op op, string arg)
// {
//	IRInstr1op * instr = new IRInstr1op(this, op, arg);
//	instrs.push_back(instr);
//}



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
: ast(tree), toasm(this, cout)
{
	current_bb = new BasicBlock(this, "main");
	bbs.push_back(current_bb);
	
	nextFreeSymbolIndex = 4;
	// TODO: check that nextBBnumber is correctly initialised.
	nextBBnumber = 0;
}

// === public methods ===

void CFG::add_bb(BasicBlock * bb)
{
	bbs.push_back(bb);
	current_bb = bb;

	// not sure about this increment, but seems like the right thing to do with
	// it...
	++nextBBnumber;	
	nextFreeSymbolIndex = 4;

	// TODO: handle if-blocks. (differents paths, same %rbp).
}

// Not used anymore.
// void CFG::add_instr(IRInstr1op::Operation1op op, string arg)
// {
// 	current_bb->add_instr(op, arg);	
// }

void CFG::add_instr(IRInstr2op::Operation2op op, string arg1, string arg2)
{
	// Test that arg1 is a variable
	if(isalpha(arg1[0]) != 0)
	{
		// Test if the variable arg1 is initialised
		if( !findVarInitialised(arg1) )
		{
			Errors::addError(arg1, notInitialised);
			throw notInitialised;
		}

		// The variable arg1 is now used
		deleteVarUsed(arg1);
	}

	// If the variable arg2 is not declared
	if( (arg2[0] != '%') && (get_var_index(arg2) == 0) )
	{
		Errors::addError(arg2, notDeclared);
		throw notDeclared;
	}
	else
	{
		//arg2 is now initialised
		addVarInitialised(arg2);
	}

	current_bb->add_instr(op, arg1, arg2);
}

void CFG::add_instr(IRInstr3op::Operation3op op, string arg1, string arg2, string arg3)
{
	// Performing statics checks.
	if(isalpha(arg1[0]) != 0)
		checkInit(arg1);

	if(isalpha(arg2[0]) != 0)
		checkInit(arg2);

	checkDeclared(arg3);		

	current_bb->add_instr(op, arg1, arg2, arg3);
}

void CFG::add_instr(IRInstrSpecial::OperationSpe op, vector<string> args)
{
	current_bb->add_instr(op, args);
}


void CFG::gen_asm()
{
	// TODO : do not use hardcoded string for globl() call.
	toasm.globl("main");
	toasm.gen_prologue(SymbolIndex.size()*4);
	for(BasicBlock * b : bbs)
	{
		b->gen_asm(toasm);
	}
	toasm.gen_epilogue();
}

// = symbol table methods =

string CFG::IR_reg_to_asm(std::string reg)
{
	string asm_reg;
	int index = get_var_index(reg);

	if(index != 0)
	{
		asm_reg = to_string(-index) + "(%rbp)";
	}
	else if (reg[0] == '%')
	{
		if(reg == "%retval")
				asm_reg = "%eax";

		if(reg == "%rbp")
				asm_reg = "%rbp";
	}
	else 
	{
		asm_reg = '$' + reg;
	}

	return asm_reg;
}

void CFG::add_to_symbol_table(string name)
{
	// handle multiple declaration errors.
	if (SymbolIndex.find(name) == SymbolIndex.end())
	{
		pair<string, int> p = make_pair(name, nextFreeSymbolIndex);
		SymbolIndex.insert(p);
		nextFreeSymbolIndex += 4;
		addVarUnused(name);
	}
	else
	{
		Errors::addError(name, multipleDeclaration);
		//arret du visiteur et retour dans le main
		throw multipleDeclaration;
	}
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
// TODO : get_var_index should be const.
{
	int index = 0;
	map<string, int>::iterator it = SymbolIndex.find(name);
	if(it != SymbolIndex.end())
			index = it->second;
	
	return index;
}

string CFG::new_BB_name() const
{
	return current_bb->getLabel();
}

void CFG::addVarUnused(string var)
{
	if( find(varUnused.begin(), varUnused.end(), var) == varUnused.end() )
		varUnused.push_back(var);
}

void CFG::deleteVarUsed(string var)
{
	varUnused.remove(var);
}

void CFG::warningsUnusedVar()
{
	std::list<string>::iterator it;
	for (it = varUnused.begin(); it != varUnused.end(); ++it)
		Errors::addError(*it, notUsed);
}

void CFG::addVarInitialised(string var)
{
	if( find(varInitialised.begin(), varInitialised.end(), var) == varInitialised.end() )
		varInitialised.push_back(var);
}

bool CFG::findVarInitialised(string var)
{
	if( find(varInitialised.begin(), varInitialised.end(), var) == varInitialised.end() )
		return false;
	else
		return true;
}

void CFG::checkInit(string var)
{
	// Test if the variable arg1 is initialised
	if( !findVarInitialised(var) )
	{
		Errors::addError(var, notInitialised);
		throw notInitialised;
	}

	// The variable arg1 is now used
	deleteVarUsed(var);
}

void CFG::checkDeclared(string var)
{
	if( (var[0] != '%') && (get_var_index(var) == 0) )
	{
		Errors::addError(var, notDeclared);
		throw notDeclared;
	}
	else
	{
		//var is now initialised
		addVarInitialised(var);
	}
}
