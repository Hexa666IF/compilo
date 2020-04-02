/*******************************************************************************************
Créé le : 18 mars 2020
par : peter
e-mail : popiette@weaboos.united
*******************************************************************************************/

using namespace std;

#include "AsmARM.h"
#include "IR.h"

//------------- public methods ---------------------------------------------------------

void AsmARM::gen_prologue(int size)
{

	output << "str	fp, [sp, #-4]!" << endl
		   << "add	fp, sp, #0" << endl
		   << "sub	sp, sp, #"<< (size + (size % 8))+4 << endl; //this ain't necessary when we no have variable
		
}

void AsmARM::gen_epilogue()
{
	// to-do : if no return do a "mov	r3, #0"
	output << "mov	r0, r3" << endl
		   << "sub	sp, fp, #0" << endl
		   << "ldr	fp, [sp], #4" << endl
		   << "bx	lr" << endl;
}

void AsmARM::globl(string name)
{
	output << ".globl " << name << endl
		   << name << ":" << endl;
}

// =============== 2 operands instructions =====================

void AsmARM::ldconst(string arg1, string arg2)
{
	// Getting x86 assembly code to access variables.
	arg1 = cfg->IR_reg_to_asm_arm(arg1);
	arg2 = cfg->IR_reg_to_asm_arm(arg2);

	if (arg2 == "%retval") {
		output << "ldr	r3, " << arg1 << endl;	
	} else {
		output << "mov	r3, " << arg1 << endl;	
		output << "str	r3, " << arg2 << endl;
	}
}

// =============== 3 operands instructions =====================

void AsmARM::add(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm_arm(arg1);	
	arg2 = cfg->IR_reg_to_asm_arm(arg2);
	arg3 = cfg->IR_reg_to_asm_arm(arg3);

	output << "ldr	r2, " << arg1 << endl
		   << "ldr	r3, " << arg2 << endl
		   << "add	r3, r3, r2" << endl
		   << "str	r3, " << arg3 << endl;
}

void AsmARM::sub(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm_arm(arg1);	
	arg2 = cfg->IR_reg_to_asm_arm(arg2);
	arg3 = cfg->IR_reg_to_asm_arm(arg3);

	// doing arg3 = arg1 - arg2
	
	output << "ldr	r2, " << arg1 << endl
		   << "ldr	r3, " << arg2 << endl
		   << "rsb	r3, r3, r2" << endl
		   << "str	r3, " << arg3 << endl;
}

void AsmARM::mul(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm_arm(arg1);	
	arg2 = cfg->IR_reg_to_asm_arm(arg2);
	arg3 = cfg->IR_reg_to_asm_arm(arg3);

	output << "ldr	r2, " << arg1 << endl
		   << "ldr	r3, " << arg2 << endl
		   << "mul	r3, r3, r2" << endl
		   << "str	r3, " << arg3 << endl;
}

void AsmARM::cmp_le(string arg1, string arg2, string label)
{

}	

void AsmARM::cmp_lt(string arg1, string arg2, string label)
{

}	

void AsmARM::cmp_eq(string arg1, string arg2, string label)
{

}

// =============== special instructions ========================

void AsmARM::call(vector<string> args)
{

	
}

//------------- Constructor / Destructors ------------------------------------------------

AsmARM::AsmARM(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ---------------------------------------------------------

string AsmARM::loadVariable(string var, string dest)
{
	return var;
}
