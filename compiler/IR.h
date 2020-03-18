#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
// Declarations from the parser -- replace with your own

class BasicBlock;
class CFG;
class Ast;


// TODO : there was a Type.h and Type used in the code. What's this ?

/*
 * IRInstr classes :
 *		Abstract representation of an assembly
 *		instruction.
 *		3 classes, wich inherit from IRInstr.
 */

// === IRInstr ===
// 		Base class for IRInstr3op, IRInstr2op
// 		and IRInstrSpecial.
// 		It is an instruction with 1 operand !

class IRInstr {
 
   public:
	
	/**  constructor */
	IRInstr(BasicBlock * bb);
	virtual ~IRInstr();
	
	/** Actual code generation */
	virtual void gen_asm(std::ostream &o) const = 0; /**< x86 assembly code generation for this IR instruction */
	
 protected:
	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	// Type t ?
};

class IRInstr1op : public IRInstr
{
	public:

		typedef enum
		{
			push,
			pop
		} Operation1op;

	// === Constructor / Destructor ===
	
		IRInstr1op(	BasicBlock * bb,
					Operation1op op,
					std::string a
			  	);
		virtual ~IRInstr1op();

	// === Overriden method from IRInstr ===
		
		// Code generation.
		void gen_asm(std::ostream &o) const;

	protected:
		Operation1op operation;
		std::string arg;
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
			wmem,
			movq,
			movl
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
		OperationSpe operation;
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
		BasicBlock(CFG* c, std::string entry_label);
		void gen_asm(std::ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

		//void add_instr(IRInstr * instr);
		void add_instr(IRInstr1op::Operation1op op, std::string arg);
		void add_instr(IRInstr2op::Operation2op op, std::string arg1, std::string arg2);
		void add_instr(IRInstr3op::Operation3op op, std::string arg1, std::string arg2, std::string arg3);
		void add_instr(IRInstrSpecial::OperationSpe op, std::vector<std::string> args);
		//void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);
		
		// Return the label of the basic block.
		// TODO : check if the return of this method can be a const reference.
		std::string getLabel() const;

	protected:
		BasicBlock* exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
		BasicBlock* exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
		std::string label; /**< label of the BB, also will be the label in the generated code */
		CFG* cfg; /** < the CFG where this block belongs */
		std::vector<IRInstr*> instrs; /** < the instructions themselves. */
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
	CFG(Ast* ast);

	
	void add_bb(BasicBlock* bb); 

	// Add the IRInstr to the current BasicBlock.
	//void add_instr(IRInstr * instr);
	void add_instr(IRInstr1op::Operation1op op, std::string arg);
	void add_instr(IRInstr2op::Operation2op op, std::string arg1, std::string arg2);
	void add_instr(IRInstr3op::Operation3op op, std::string arg1, std::string arg2, std::string arg3);
	void add_instr(IRInstrSpecial::OperationSpe op, std::vector<std::string> args);

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	// This method has not been declared const yet, because we aren't sure
	// that this method won't modify some attributes of the CFG, for example
	// the basicblocks pointers...
	void gen_asm(std::ostream& o);
	
	// Helper method : inputs a IR reg or input variable, and return
	// e.g. "-24(%rbp)" for the proper value of 24 
	std::string IR_reg_to_asm(std::string reg);
	
	void gen_asm_prologue(std::ostream& o);
	void gen_asm_epilogue(std::ostream& o);

	// symbol table methods
	void add_to_symbol_table(std::string name); // , Type t);
	std::string create_new_tempvar();  // Type t);
	int get_var_index(std::string name);
	//Type get_var_type(std::string name);

	// basic block management
	// TODO : check if the return of this method can be a const reference.
	std::string new_BB_name() const;

 protected:
	
	Ast* ast; /**< The AST this CFG comes from */
	BasicBlock* current_bb;
	
	//std::map <std::string, Type> SymbolType; /**< part of the symbol table  */
	std::map <std::string, int> SymbolIndex; /**< part of the symbol table  */
	int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	int nextBBnumber; /**< just for naming */
	
	std::vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
};


#endif