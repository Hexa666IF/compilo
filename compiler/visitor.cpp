
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"
#include <string>
#include <iostream>

using namespace std;

Visitor::Visitor(CFG * c) : ifccVisitor(), cfg(c)
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
	//string val = visit(ctx->expr());
	//string var = visit(ctx->var());
	//cfg->add_instr(IRInstr2op::ldconst, val, var);
	// TODO : compute result in the AST.
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
	// Search for symbol index into symbol table.
	string symbol = ctx->TEXT()->getText();
	return symbol;
}

antlrcpp::Any Visitor::visitValConst(ifccParser::ValConstContext *ctx)
{
	string valeur = ctx->CONST()->getText();
	return valeur;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx)
{
	// Search for symbol index into symbol table.	
	string retval = "%retval";
	string symbol = ctx->TEXT()->getText();
	int offset = cfg->get_var_index(symbol);
	cfg->add_instr(IRInstr2op::ldconst, symbol, retval);

	return retval;
}

// === Expression computation related methods ===

antlrcpp::Any Visitor::visitAdd(ifccParser::AddContext *ctx) {
	std::cout << "Adding";
	visit(ctx->term());
	visit(ctx->expr());
	// TODO : add into the AST.
	return 0;
}

antlrcpp::Any Visitor::visitSub(ifccParser::SubContext *ctx) {
	std::cout << "Subtracting";
	visit(ctx->term());
	visit(ctx->expr());
	// TODO : add into the AST.
	return 0;
}

antlrcpp::Any Visitor::visitExpr_single(ifccParser::Expr_singleContext *ctx) {
	std::cout << "Visiting Expr";
	return visit(ctx->term());
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *ctx) {
	// TODO: Add into the AST.
	return 0;
}

antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *ctx) {
	// TODO: Add into the AST.
	return 0;
}

antlrcpp::Any Visitor::visitF_single(ifccParser::F_singleContext *ctx) {
	std::cout << "Visiting F_single";
	return visit(ctx->f());
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx) {
	std::cout << "Visiting const";
	//visit(ctx->f());
	return visit(ctx->val());
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *ctx) {
	visit(ctx->expr());
	return 0;
}


