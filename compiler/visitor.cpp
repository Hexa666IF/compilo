
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

antlrcpp::Any Visitor::visitText(ifccParser::TextContext *ctx){
	return 0;
}

antlrcpp::Any Visitor::visitL(ifccParser::LContext *ctx){
	return 0;
}

antlrcpp::Any Visitor::visitVar(ifccParser::VarContext *ctx){
	return 0;
}
