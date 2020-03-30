/******************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
******************************************************************/

#if ! defined ( AST_H )
#define AST_H

#include <vector>
#include <string>

#include "IR.h"

class Node
{
	public:
	// ----- public methods -----
	
		// Generate IRInstr and give them to the CFG.
		virtual void gen_instr(CFG * cfg) const = 0;

	// ----- Constructor - Destructor -----
		// Node();
		// ~Node();

	protected:
	// ----- protected methods -----
	
	// ----- protected attributes -----
};

class RValue : public Node
{
	public:
	// ----- public methods -----
	
		// Returns the value of the RValue.
		// Due to the subclasses, it can be the result of a
		// calculation, a constant, or a variable.
		virtual std::string getValue() const = 0;

	// ----- Constructor - Destructor -----
	
};

class Constant : public RValue
{
	public:
	// ----- public methods -----
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;	
	
	// ----- Constructor -----
		Constant(int val);
		Constant(std::string val);
	
	protected:
		int value;
};

class Variable : public RValue
{
	public:
	// ----- public methods -----
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Variable(std::string variable);

	protected:
		std::string name;
};

class Operation : public RValue
{
	public:
	// ----- public methods -----
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Operation(IRInstr3op::Operation3op op, RValue * l, RValue * r);
		~Operation();
		
	protected:
	// ----- protected methods -----
		
		// Return a temporary variable name for storing the
		// intermediate result of the computation.
		// For example : tmp1, tmp7...
		static std::string get_tmp_var();

	// ----- Protected attributes ----
		RValue * left;
		RValue * right;
		IRInstr3op::Operation3op operation;

		// The temporary variable name for the intermediate result.
		std::string tmp_var;
};

class Return : public Node
{
	public:
	// ----- public methods -----
	
		void gen_instr(CFG * cfg) const;
	
	// ----- Constructor -----	
		Return(RValue * rval);

	protected:
		RValue * retvalue;
};

class Assign : public Node
{
	public:
	// ----- public methods -----

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Assign(Variable * dest, RValue * rval);
	
	protected:
		Variable * lvalue;
		RValue * rvalue;
};

// Abstract Syntax Tree for computation representation.
// This class generate the instruction that will lead to
// the result to store somewhere in the memory.
class Ast
{
	public:
	//----- public methods -----
				
		// Add the node into the childs vector of the AST.
		void addNode(Node * node);
		
		void addSymbol(std::string symbol);

		std::map<std::string, int> getSymbolIndex() const;

	//--- Constructor - Destructor ---
		Ast();	
		~Ast();

	protected:
	//----- protected methods -----
	
	//----- protected attributes -----
		
		std::vector<Node *> childs;

		// The symbol table held by the AST.
		// Variable will be inserted inside this map by the
		// addSymbol method.
		std::map<std::string, int> symbolIndex;
		int next_index;

};

#endif // ! defined ( AST_H )
