
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

using namespace std;

Visitor::Visitor(BasicBlock * bb) : ifccVisitor(), block(bb)
{

}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	int retval = stoi(ctx->CONST()->getText());

	block->add_instr(IRInstr1op::push, "%rbp");
	block->add_instr(IRInstr2op::movq, "%rsp", "%rbp");
	string retcode = "$" + to_string(retval);
	block->add_instr(IRInstr2op::movl, retcode, "%eax");
	block->add_instr(IRInstr1op::pop, "%rbp");

	return 0;
}
