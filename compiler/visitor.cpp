
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	std::string retval = visit(ctx->expr());
	std::cout<<".globl	main\n"
	"main: \n"
	   "pushq %rbp\n"
	   "movq %rsp, %rbp\n"
	"movl "<<retval<<", %eax\n"
	   "popq %rbp\n"
	"ret\n";
	
	return 0;
}

antlrcpp::Any Visitor::visitAdd(ifccParser::AddContext *ctx) {
	std::cout << "Adding";
	visit(ctx->term());
	visit(ctx->expr());
	return 0;
}

antlrcpp::Any Visitor::visitMoins(ifccParser::MoinsContext *ctx) {
	std::cout << "Subtracting";
	visit(ctx->term());
	visit(ctx->expr());
	return 0;
}

antlrcpp::Any Visitor::visitExpr_single(ifccParser::Expr_singleContext *ctx) {
	std::cout << "Visiting Expr";
	return visit(ctx->term());
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *ctx) {
	return 0;
}

antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *ctx) {
	return 0;
}

antlrcpp::Any Visitor::visitF_single(ifccParser::F_singleContext *ctx) {
	std::cout << "Visiting F_single";
	return visit(ctx->f());
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx) {
	std::cout << "Visiting const";
	// visit(ctx->f());
	return ("$"+ctx->CONST()->getText());
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *ctx) {
	return 0;
}