/*******************************************************************************************
Créé le : 22 mars 2020
par : pierre
e-mail :
*******************************************************************************************/

#include "Ast.h"

using namespace std;

//------------- public methods -------------------------------------------------

void Ast::gen_instr() const
{
	gen_instr(root);	
}

string Ast::get_tmp_var()
{
	string name = "!tmp" + to_string(n_tmp_var);
	++n_tmp_var;

	return name;
}


//------------- Constructor - Destructor ------------------------------------

Ast::Ast(node_s * node, CFG * control)
		: root(node), cfg(control), n_tmp_var(0)
{

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
