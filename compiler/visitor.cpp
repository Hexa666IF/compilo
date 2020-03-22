
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"
#include <string>
#include <iostream>

using namespace std;

Visitor::Visitor(CFG * c) : ifccVisitor(), cfg(c), ast(nullptr)
{

}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
	visit(ctx->l());
	return 0;
}

antlrcpp::Any Visitor::visitLDecl(ifccParser::LDeclContext *ctx)
{	
	visit(ctx->decl());
	visit(ctx->l());

	return 0;
}

antlrcpp::Any Visitor::visitLAffect(ifccParser::LAffectContext *ctx)
{
	visit(ctx->affect());
	visit(ctx->l());

	return 0;
}

antlrcpp::Any Visitor::visitReturn(ifccParser::ReturnContext *ctx)
{
	string retval = visit(ctx->val());
	cfg->add_instr(IRInstr2op::ldconst, retval, "%retval");

	return 0;
}

antlrcpp::Any Visitor::visitLEpsilon(ifccParser::LEpsilonContext *ctx)
{
	return 0;
}

antlrcpp::Any Visitor::visitDeclMultiple(ifccParser::DeclMultipleContext *ctx)
{
	// Add symbol name to symbol table.
	string symbol = ctx->TEXT()->getText();
	cfg->add_to_symbol_table(symbol);
	visit(ctx->decl());

	return 0;
}

antlrcpp::Any Visitor::visitDeclSimple(ifccParser::DeclSimpleContext *ctx)
{
	// Add symbol name to symbol table.
	string symbol = ctx->TEXT()->getText();
	cfg->add_to_symbol_table(symbol);

	return 0;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx)
{
	string var = visit(ctx->var());	

	ast = new Ast(cfg);
	
	node_s * root = visit(ctx->expr());
	ast->set_root(root);
	ast->gen_instr();
	cfg->add_instr(IRInstr2op::ldconst, "%retval", var);
	delete(ast);
	ast = nullptr;

	return 0;
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *ctx)
{
	// Add symbol name to symbol table.
	string symbol = ctx->TEXT()->getText();
	cfg->add_to_symbol_table(symbol);
	return symbol;
}

antlrcpp::Any Visitor::visitVarText(ifccParser::VarTextContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	return symbol;
}

antlrcpp::Any Visitor::visitValConst(ifccParser::ValConstContext *ctx)
{
	string val = ctx->CONST()->getText();
	//node_s * value = create_leaf(val);
	return val;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx)
{
	// Search for symbol index into symbol table.	
	// string retval = "%retval";
	 string symbol = ctx->TEXT()->getText();
	// cfg->add_instr(IRInstr2op::ldconst, symbol, retval);
	//node_s * var = create_leaf(symbol);
	
	return symbol;
}

// === Expression computation related methods ===

antlrcpp::Any Visitor::visitAdd(ifccParser::AddContext *ctx) {
	std::cout << "Adding";
	node_s * left = visit(ctx->term());
	node_s * right = visit(ctx->expr());
	string tmpvar = ast->get_tmp_var();

	node_s * add = create_node(IRInstr3op::add, tmpvar);
	add->left = left;
	add->right = right;
	// TODO : add into the AST.
	return add;
}

antlrcpp::Any Visitor::visitSub(ifccParser::SubContext *ctx) {
	std::cout << "Subtracting";
	node_s * left = visit(ctx->term());
	node_s * right = visit(ctx->expr());
	string tmpvar = ast->get_tmp_var();

	node_s * sub = create_node(IRInstr3op::sub, tmpvar);
	sub->left = left;
	sub->right = right;
	// TODO : add into the AST.
	return sub;
}

antlrcpp::Any Visitor::visitExpr_single(ifccParser::Expr_singleContext *ctx) {
	std::cout << "Visiting Expr";
	return visit(ctx->term());
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *ctx) {
	node_s * left = visit(ctx->f());
	node_s * right = visit(ctx->term());
	string tmpvar = ast->get_tmp_var();

	node_s * mul = create_node(IRInstr3op::mul, tmpvar);
	mul->left = left;
	mul->right = right;
	return mul;
}

antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *ctx) {
	// TODO: handle division ! 
	return 0;
}

antlrcpp::Any Visitor::visitF_single(ifccParser::F_singleContext *ctx) {
	std::cout << "Visiting F_single";
	return visit(ctx->f());
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx) {
	std::cout << "Visiting const";
	//visit(ctx->f());
	node_s * leaf = create_leaf(visit(ctx->val())); 
	return leaf;
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *ctx) {
	visit(ctx->expr());
	return 0;
}


