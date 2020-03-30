/*******************************************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail : Darkpierre@hotmail.fr
*******************************************************************************************/

using namespace std;

#include "AsmMSP430.h"
#include "IR.h"

//------------- public methods ---------------------------------------------------------

void AsmMSP430::gen_prologue(int size)
{
	output << "SUB.W   #" << size << ", R1" << endl;
}

void AsmMSP430::gen_epilogue()
// to-do : find MSP430 epilogue
{
	output << "movq %rbp, %rsp" << endl
		   << "popq %rbp" << endl
		   << "ret" << endl;
}


void AsmMSP430::ldconst(string arg1, string arg2)
// to-do : find the MSP430 equivalent
{
	// Getting MSP430 assembly code to access variables.
	arg1 = loadVariable(arg1);
	arg2 = cfg->IR_reg_to_asm_MSP430(arg2);

	output << "movl " << arg1 << ", " << arg2 << endl;	
}

void AsmMSP430::add(string arg1, string arg2, string arg3)
// to-do : find the MSP430 equivalent
{
	arg1 = loadVariable(arg1);	
	arg3 = cfg->IR_reg_to_asm_MSP430(arg3);
	output << "movl " << arg1 << ", " << arg3 << endl;	
	
	arg2 = loadVariable(arg2);
	output << "addl " << arg2 << ", " << arg3 << endl;
}

void AsmMSP430::sub(string arg1, string arg2, string arg3)
// to-do : find the MSP430 equivalent
{
	arg1 = loadVariable(arg1);		
	arg3 = cfg->IR_reg_to_asm_MSP430(arg3);
	output << "movl " << arg1 << ", " << arg3 << endl;

	arg2 = loadVariable(arg2);
	output << "subl " << arg2 << ", " << arg3 << endl;
}

void AsmMSP430::mul(string arg1, string arg2, string arg3)
// to-do : find the MSP430 equivalent, also kill myself
{
	arg1 = cfg->IR_reg_to_asm_MSP430(arg1);	
	arg2 = cfg->IR_reg_to_asm_MSP430(arg2);
	arg3 = cfg->IR_reg_to_asm_MSP430(arg3);
	
	output << "movl " << arg1 << ", " << "%eax" << endl;
	output << "movl " << arg2 << ", " << "%ebx" << endl;
	output << "mul %ebx" << endl;
	output << "movl %eax, " << arg3 << endl;
}

void AsmMSP430::globl(string name)
// to-do : find the MSP430 equivalent
{
	output << ".globl " << name << endl
		   << name << ":" << endl;
}

//------------- Constructor / Destructors ------------------------------------------------

AsmMSP430::AsmMSP430(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ----------------------------------------------

string AsmMSP430::loadVariable(string var)
// to-do : find the MSP430 equivalent
{
	string asm_arg = cfg->IR_reg_to_asm_MSP430(var);
	if(asm_arg[0] != '$')
	// asm_arg is not a constant, it needs to be put in a register to
	// be available for computation.
	{
		output << "movl " << asm_arg << ", " << "%eax" << endl;
		asm_arg = "%eax";
	}

	return asm_arg;
}
