
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
	ast = new Ast(cfg);
	
	node_s * root = visit(ctx->expr());
	ast->set_root(root);
	ast->gen_instr();
	delete(ast);
	ast = nullptr;

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
	cfg->add_instr(IRInstr2op::ldconst, "0", symbol);

	return 0;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx)
{
	string var = visit(ctx->var());	

	ast = new Ast(cfg, var);
	
	node_s * root = visit(ctx->expr());
	ast->set_root(root);
	ast->gen_instr();
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
	
	return val;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	
	return symbol;
}

// === Expression computation related methods ===

antlrcpp::Any Visitor::visitAdd(ifccParser::AddContext *ctx) {
	string tmpvar = ast->get_tmp_var();
	node_s * left = visit(ctx->term());
	node_s * right = visit(ctx->expr());

	node_s * add = create_node(IRInstr3op::add, tmpvar, left, right);
	
	return add;
}

antlrcpp::Any Visitor::visitSub(ifccParser::SubContext *ctx) {
	string tmpvar = ast->get_tmp_var();
	node_s * left = visit(ctx->term());
	node_s * right = visit(ctx->expr());

	node_s * sub = create_node(IRInstr3op::sub, tmpvar, left, right);
	
	return sub;
}

antlrcpp::Any Visitor::visitExpr_single(ifccParser::Expr_singleContext *ctx) {
	return visit(ctx->term());
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *ctx) {
	string tmpvar = ast->get_tmp_var();
	node_s * left = visit(ctx->f());
	node_s * right = visit(ctx->term());

	node_s * mul = create_node(IRInstr3op::mul, tmpvar, left, right);
	return mul;
}

antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *ctx) {
	// Division is not part of the requirements.
	// We'll handle it later maybe.
	return 0;
}

antlrcpp::Any Visitor::visitF_single(ifccParser::F_singleContext *ctx) {
	return visit(ctx->f());
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx) {
	node_s * leaf = create_leaf(visit(ctx->val())); 
	return leaf;
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *ctx) {
	visit(ctx->expr());
	return 0;
}

