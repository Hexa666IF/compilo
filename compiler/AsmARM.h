/******************************************************************
Créé le : 18 mars 2020
par : pierre
e-mail :
******************************************************************/

#if ! defined ( ASMARM_H )
#define ASMARM_H

#include <iostream>
#include <string>

#include "Asm.h"


class CFG;
//-----------------------------------------------------------------

// class used for converting IR instructions to x86 assembly
class AsmARM : public Asm
{
	public:

	//----- public methods -----
		void gen_prologue(int size);
		void gen_epilogue(int size);
		void globl(std::string name);
		void label(std::string label);

// =============== 1 operand  instructions =====================

		void jump(std::string label);

// =============== 2 operands instructions =====================

		void ldconst(std::string arg1, std::string arg2);
		void ldparam(std::string arg1, std::string arg2);
		
// =============== 3 operands instructions =====================

		// add arg1 and arg2, and store the result into arg3.
		void add(std::string arg1, std::string arg2, std::string arg3);

		// sub arg1 and arg2, and store the result into arg3.
		void sub(std::string arg1, std::string arg2, std::string arg3);

		// mul arg1 and arg2, and store the result into arg3.
		void mul(std::string arg1, std::string arg2, std::string arg3);
		
		// Compare that arg1 is less or equal than arg2. (Jump to label if it is the case).
		void cmp_le(std::string arg1, std::string arg2, std::string label);
		
		// Compare that arg1 is less than arg2. (Jump to label if it is the case).
		void cmp_lt(std::string arg1, std::string arg2, std::string label);
		
		// Compare that arg1 equal to arg2. (Jump to label if it is the case).
		void cmp_eq(std::string arg1, std::string arg2, std::string label);

// =============== Special instructions ========================

		// call the function wich is the first string of the vector with the rest of the arguments.
		void call(std::vector<std::string> args);
			
	//---- overloaded operators ----
	//--- Constructors / Destructor ---
		AsmARM(CFG * graph, std::ostream &out);

	protected:
	//----- protected methods -----
	
		// Loads the variable into a register so that
		// it can be used for calculation.
		// It returns the register in wich the variable has
		// been put. (%eax, usually).
		std::string loadVariable(std::string var, std::string dest = "default");

		// Selects the correct 'load' operator to use betwenn ldr and mov
		std::string getLoadOperator(std::string arg);	
	//----- protected attributes -----
		CFG * cfg;
		std::ostream &output;


};

#endif // ! defined ( ASMARM_H )
