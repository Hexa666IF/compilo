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
	output << "leave" << endl;
			//<< "movq %rbp, %rsp" << endl
		   //<< "popq %rbp" << endl
		   output << "ret" << endl;
}


void Asmx86::ldconst(string arg1, string arg2)
{
	// Getting x86 assembly code to access variables.
	arg1 = loadVariable(arg1);
	arg2 = cfg->IR_reg_to_asm_x86(arg2);

	output << "movl " << arg1 << ", " << arg2 << endl;	
}

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

void Asmx86::call(vector<string> args)
{
	for(int i = 1; i < args.size(); i++)
	{
		string arg = cfg->IR_reg_to_asm_x86(args[i]);
		string dest = cfg->IR_reg_to_asm_x86("%farg"+to_string(i));

		output << "movq " << arg << ", " << dest << endl;
	}
	
	output << "call " << args[0] << endl;
	//output << "leave" << endl;
}

void Asmx86::globl(string name)
{
	output << ".globl " << name << endl
		   << name << ":" << endl;
}

//------------- Constructor / Destructors ------------------------------------------------

Asmx86::Asmx86(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ----------------------------------------------

string Asmx86::loadVariable(string var)
{
	string asm_arg = cfg->IR_reg_to_asm_x86(var);
	if(asm_arg[0] != '$')
	// asm_arg is not a constant, it needs to be put in a register to
	// be available for computation.
	{
		output << "movl " << asm_arg << ", " << "%eax" << endl;
		asm_arg = "%eax";
	}

	return asm_arg;
}
