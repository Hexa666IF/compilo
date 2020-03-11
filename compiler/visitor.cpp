
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"
#include <string>
using namespace std;

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){
	
	std::cout<<".globl	main\n"
	"main: \n"
	"pushq %rbp\n"
	"movq %rsp, %rbp\n";
	
	visit(ctx->l());
	
	std::cout<<"movl ";

	visit(ctx->val());

	std::cout<<", %eax\n"
	"popq %rbp\n"
	"ret\n";
	
	return 0;
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx){
	
	int retval = stoi(ctx->CONST()->getText());
	std::cout<<"$"<<retval;
	
	return 0;
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
