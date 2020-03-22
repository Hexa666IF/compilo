/*******************************************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
*******************************************************************************************/

#include "Ast.h"

using namespace std;

// === node_s methods ==

node_s * create_leaf(string val)
{
	node_s * leaf = new node_s { true, IRInstr3op::add, nullptr, nullptr, val};
	// We give the 'add' value to the operation, but it will not be considered
	// anyway.
	return leaf;
}

node_s * create_node(IRInstr3op::Operation3op op, string valname)
{
	node_s * node = new node_s { false, op, nullptr, nullptr, valname };
	return node;
}

void uproot_node(node_s * root)
{
	if(root->left != nullptr)
			uproot_node(root->left);
	if(root->right != nullptr)
			uproot_node(root->right);

	delete root;
}	

//------------- public methods -------------------------------------------------

void Ast::gen_instr() const
{
	gen_instr(root);
	cfg->add_instr(IRInstr2op::ldconst, root->val, "%retval");	
}

string Ast::get_tmp_var()
{
	string name = "!tmp" + to_string(n_tmp_var);
	cfg->add_to_symbol_table(name);
	++n_tmp_var;
	
	return name;
}

void Ast::set_root(node_s * node)
{
	root = node;
}

//------------- Constructor - Destructor ------------------------------------

Ast::Ast(CFG * control)
		: root(nullptr), cfg(control), n_tmp_var(0)
{

}

Ast::~Ast()
{
	uproot_node(root);	
}

//------------- protected methods -----------------------------------------------

void Ast::gen_instr(node_s * node) const
{
	if(node->left->isValue == false)
			gen_instr(node->left);

	if(node->right->isValue == false)
			gen_instr(node->right);
	
	switch(node->op)
	{
			// TODO : put the values name in the right order for the instruction.
			// TODO : handle division ?
			case IRInstr3op::add:
				cfg->add_instr(	IRInstr3op::add, 
								node->left->val, 
								node->right->val, 
								node->val);
				break;
				
			case IRInstr3op::sub:
				cfg->add_instr(	IRInstr3op::sub, 
								node->left->val, 
								node->right->val, 
								node->val);
				break;

			case IRInstr3op::mul:
				cfg->add_instr(	IRInstr3op::mul, 
								node->left->val, 
								node->right->val, 
								node->val);
				break;

			default:
				break;
	}
}
