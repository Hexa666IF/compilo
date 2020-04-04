
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

#include <string>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

Visitor::Visitor() : ifccVisitor()
{
	ast = new Ast();
}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
	deque<Node *> * block = visit(ctx->block());
	ast->setChilds(block);
	return 0;
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext * ctx)
{
	deque<Node *> * block = visit(ctx->l());
	return block; 
}

antlrcpp::Any Visitor::visitLDecl(ifccParser::LDeclContext *ctx)
{	
	// Declaration are 0 initialised variables.
	// That's why we still get an Assign object here.
	Assign * assign = visit(ctx->decl());
	deque<Node *> * block = visit(ctx->l());
	block->push_front(assign);

	return block;
}

antlrcpp::Any Visitor::visitLAffect(ifccParser::LAffectContext *ctx)
{
	Assign * assign = visit(ctx->affect());
	deque<Node *> * block = visit(ctx->l());
	block->push_front(assign);

	return block;
}

antlrcpp::Any Visitor::visitLCall(ifccParser::LCallContext *ctx)
{
	RValue * call = visit(ctx->call());
	ast->addNode(call);

	deque<Node *> * block = visit(ctx->l());
	block->push_front(call);
	return block;
}

antlrcpp::Any Visitor::visitReturn(ifccParser::ReturnContext *ctx)
{
	RValue * retval = visit(ctx->expr());
	Return * ret = new Return(retval, ast);
	// ast->addNode(ret);
	
	deque<Node *> * block = visit(ctx->l());
	block->push_front(ret);
	return block;
}

antlrcpp::Any Visitor::visitLIf(ifccParser::LIfContext * ctx)
{
	If * ifNode = visit(ctx->ifblock());
	deque<Node *> * block = visit(ctx->l());
	block->push_front(ifNode);

	return block;
}

antlrcpp::Any Visitor::visitLEpsilon(ifccParser::LEpsilonContext *ctx)
{
	// This deque represent the whole block we're in.
	// It will go through all the lines backwards, and will contains
	// each line representation.
	deque<Node *> * blockNodes = new deque<Node *>();
	return blockNodes;
}

antlrcpp::Any Visitor::visitIfblock(ifccParser::IfblockContext * ctx)
{
	Condition * condition = visit(ctx->condition());
	
	// the block inside the if.
	deque<Node *> * ifBlock = visit(ctx->block());
	If * ifNode = new If(condition, ifBlock);

	return ifNode;
}

antlrcpp::Any Visitor::visitCondition(ifccParser::ConditionContext * ctx)
{
	static const string operators [] = { "<", "<=", ">", ">=", "==" };
	static const Condition::Comparison types [] = { 
			Condition::Comparison::lt, 
			Condition::Comparison::le, 
			Condition::Comparison::gt, 
			Condition::Comparison::ge, 
			Condition::Comparison::eq 
	};
	RValue * left = visit(ctx->expr(0));
	RValue * right = visit(ctx->expr(1));
	string str_comp = ctx->COMPARISON()->getText();
	unsigned int i = 0;
	while(i < 5 && str_comp != operators[i])
		++i;

	Condition * cond = new Condition(left, types[i], right);
	return cond;
}

antlrcpp::Any Visitor::visitDeclMultiple(ifccParser::DeclMultipleContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	ast->addSymbol(symbol);

	// Is the initialisation here a good idea ?
	Variable * variable = new Variable(symbol, ast);
	Assign * assign = new Assign(variable, new Constant(0, ast), ast);
	visit(ctx->decl());
	
	return assign;
}

antlrcpp::Any Visitor::visitDeclSimple(ifccParser::DeclSimpleContext *ctx)
{
	string symbol = ctx->TEXT()->getText();
	ast->addSymbol(symbol);
	Variable * variable = new Variable(symbol, ast);
	Assign * assign = new Assign(variable, new Constant(0, ast), ast);
	// ast->addNode(assign);
	
	return assign;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx)
{
	Variable * var = visit(ctx->var());	
	Assign * assign = new Assign(var, visit(ctx->expr()), ast);
	// ast->addNode(assign);

	return assign;
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

antlrcpp::Any Visitor::visitValCall(ifccParser::ValCallContext *ctx)
{
	RValue * call = visit(ctx->call());

	return call;
}

antlrcpp::Any Visitor::visitCallParam(ifccParser::CallParamContext *ctx)
{
	string name = ctx->TEXT()->getText();
	vector<RValue *> args = visit(ctx->param());
	RValue * function = new FunctionCall(name, args, ast);

	return function;
}

antlrcpp::Any Visitor::visitCallNoParam(ifccParser::CallNoParamContext *ctx)
{
	string name = ctx->TEXT()->getText();
	vector<RValue *> args;
	RValue * function = new FunctionCall(name, args, ast);

	return function;
}

antlrcpp::Any Visitor::visitParamSimple(ifccParser::ParamSimpleContext *ctx)
{
	vector<RValue *> args;
	args.insert(args.begin(), 1, visit(ctx->expr()));

	return args;
}

antlrcpp::Any Visitor::visitParamMultiple(ifccParser::ParamMultipleContext *ctx)
{
	vector<RValue *> args = visit(ctx->param());
	args.insert(args.begin(), 1, visit(ctx->expr()));
	return args;
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

