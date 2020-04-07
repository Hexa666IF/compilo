/*******************************************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail :
*******************************************************************************************/

using namespace std;

#include "Asmx86.h"
#include "IR.h"

//------------- public methods ---------------------------------------------------------

void Asmx86::gen_prologue(int size)
{
	output << "pushq %rbp" << endl
		   << "movq %rsp, %rbp" << endl;
	
	//subq the stack pointeur by the nearest upper 16 multiple of the allocated memory
	int decalage = size;
	int reste = decalage % 16;
	if(reste){
		decalage = ((decalage / 16) * 16) + 16;
	}

	output << "subq $" << decalage << ", %rsp" << endl;
}

void Asmx86::gen_epilogue()
{
	output << "movq %rbp, %rsp" << endl
		   << "popq %rbp" << endl
		   << "ret" << endl;
}

void Asmx86::globl(string name)
{
	output << ".globl " << name << endl;
		 //  << name << ":" << endl;
}

void Asmx86::label(string label)
{
	output << label << ":" << endl;
}

// =============== 1 operand instructions  =====================

void Asmx86::jump(string label)
{
	output << "jmp " << label << endl;
}

// =============== 2 operands instructions =====================

void Asmx86::ldconst(string arg1, string arg2)
{
	// Getting x86 assembly code to access variables.
	arg1 = loadVariable(arg1);
	arg2 = cfg->IR_reg_to_asm_x86(arg2);

	output << "movl " << arg1 << ", " << arg2 << endl;	
}

void Asmx86::ldparam(string arg1, string arg2)
{
	// Getting x86 assembly code to access variables.
	arg1 = cfg->IR_reg_to_asm_x86(arg1);
	arg2 = cfg->IR_reg_to_asm_x86(arg2);

	output << "movl " << arg1 << ", " << arg2 << endl;	
}

// =============== 3 operands instructions =====================

void Asmx86::add(string arg1, string arg2, string arg3)
{
	arg1 = loadVariable(arg1);	
	arg3 = cfg->IR_reg_to_asm_x86(arg3);
	output << "movl " << arg1 << ", " << arg3 << endl;	
	
	arg2 = loadVariable(arg2);
	output << "addl " << arg2 << ", " << arg3 << endl;
}

void Asmx86::sub(string arg1, string arg2, string arg3)
{
	arg1 = loadVariable(arg1);		
	arg3 = cfg->IR_reg_to_asm_x86(arg3);
	output << "movl " << arg1 << ", " << arg3 << endl;

	arg2 = loadVariable(arg2);
	output << "subl " << arg2 << ", " << arg3 << endl;
}

void Asmx86::mul(string arg1, string arg2, string arg3)
{
	arg1 = cfg->IR_reg_to_asm_x86(arg1);	
	arg2 = cfg->IR_reg_to_asm_x86(arg2);
	arg3 = cfg->IR_reg_to_asm_x86(arg3);
	
	output << "movl " << arg1 << ", " << "%eax" << endl;
	output << "movl " << arg2 << ", " << "%ebx" << endl;
	output << "mul %ebx" << endl;
	output << "movl %eax, " << arg3 << endl;
}

void Asmx86::cmp_le(string arg1, string arg2, string label)
{
	setup_cmp(arg1, arg2);
	output << "jle " << label << endl;
}

void Asmx86::cmp_lt(string arg1, string arg2, string label)
{
	setup_cmp(arg1, arg2);
	output << "jl " << label << endl;
}

void Asmx86::cmp_eq(string arg1, string arg2, string label)
{
	setup_cmp(arg1, arg2);
	output << "jnz " << label << endl;
}

// =============== Special instructions =====================

void Asmx86::call(vector<string> args)
{
	for(int i = 1; i < args.size(); i++)
	{
		string arg = cfg->IR_reg_to_asm_x86(args[i]);
		string dest = cfg->IR_reg_to_asm_x86("%farg"+to_string(i));

		output << "movl " << arg << ", " << dest << endl;
	}
	
	output << "call " << args[0] << endl;
	output << "movl %eax, %ecx" << endl;
}

//------------- Constructor / Destructors ------------------------------------------------

Asmx86::Asmx86(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ----------------------------------------------

string Asmx86::loadVariable(string var, string dest)
{
	string asm_arg = cfg->IR_reg_to_asm_x86(var);
	// if(asm_arg[0] != '$')
	// asm_arg is not a constant, it needs to be put in a register to
	// be available for computation.
	{
		output << "movl " << asm_arg << ", " << dest << endl;
		asm_arg = dest;
	}

	return asm_arg;
}

void Asmx86::setup_cmp(string & arg1, string & arg2)
{
	arg1 = cfg->IR_reg_to_asm_x86(arg1);
	arg2 = cfg->IR_reg_to_asm_x86(arg2);
	// Test to avoid putting the two values in the same register...
	// Not very clean, I admit.
	if(arg2 != "%eax")
	{
		output << "movl " << arg1 << ", %eax" << endl;
		arg1 = "%eax";
		output << "movl " << arg2 << ", %ebx" << endl;
		arg2 = "%ebx";
	}
	else
	{
		output << "movl " << arg1 << ", %ebx" << endl;
		arg1 = "%ebx";
	}
		
	// Arg2 is put first to check (arg1 - arg2). see x86 doc.
	output << "cmp " << arg2 << ", " << arg1 << endl;

}
