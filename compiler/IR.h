#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

// Declarations from the parser -- replace with your own
#include "type.h"
#include "symbole.h"
class BasicBlock;
class CFG;
class DefFonction;


/*
 * IRInstr classes :
 *		Abstract representation of an assembly
 *		instruction.
 *		3 classes, wich inherit from IRInstr.
 */

// === IRInstr ===
// 		Base class for IRInstr3op, IRInstr2op
// 		and IRInstrSpecial.
// 		Cannot be instanciated, because it would
// 		be nonsense !

class IRInstr {
 
   public:
	
	/**  constructor */
	IRInstr(BasicBlock * bb);
	
	/** Actual code generation */
	void gen_asm(ostream &o) const = 0; /**< x86 assembly code generation for this IR instruction */
	
 protected:
	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
};

// === IRInstr2op ===
// 		2 operands instructions.
// 		Used for copy, ldconst, rmem
// 		and wmem.

class IRInstr2op : public IRInstr
{
	public:
		typedef enum {
			copy,
			ldconst,
			rmem,
			wmem
		} Operation2op;

	// === Constructors / Destructor ===
	
		IRInstr2op(	BasicBlock * bb,
					Operation2op op,
					std::string arg1,
					std::string arg2
				  );
	// === Overriden methods ===
	
		// code generation inherited from IRInstr.
		void gen_asm(std::ostream &o) const;
	
	protected:
		Operation2op operation;
		std::string arg1;
		std::string arg2;
};


// === IRInstr3op ===
// 		3 operands instructions.
// 		Used for add, sub, mul and 
// 		cmp_* operations.

class IRInstr3op : public IRInstr
{
	public:
		typedef enum {
			add,
			sub,
			mul,
			cmp_eq,
			cmp_lt,
			cmp_le
		} Operation3op;
		
	// === Constructors / Destructor ===
	
		IRInstr3op(	BasicBlock * bb,
					Operation3op op,
					std::string a1,
					std::string a2,
					std::string a3
				  );

	// === Overriden methods ===

		// Code generation inherited from IRInstr.
		void gen_asm(std::ostream &o) const;

	protected:
		Operation3op operation;
		std::string arg1;
		std::string arg2;
		std::string arg3;
};


// === IRInstrSpecial ===
// 		Special instructions with variables
// 		arguments.
// 		Only used for call, for now...

class IRInstrSpecial : public IRInstr
{
	public:
		typedef enum 
		{
			call
		} OperationSpe;

	// === Constructors / Destructor ===
	
		IRInstrSpecial(	BasicBlock * bb,
						OperationSpe op,
						std::vector<std::string> av
					  );
	// === Overriden methods ===
	
		// Code generation inherited from IRInstr.
		void gen_asm(std::ostream &o) const;
	
	protected:
		OperationSpe op;
		std::vector<std::string> args;
};


/**  The class for a basic block */

/* A few important comments.
	 IRInstr has no jump instructions:
	 assembly jumps are generated as follows in BasicBlock::gen_asm():
     1/ a cmp_* comparison instructions, if it is the last instruction of its block, 
       generates an actual assembly comparison followed by a conditional jump to the exit_false branch
			 If it is not the last instruction of its block, it behaves as an arithmetic two-operand instruction (add or mult)
		 2/ BasicBlock::gen_asm() first calls IRInstr::gen_asm() on all its instructions, and then 
		    if  exit_true  is a  nullptr, it generates the epilogue
				if  exit_false is not a nullptr, and the last instruction is not a cmp, it generates two conditional branches based on the value of the last variable assigned 
        otherwise it generates an unconditional jmp to the exit_true branch 
*/

class BasicBlock {
 public:
	BasicBlock(CFG* cfg, string entry_label);
	void gen_asm(ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

	void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);

	// No encapsulation whatsoever here. Feel free to do better.
	BasicBlock* exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
	BasicBlock* exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
	string label; /**< label of the BB, also will be the label in the generated code */
	CFG* cfg; /** < the CFG where this block belongs */
	vector<IRInstr*> instrs; /** < the instructions themselves. */
 protected:

 
};




/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of bbs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {
 public:
	CFG(DefFonction* ast);

	DefFonction* ast; /**< The AST this CFG comes from */
	
	void add_bb(BasicBlock* bb); 

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	void gen_asm(ostream& o);
	string IR_reg_to_asm(string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
	void gen_asm_prologue(ostream& o);
	void gen_asm_epilogue(ostream& o);

	// symbol table methods
	void add_to_symbol_table(string name, Type t);
	string create_new_tempvar(Type t);
	int get_var_index(string name);
	Type get_var_type(string name);

	// basic block management
	string new_BB_name();
	BasicBlock* current_bb;

 protected:
	map <string, Type> SymbolType; /**< part of the symbol table  */
	map <string, int> SymbolIndex; /**< part of the symbol table  */
	int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	int nextBBnumber; /**< just for naming */
	
	vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
};


#endif
