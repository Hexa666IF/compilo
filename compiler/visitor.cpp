
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"
#include <string>
#include <iostream>

using namespace std;

Visitor::Visitor(CFG * c) : ifccVisitor(), cfg(c)
{

}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	visit(ctx->l());
	return 0;
}

antlrcpp::Any Visitor::visitLDecl(ifccParser::LDeclContext *ctx){
	
	visit(ctx->decl());
	visit(ctx->l());

	return 0;
}

antlrcpp::Any Visitor::visitLAffect(ifccParser::LAffectContext *ctx){

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

antlrcpp::Any Visitor::visitLEpsilon(ifccParser::LEpsilonContext *ctx){
	return 0;
}

antlrcpp::Any Visitor::visitDeclMultiple(ifccParser::DeclMultipleContext *ctx){

	// Add symbol name to symbol table.
	string symbol = ctx->TEXT()->getText();

	cfg->add_to_symbol_table(symbol);
	visit(ctx->decl());

	return 0;
}

antlrcpp::Any Visitor::visitDeclSimple(ifccParser::DeclSimpleContext *ctx){

	// Add symbol name to symbol table.
	string symbol = ctx->TEXT()->getText();
	cfg->add_to_symbol_table(symbol);
	return 0;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx){

	string val = visit(ctx->val());
	string var = visit(ctx->var());

	cfg->add_instr(IRInstr2op::ldconst, val, var);

	return 0;
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *ctx){

	// Add symbol name to symbol table.
	string symbol = ctx->TEXT()->getText();
	cfg->add_to_symbol_table(symbol);
	return symbol;
}

antlrcpp::Any Visitor::visitVarText(ifccParser::VarTextContext *ctx){

	// Search for symbol index into symbol table.
	string symbol = ctx->TEXT()->getText();
	return symbol;
}

antlrcpp::Any Visitor::visitValConst(ifccParser::ValConstContext *ctx){

	string valeur = ctx->CONST()->getText();
	return valeur;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx){

	// Search for symbol index into symbol table.
	string symbol = ctx->TEXT()->getText();
	int offset = cfg->get_var_index(symbol);

	cfg->add_instr(IRInstr2op::ldconst, symbol, "%retval");

	string retval = "%retval";

	return retval;
}
