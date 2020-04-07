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

	output << "@ start of prologue" << endl
		   << "str	fp, [sp, #-4]!" << endl
		   << "add	fp, sp, #0" << endl
		   << "sub	sp, sp, #"<< (size + (size % 8))+4 << endl //this ain't necessary when we no have variable
		   << "@ end of prologue" << endl;	
}

void AsmARM::gen_epilogue(int size)
{
	// to-do : if no return do a "mov	r3, #0"
	output << "@ start of epilogue" << endl
		   << "mov	r0, r3" << endl
		   << "sub	sp, fp, #0" << endl
		   << "ldr	fp, [sp], #4" << endl
		   << "bx	lr" << endl
		   << "@ end of epilogue" << endl;
}

void AsmARM::globl(string name)
{
	output << ".globl " << name << endl;
}

void AsmARM::label(string label)
{
	output << label << ":" << endl;
}

// =============== 1 operand  instructions =====================

void AsmARM::jump(string label)
{
	output << "@ jump" << endl;
	output << "@ not implemented" << endl;
}

// =============== 2 operands instructions =====================

void AsmARM::ldconst(string arg1, string arg2)
{
	output << "@ "<< arg2 << "=" << arg1 << endl;

	// Getting x86 assembly code to access variables.
	arg1 = cfg->IR_reg_to_asm_arm(arg1);
	arg2 = cfg->IR_reg_to_asm_arm(arg2);

	if (arg2 == "%retval") {
		output << getLoadOperator(arg1) << "	r3, " << arg1 << endl;	
	} else {
		output << getLoadOperator(arg1) << "	r3, " << arg1 << endl;	
		output << "str	r3, " << arg2 << endl;
	}
}

void AsmARM::ldparam(string arg1, string arg2){}

// =============== 3 operands instructions =====================

void AsmARM::add(string arg1, string arg2, string arg3)
{
	output << "@ " << arg3 << "=" << arg1 << "+" << arg2 << endl;

	arg1 = cfg->IR_reg_to_asm_arm(arg1);	
	arg2 = cfg->IR_reg_to_asm_arm(arg2);
	arg3 = cfg->IR_reg_to_asm_arm(arg3);

	output << getLoadOperator(arg1) << "	r2, " << arg1 << endl
		   << getLoadOperator(arg2) << "	r3, " << arg2 << endl
		   << "add	r3, r3, r2" << endl
		   << "str	r3, " << arg3 << endl;
}

void AsmARM::sub(string arg1, string arg2, string arg3)
{
	output << "@ " << arg3 << "=" << arg1 << "-" << arg2 << endl;

	arg1 = cfg->IR_reg_to_asm_arm(arg1);	
	arg2 = cfg->IR_reg_to_asm_arm(arg2);
	arg3 = cfg->IR_reg_to_asm_arm(arg3);

	// doing arg3 = arg1 - arg2
	
	output << getLoadOperator(arg1) << "	r2, " << arg1 << endl
		   << getLoadOperator(arg2) << "	r3, " << arg2 << endl
		   << "rsb	r3, r3, r2" << endl
		   << "str	r3, " << arg3 << endl;
}

void AsmARM::mul(string arg1, string arg2, string arg3)
{
	output << "@ " << arg3 << "=" << arg1 << "*" << arg2 << endl;

	arg1 = cfg->IR_reg_to_asm_arm(arg1);	
	arg2 = cfg->IR_reg_to_asm_arm(arg2);
	arg3 = cfg->IR_reg_to_asm_arm(arg3);

	output << getLoadOperator(arg1) << "	r2, " << arg1 << endl
		   << getLoadOperator(arg2) << "	r3, " << arg2 << endl
		   << "mul	r3, r3, r2" << endl
		   << "str	r3, " << arg3 << endl;
}

void AsmARM::cmp_le(string arg1, string arg2, string label)
{
	output << "@ " << arg1 << "<=" << arg2 << endl;
	output << "@ not implemented" << endl;
}	

void AsmARM::cmp_lt(string arg1, string arg2, string label)
{
	output << "@ " << arg1 << "<" << arg2 << endl;
	output << "@ not implemented" << endl;
}	

void AsmARM::cmp_eq(string arg1, string arg2, string label)
{
	output << "@ " << arg1 << "==" << arg2 << endl;
	output << "@ not implemented" << endl;
}

// =============== special instructions ========================

void AsmARM::call(vector<string> args)
{
	output << "@ call" << endl;
	output << "@ not implemented" << endl;
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

std::string AsmARM::getLoadOperator(std::string arg)
{
	if (arg[0]=='#') return "mov";
	return "ldr";
}
