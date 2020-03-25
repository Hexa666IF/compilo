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
		   << "popq %rbp" << endl
		   << "ret" << endl;
}


void Asm::ldconst(string arg1, string arg2)
{
	// Getting x86 assembly code to access variables.
	arg1 = loadVariable(arg1);
	arg2 = cfg->IR_reg_to_asm(arg2);

	output << "movl " << arg1 << ", " << arg2 << endl;	
}

void Asm::add(string arg1, string arg2, string arg3)
{
	arg1 = loadVariable(arg1);	
	arg3 = cfg->IR_reg_to_asm(arg3);
	output << "movl " << arg1 << ", " << arg3 << endl;	
	
	arg2 = loadVariable(arg2);
	output << "addl " << arg2 << ", " << arg3 << endl;
}

void Asm::sub(string arg1, string arg2, string arg3)
{
	arg1 = loadVariable(arg1);		
	arg3 = cfg->IR_reg_to_asm(arg3);
	output << "movl " << arg1 << ", " << arg3 << endl;

	arg2 = loadVariable(arg2);
	output << "subl " << arg2 << ", " << arg3 << endl;
}

void Asm::mul(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm(arg1);	
	arg2 = cfg->IR_reg_to_asm(arg2);
	arg3 = cfg->IR_reg_to_asm(arg3);
	
	output << "movl " << arg1 << ", " << "%eax" << endl;
	output << "mul " << arg2 << endl;
	output << "movl %eax, " << arg3 << endl;
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

//------------- Protected methods ----------------------------------------------

string Asm::loadVariable(string var)
{
	string asm_arg = cfg->IR_reg_to_asm(var);
	if(asm_arg[0] != '$')
	// asm_arg is not a constant, it needs to be put in a register to
	// be available for computation.
	{
		output << "movl " << asm_arg << ", " << "%eax" << endl;
		asm_arg = "%eax";
	}

	return asm_arg;
}
