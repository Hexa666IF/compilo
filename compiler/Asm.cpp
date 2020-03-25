/*******************************************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail :
*******************************************************************************************/

using namespace std;

#include "Asm.h"
#include "IR.h"

//------------- public methods ---------------------------------------------------------

void Asm::gen_prologue(int size)
{
	output << "pushq %rbp" << endl
		   << "movq %rsp, %rbp" << endl
		   << "subq $" << size << ", %rsp" << endl;
}

void Asm::gen_epilogue()
{
	// TODO : check if ret is allowed.
	output << "movq %rbp, %rsp" << endl
		   << "pop %rbp" << endl
		   << "ret" << endl;
}


void Asm::ldconst(string arg1, string arg2)
{
	// Getting x86 assembly code to access variables.
	arg1 = cfg->IR_reg_to_asm(arg1);
	arg2 = cfg->IR_reg_to_asm(arg2);

	output << "movq " << arg1 << ", " << arg2 << endl;	
}

void Asm::add(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm(arg1);	
	arg2 = cfg->IR_reg_to_asm(arg2);
	arg3 = cfg->IR_reg_to_asm(arg3);
	
	output << "movq " << arg1 << ", " << arg3 << endl
		   << "addq " << arg2 << ", " << arg3 << endl;
}

void Asm::sub(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm(arg1);	
	arg2 = cfg->IR_reg_to_asm(arg2);
	arg3 = cfg->IR_reg_to_asm(arg3);
	
	output << "movq " << arg1 << ", " << arg3 << endl
		   << "subq " << arg2 << ", " << arg3 << endl;
}

void Asm::mul(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm(arg1);	
	arg2 = cfg->IR_reg_to_asm(arg2);
	arg3 = cfg->IR_reg_to_asm(arg3);

	output << "movq " << arg1 << ", " << arg3 << endl
		   << "mul " << arg2 << ", " << arg3 << endl;
}

void Asm::globl(string name)
{
	output << ".globl " << name << endl
		   << name << ":" << endl;
}

//------------- Constructor / Destructors ------------------------------------------------

Asm::Asm(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ---------------------------------------------------------
