
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	int retval = stoi(ctx->EXPR()->getText());
	std::cout<<".globl	main\n"
	"main: \n"
	   "pushq %rbp\n"
	   "movq %rsp, %rbp\n"
	"movl $"<<retval<<", %eax\n"
	   "popq %rbp\n"
	"ret\n";
	
	return 0;
}
