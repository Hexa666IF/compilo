/******************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
******************************************************************/

#if ! defined ( AST_H )
#define AST_H

#include <vector>
#include <deque>
#include <string>
#include <unordered_set>

#include "IR.h"
#include "Errors.h"

class Node
{
	public:
	// ----- public methods -----
		
		// Generate IRInstr and give them to the CFG.
		virtual void gen_instr(CFG * cfg) const = 0;

		void setParent(Function * f);

	// ----- Constructor - Destructor -----
		Node(Function * f = nullptr);
		// ~Node();

	protected:
	// ----- protected methods -----
	
	// ----- protected attributes -----
		Function * parentTree;
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
		RValue(Function * f = nullptr);
	
};

class Constant : public RValue
{
	public:
	// ----- public methods -----
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;	
	
	// ----- Constructor -----
		Constant(int val, Function * f);
		Constant(std::string val, Function * f);
	
	protected:
		int value;
};

class Variable : public RValue
{
	public:
	// ----- public methods -----
	
		// Return the name of the variable.
		// This function also call the removeFromUnuseds methods
		// from the AST. Indeed, if our variable is present in the
		// tree, that mean it is used somewhere in the source code.
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Variable(std::string variable, Function * f);

	protected:
		std::string name;
};

class FunctionCall : public RValue
{
	public:
	// ----- public methods -----
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		FunctionCall(	std::string functionName, 
						std::deque<RValue *> * args, 
						Function * f
					);

	protected:
		std::string name;
		std::deque<RValue *> * arguments;
};

class Operation : public RValue
{
	public:
	// ----- public methods -----
		std::string getValue() const;

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Operation(	
					IRInstr3op::Operation3op op, 
					RValue * l, 
					RValue * r, 
					Function * f
					);

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
		Return(RValue * rval, Function * f);

	protected:
		RValue * retvalue;
};

class Assign : public Node
{
	public:
	// ----- public methods -----

		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Assign(Variable * dest, RValue * rval, Function * f);
	
	protected:
		Variable * lvalue;
		RValue * rvalue;
};

// Represent a condition of the type :
// "left comparison right"
// For example : "a < 2" 
class Condition : public Node
{
	public :
		typedef enum { gt, ge, lt, le, eq } Comparison;
	
	// ----- Public methods -----
		virtual void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		Condition(RValue * l, Comparison comp, RValue * r);
	
	protected:
		RValue * left;
		RValue * right;
		Comparison comparison;

};

class If : public Node
{
	public :
	// ------ Public methods -----
		virtual void gen_instr(CFG * cfg) const;
	
	// ----- Constructor -----
		If(Condition * c, std::deque<Node *> * content);
	
	protected:
		Condition * condition;
		std::deque<Node *> * sub_nodes;
};

class IfElse : public If
{
	public :
	// ----- Public methods -----
		void gen_instr(CFG * cfg) const;

	// ----- Constructor -----
		IfElse(	Condition * c, 
				std::deque<Node *> * ifContent,
				std::deque<Node *> * elseContent
			  );
	
	protected:
		std::deque<Node *> * else_sub_nodes;
};

class While : public Node
{
	public:
	// ---- Public methods -----
		void gen_instr(CFG * cfg) const;
	
	// ---- Constructor ----
		While(Condition * c, std::deque<Node *> * content);

	protected:
		Condition * condition;
		std::deque<Node *> * sub_nodes;
};

class Function 
{
	public:
	//----- public methods -----
				
		// Add the node into the childs vector of the Function.
		void addNode(Node * node);
		
		void addSymbol(std::string symbol);

		// Generate IRInstr and put them into the CFG by
		// calling the cfg add_instr method.
		void gen_instr(CFG * cfg) const;
		
		// Remove a variable name from the unuseds unordered_set.
		// This method should be called by the node that can perform
		// checks to ensure that variable is declared... or used in this case.
		// If the variable has already been removed, the function does nothing.
		void removeFromUnuseds(std::string variable);

		// Return true if variable is in symbolIndex, 
		// return false otherwise.
		bool isDeclared(std::string variable) const;
		
		void setParameters(std::deque<Variable *> * params);

		void setChilds(std::deque<Node *> * block);

		std::map<std::string, int> & getSymbolIndex();
		int & getNextIndex();

		
		const std::unordered_set<std::string> & getUnuseds() const;
	
	//--- Constructor - Destructor ---
		Function(std::string name);	
		~Function();

	protected:
	//----- protected methods -----
	
	//----- protected attributes -----
		std::string name;
		std::deque<Variable *> * parameters;
		std::deque<Node *> * childs;

		// The symbol table held by the Function.
		// Variable will be inserted inside this map by the
		// addSymbol method.
		std::map<std::string, int> symbolIndex;
		int next_index;

		std::unordered_set<std::string> unuseds;

};

#endif // ! defined ( AST_H )
