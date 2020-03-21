/******************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail :
******************************************************************/

#if ! defined ( ASM_H )
#define ASM_H

#include <iostream>
#include <string>

class CFG;
//-----------------------------------------------------------------

// class used for converting IR instructions to x86 assembly
class Asm
{
	public:

	//----- public methods -----
		void gen_prologue(int size);
		void gen_epilogue();

		void ldconst(std::string arg1, std::string arg2);
	
		// TODO : check if the globl exist in ARM and MSP430 ABI.
		void globl(std::string name);

	//---- overloaded operators ----
	//--- Constructors / Destructor ---
		Asm(CFG * graph, std::ostream &out);

	protected:
	//----- protected methods -----
	//----- protected attributes -----
		CFG * cfg;
		std::ostream &output;


};

#endif // ! defined ( ASM_H )
