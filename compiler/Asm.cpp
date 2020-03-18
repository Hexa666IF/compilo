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
	int index1 = cfg->get_var_index(arg1);
	int index2 = cfg->get_var_index(arg2);

	if(index1 != 0)
			arg1 = to_string( - index1 ) + "(%rbp)";
	else
			arg1 = "$" + arg1;
	
	if(index2 != 0)
			arg2 = to_string( - index2 ) + "(%rbp)";
	else
			arg2 = "$" + arg2;

	cout << "movl " << arg1 << ", " << arg2 << endl;	
}
//------------- Constructor / Destructors ------------------------------------------------

Asm::Asm(CFG * graph, ostream &out) : cfg(graph), output(out)
{

}	

//------------- Protected methods ---------------------------------------------------------
