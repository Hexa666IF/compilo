/******************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
******************************************************************/

#if ! defined ( AST_H )
#define AST_H

#include <string>

#include "IR.h"

// Representation of an operation of the Abstract Syntax
// Tree.
typedef struct node_s
{
	bool isValue;
	IRInstr3op::Operation3op op;
	node_s * left;
	node_s * right;
	std::string val;
} node_s;

// Abstract Syntax Tree for computation representation.
// This class generate the instruction that will lead to
// the result to store somewhere in the memory.
class Ast
{
	public:
	//----- public methods -----
		
		// void add(node_s * node, node_s * left_child, node_s * right_child);

		// Generate the instructions computing and storing the result
		// into the %retval register.
		void gen_instr() const;
		
		// return the string corresponding to the next tmp_var name
		// available for the computation.
		// Each call to this function reserves a name.
		std::string get_tmp_var();

	//--- Constructor - Destructor ---
		Ast(node_s * node, CFG * control);	
	
	protected:
	//----- protected methods -----
	
	// generate instructions from another point
	// in the tree than the root point.
	// This is why this function is protected : 
	// 		We don't want the user to be able to mess up with
	// 		the generated instructions...
	void gen_instr(node_s * node) const;

	//----- protected attributes -----
		node_s * root;
		CFG * cfg;

		// gives the next tmp variable number for symbol table.
		unsigned int n_tmp_var;

};

#endif // ! defined ( AST_H )
