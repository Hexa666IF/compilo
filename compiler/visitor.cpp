
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

#include <string>
#include <iostream>

using namespace std;

Visitor::Visitor() : ifccVisitor()
{
	ast = new Ast();
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
	RValue * retval = visit(ctx->expr());
	Return * ret = new Return(retval, ast);
	ast->addNode(ret);

	return 0;
}

antlrcpp::Any Visitor::visitLEpsilon(ifccParser::LEpsilonContext *ctx)
{
	return 0;
}

antlrcpp::Any Visitor::visitDeclMultiple(ifccParser::DeclMultipleContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	ast->addSymbol(symbol);
	visit(ctx->decl());

	return 0;
}

antlrcpp::Any Visitor::visitDeclSimple(ifccParser::DeclSimpleContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	ast->addSymbol(symbol);
	Variable * variable = new Variable(symbol, ast);
	Assign * assign = new Assign(variable, new Constant(0, ast), ast);
	ast->addNode(assign);
	
	return 0;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx)
{
	Variable * var = visit(ctx->var());	
	Assign * assign = new Assign(var, visit(ctx->expr()), ast);
	ast->addNode(assign);

	return 0;
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	ast->addSymbol(symbol);
	Variable * variable = new Variable(symbol, ast);
	
	return variable;
}

antlrcpp::Any Visitor::visitVarText(ifccParser::VarTextContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	Variable * variable = new Variable(symbol, ast);
	
	return variable;
}

antlrcpp::Any Visitor::visitValConst(ifccParser::ValConstContext *ctx)
{
	string val = ctx->CONST()->getText();
	RValue * constant = new Constant(val, ast);
	
	return constant;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	RValue * variable = new Variable(symbol, ast);
	
	return variable;
}

// === Expression computation related methods ===

antlrcpp::Any Visitor::visitAdd(ifccParser::AddContext *ctx) 
{
	RValue * left = visit(ctx->term());
	RValue * right = visit(ctx->expr());
	RValue * add = new Operation(IRInstr3op::add, left, right, ast);
	
	return add;
}

antlrcpp::Any Visitor::visitSub(ifccParser::SubContext *ctx) 
{
	RValue * left = visit(ctx->term());
	RValue * right = visit(ctx->expr());
	RValue * sub = new Operation(IRInstr3op::sub, left, right, ast);
	
	return sub;
}

antlrcpp::Any Visitor::visitExpr_single(ifccParser::Expr_singleContext *ctx) 
{	
	RValue * op = visit(ctx->term());
	return op;
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *ctx) 
{
	RValue * left = visit(ctx->f());
	RValue * right = visit(ctx->term());
	RValue * mul = new Operation(IRInstr3op::mul, left, right, ast); 
	
	return mul;
}

antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *ctx) 
{
	// Division is not part of the requirements.
	// We'll handle it later maybe.
	return 0;
}

antlrcpp::Any Visitor::visitF_single(ifccParser::F_singleContext *ctx) 
{
	RValue * rvalue = visit(ctx->f());
	return rvalue;
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx) 
{
	RValue * rvalue = visit(ctx->val());	
	return rvalue;
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *ctx) 
{
	RValue * op = visit(ctx->expr());
	
	return op;
}

Ast * Visitor::getAst() const
{
	return ast;
}

