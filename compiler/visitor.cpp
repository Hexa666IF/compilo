
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
	
	//visit(ctx->l());
	
	string retcode = visit(ctx->val());
	
	block->add_instr(IRInstr2op::movl, retcode, "%eax");

	block->add_instr(IRInstr1op::pop, "%rbp");

	return 0;
}

antlrcpp::Any Visitor::visitLDecl(ifccParser::LDeclContext *ctx){
	
	return 0;
}

antlrcpp::Any Visitor::visitLAffect(ifccParser::LAffectContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitLEpsilon(ifccParser::LEpsilonContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitDeclMultiple(ifccParser::DeclMultipleContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitDeclSimple(ifccParser::DeclSimpleContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitVarText(ifccParser::VarTextContext *ctx){

	return 0;
}

antlrcpp::Any Visitor::visitValConst(ifccParser::ValConstContext *ctx){

	string valeur = ctx->CONST()->getText();
	string retval = '$'+valeur;
	
	return retval;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx){

	return 0;
}