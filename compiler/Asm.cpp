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
	output << "movq %rsp, %rbp" << endl
		   << "pop %rbp" << endl
		   << "ret" << endl;
}


void Asm::ldconst(string arg1, string arg2)
// TODO: refactoring...
{
	// Getting x86 assembly code to access variables.
	arg1 = cfg->IR_reg_to_asm(arg1);
	arg2 = cfg->IR_reg_to_asm(arg2);

	output << "movl " << arg1 << ", " << arg2 << endl;	
}
//------------- Constructor / Destructors ------------------------------------------------

Asm::Asm(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ---------------------------------------------------------
