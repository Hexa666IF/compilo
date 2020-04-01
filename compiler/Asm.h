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
		virtual void gen_prologue(int size) = 0;
		virtual void gen_epilogue(int size) = 0;

		virtual void ldconst(std::string arg1, std::string arg2) = 0;
		
		// add arg1 and arg2, and store the result into arg3.
		virtual void add(std::string arg1, std::string arg2, std::string arg3) = 0;

		// sub arg1 and arg2, and store the result into arg3.
		virtual void sub(std::string arg1, std::string arg2, std::string arg3) = 0;

		// mul arg1 and arg2, and store the result into arg3.
		virtual void mul(std::string arg1, std::string arg2, std::string arg3) = 0;
		
		// TODO : check if the globl exist in ARM and MSP430 ABI.
		virtual void globl(std::string name) = 0;

	//---- overloaded operators ----
	//--- Constructors / Destructor ---
		Asm(){};
		Asm(CFG * graph, std::ostream &out){};

	protected:
	//----- protected methods -----
	
		// Loads the variable into a register so that
		// it can be used for calculation.
		// It returns the register in wich the variable has
		// been put. (%eax, usually).
		virtual std::string loadVariable(std::string var) = 0;	
	//----- protected attributes -----
		// CFG * cfg;
		// std::ostream &output;


};

#endif // ! defined ( ASM_H )
