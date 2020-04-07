/******************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail :
******************************************************************/

#if ! defined ( ASM_H )
#define ASM_H

#include <iostream>
#include <string>
#include <vector>

class CFG;
//-----------------------------------------------------------------

// class used for converting IR instructions to x86 assembly
class Asm
{
	public:

	//----- public methods -----
		virtual void gen_prologue(int size) = 0;
		virtual void gen_epilogue(int size) = 0;
		virtual void globl(std::string name) = 0;
		virtual void label(std::string label) = 0;

// =============== 1 operands instructions =====================

		virtual void jump(std::string label) = 0;

// =============== 2 operands instructions =====================

		virtual void ldconst(std::string arg1, std::string arg2) = 0;
		virtual void ldparam(std::string arg1, std::string arg2) = 0;
	
// =============== 3 operands instructions =====================

		// add arg1 and arg2, and store the result into arg3.
		virtual void add(std::string arg1, std::string arg2, std::string arg3) = 0;

		// sub arg1 and arg2, and store the result into arg3.
		virtual void sub(std::string arg1, std::string arg2, std::string arg3) = 0;

		// mul arg1 and arg2, and store the result into arg3.
		virtual void mul(std::string arg1, std::string arg2, std::string arg3) = 0;
		
		// Compare that arg1 is less or equal than arg2. (Jump to label if it is the case).
		virtual void cmp_le(std::string arg1, std::string arg2, std::string label) = 0;
		
		// Compare that arg1 is less than arg2. (Jump to label if it is the case).
		virtual void cmp_lt(std::string arg1, std::string arg2, std::string label) = 0;
		
		// Compare that arg1 equal to arg2. (Jump to label if it is the case).
		virtual void cmp_eq(std::string arg1, std::string arg2, std::string label) = 0;

// =============== Special instructions ========================
		
		// call the function wich is the first string of the vector with the rest of the arguments.
		virtual void call(std::vector<std::string> args) = 0;
			

	//---- overloaded operators ----
	//--- Constructors / Destructor ---
		Asm(){};
		Asm(CFG * graph, std::ostream &out){};

	protected:
	//----- protected methods -----
	
		// Loads the variable into a register so that
		// it can be used for calculation.
		// It returns the register in wich the variable has
		// been put : dest if provided.
		virtual std::string loadVariable(std::string var, std::string dest) = 0;	
	//----- protected attributes -----
		// CFG * cfg;
		// std::ostream &output;


};

#endif // ! defined ( ASM_H )
