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
	output << "; start of prologue" << endl
		<< "SUB.W	#" << size << ", R1" << endl
		<< "; end of prologue" << endl;
}

void AsmMSP430::gen_epilogue(int size)
{
	output << "; start of epilogue" << endl
		<< "ADD.W	#" << size << ", R1" << endl
		<< "; end of epilogue" << endl;
}


void AsmMSP430::ldconst(string arg1, string arg2)
{
	output << "; "<< arg2 << "=" << arg1 << endl;

	// Getting MSP430 assembly code to access variables.
	arg1 = cfg->IR_reg_to_asm_msp430(arg1);
	arg2 = cfg->IR_reg_to_asm_msp430(arg2);

	output << "MOV.W	" << arg1 << ", " << arg2 << endl;	
}

void AsmMSP430::add(string arg1, string arg2, string arg3)
{
	output << "; " << arg3 << "=" << arg1 << "+" << arg2 << endl;
	
	arg1 = cfg->IR_reg_to_asm_msp430(arg1);	
	arg2 = cfg->IR_reg_to_asm_msp430(arg2);
	arg3 = cfg->IR_reg_to_asm_msp430(arg3);

	// doing arg3 = arg1 + arg2
	
	output << "MOV.W	"<< arg1  << ", R12" << endl
		   << "ADD.W	"<< arg2 << ", R12" << endl
		   << "MOV.W	R12, "<< arg3 << endl;
}

void AsmMSP430::sub(string arg1, string arg2, string arg3)
{
	output << "; " << arg3 << "=" << arg1 << "-" << arg2 << endl;
	
	arg1 = cfg->IR_reg_to_asm_msp430(arg1);	
	arg2 = cfg->IR_reg_to_asm_msp430(arg2);
	arg3 = cfg->IR_reg_to_asm_msp430(arg3);

	// doing arg3 = arg1 + arg2
	
	output << "MOV.W	"<< arg1  << ", R12" << endl
		   << "SUB.W	"<< arg2 << ", R12" << endl
		   << "MOV.W	R12, "<< arg3 << endl;
}

void AsmMSP430::mul(string arg1, string arg2, string arg3)
// to-do : find the MSP430 equivalent, also kill myself
{
	arg1 = cfg->IR_reg_to_asm_msp430(arg1);	
	arg2 = cfg->IR_reg_to_asm_msp430(arg2);
	arg3 = cfg->IR_reg_to_asm_msp430(arg3);
	
	output << "movl " << arg1 << ", " << "%eax" << endl;
	output << "movl " << arg2 << ", " << "%ebx" << endl;
	output << "mul %ebx" << endl;
	output << "movl %eax, " << arg3 << endl;
}

void AsmMSP430::globl(string name)
{
	output << ".global	" << name << endl
		<< "type " << name << " @function" << endl
		<< name << ":" << endl;
}

//------------- Constructor / Destructors ------------------------------------------------

AsmMSP430::AsmMSP430(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ----------------------------------------------

string AsmMSP430::loadVariable(string var)
{
	return var;
}
