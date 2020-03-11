
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"
#include <string>
using namespace std;

Visitor::Visitor(BasicBlock * bb) : ifccVisitor(), block(bb)
{

}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	block->add_instr(IRInstr1op::push, "%rbp");
	block->add_instr(IRInstr2op::movq, "%rsp", "%rbp");
	
	visit(ctx->l());
	
	string retcode = visit(ctx->val());
	
	block->add_instr(IRInstr2op::movl, retcode, "%eax");

	block->add_instr(IRInstr1op::pop, "%rbp");

	return 0;
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx){
	
	string valeur = ctx->CONST()->getText();
	string retval = "$"+valeur;
	
	return retval;
}

antlrcpp::Any Visitor::visitTextVar(ifccParser::TextVarContext *ctx){
	
	
	
	
	
	return 0;
}

antlrcpp::Any Visitor::visitTextVal(ifccParser::TextValContext *ctx){
	
	
	
	
	
	return 0;
}

antlrcpp::Any Visitor::visitL(ifccParser::LContext *ctx){
	
	
	visit(ctx->val());
	
	
	visit(ctx->var());
	
	
	visit(ctx->l());
	
	return 0;
}

antlrcpp::Any Visitor::visitDecl(ifccParser::DeclContext *ctx){
	
	
	
	
	return 0;
}
