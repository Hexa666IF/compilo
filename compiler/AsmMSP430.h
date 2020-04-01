/******************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail : Darkpierre@hotmail.fr
******************************************************************/

#if ! defined ( ASMMSP430_H )
#define ASMMSP430_H

#include <iostream>
#include <string>

#include "Asm.h"


class CFG;
//-----------------------------------------------------------------

// class used for converting IR instructions to MSP430 assembly
class AsmMSP430 : public Asm
{
	public:

	//----- public methods -----
		void gen_prologue(int size);
		void gen_epilogue(int size);

		void ldconst(std::string arg1, std::string arg2);
		
		// add arg1 and arg2, and store the result into arg3.
		void add(std::string arg1, std::string arg2, std::string arg3);

		// sub arg1 and arg2, and store the result into arg3.
		void sub(std::string arg1, std::string arg2, std::string arg3);

		// mul arg1 and arg2, and store the result into arg3.
		void mul(std::string arg1, std::string arg2, std::string arg3);
		
		// TODO : check if the globl exist in ARM and MSP430 ABI. It exists in ARM
		void globl(std::string name);

	//---- overloaded operators ----
	//--- Constructors / Destructor ---
		AsmMSP430(CFG * graph, std::ostream &out);

	protected:
	//----- protected methods -----
	
		// Loads the variable into a register so that
		// it can be used for calculation.
		// It returns the register in wich the variable has
		// been put. (%eax, usually).
		std::string loadVariable(std::string var);	
	//----- protected attributes -----
		CFG * cfg;
		std::ostream &output;


};

#endif // ! defined ( ASMMSP430_H )
