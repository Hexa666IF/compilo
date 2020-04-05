#include "IR.h"
#include <algorithm>

using namespace std;

#include "Ast.h"
#include "reg.h"

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

IRInstr1op::IRInstr1op( BasicBlock * bb,
						Operation1op op,
						string a1
					  )
: IRInstr(bb), operation(op), arg1(a1)
{

}

void IRInstr1op::gen_asm(Asm & toasm) const
{
	toasm.jump(arg1);
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

		case cmp_eq:
			toasm.cmp_eq(arg1, arg2, arg3);
			break;

		case cmp_lt:
			toasm.cmp_lt(arg1, arg2, arg3);
			break;

		case cmp_le:
			toasm.cmp_le(arg1, arg2, arg3);
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
	switch(operation)
	{
		case call:
				toasm.call(args);
				break;

		default:
				break;
	}	
}

// ============================= BasicBlock =================================

// === Static attribute initialisation ===

unsigned int BasicBlock::nextId = 0;

// === Constructor / Destructor  ===

BasicBlock::BasicBlock(CFG * c, string entry_label)
: exit_true(nullptr), exit_false(nullptr), label(entry_label), cfg(c)
{

}

BasicBlock::BasicBlock(CFG * c)
: 	exit_true(nullptr), 
	exit_false(nullptr), 
	label("label_" + to_string(nextId++)), 
	cfg(c)
{
	
}

// === public methods ===

// Static method
string BasicBlock::getNextLabel()
{
	return "label_" + to_string(nextId);
}

void BasicBlock::gen_asm(Asm &toasm)
{
	for( IRInstr * instr : instrs )
	{
		instr->gen_asm(toasm);
	}
}

void BasicBlock::add_instr(IRInstr1op::Operation1op op, string arg1)
{
	IRInstr1op * instr = new IRInstr1op(this, op, arg1);
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

CFG::CFG(Function * tree, std::string asm_choice)
: func(tree), SymbolIndex(tree->getSymbolIndex()), nextFreeSymbolIndex(tree->getNextIndex())
{
	if (asm_choice=="-arm") {
		toasm = new AsmARM(this,cout);
	} else if (asm_choice=="-msp430") {
		toasm = new Asmx86(this,cout);
	} else {
		toasm = new Asmx86(this,cout);
	}
	
	current_bb = new BasicBlock(this, "main");
	bbs.push_back(current_bb);
}

// === public methods ===

void CFG::add_bb(BasicBlock * bb)
{
	bbs.push_back(bb);
	current_bb = bb;
}

void CFG::add_instr(IRInstr1op::Operation1op op, string arg1)
{
	current_bb->add_instr(op, arg1);
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


void CFG::gen_asm()
{
	string name = func->getName();
	if(name == "main")
	{
		toasm->globl("main");
	}
	toasm->label(name);
	toasm->gen_prologue(SymbolIndex.size()*4);
	bbs[0]->gen_asm(*toasm);
	for(unsigned int i = 1; i < bbs.size(); ++i)
	{
		toasm->label(bbs[i]->getLabel());
		bbs[i]->gen_asm(*toasm);
	}
	toasm->gen_epilogue();
}

// = symbol table methods =

string CFG::IR_reg_to_asm_x86(std::string reg)
{
	static const unsigned int n_reg = 10;
	static const string abstract_reg [] = 
		{ 	RETVAL, RETVALD, RBASEP, RSTACKP,
			FARG1, FARG2, FARG3, FARG4,
			FARG5, FARG6
		};

	static const string x86_reg [] =
		{	"%eax", "%edx", "%rbp", "%rsp",
			"%rdi", "%rsi", "%rdx", "%rcx",
			"%r8", "%r9"
		};

	string asm_reg;
	int index = get_var_index(reg);

	if(index != 0)
	{
		asm_reg = to_string(-index) + "(%rbp)";
	}
	else if (reg[0] == '%')
	{
			unsigned int i = 0;
			while(i < n_reg && reg != abstract_reg[i])
				++i;

			if(i < 10)
				asm_reg = x86_reg[i];
			else
				asm_reg = "BAD ABSTRACT REG : " + reg;
	}
	else 
	{
		asm_reg = '$' + reg;
	}

	return asm_reg;
}

string CFG::IR_reg_to_asm_arm(std::string reg)
{
	string asm_reg;
	int index = get_var_index(reg);
	index = index;

	if(index != 0)
	{
		asm_reg = "[fp, #" + to_string(-(index+4)) + "]";
	}
	else if (reg[0] == '%')
	{
		asm_reg = reg;
	}
	else 
	{
		asm_reg = '#' + reg;
	}

	return asm_reg;
}

int CFG::get_symbol_table_length() const
{
	return SymbolIndex.size();
}

void CFG::add_to_symbol_table(string name)
{
	// handle multiple declaration errors.
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

int CFG::get_var_index(const string name) const
{
	int index = 0;
	map<string, int>::const_iterator it = SymbolIndex.find(name);
	if(it != SymbolIndex.cend())
			index = it->second;
	
	return index;
}

