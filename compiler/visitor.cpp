
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

using namespace std;

Visitor::Visitor(CFG * c) : ifccVisitor(), cfg(c)
{

}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	int retval = stoi(ctx->CONST()->getText());

	cfg->add_instr(IRInstr1op::push, "%rbp");
	cfg->add_instr(IRInstr2op::movq, "%rsp", "%rbp");
	string retcode = "$" + to_string(retval);
	cfg->add_instr(IRInstr2op::movl, retcode, "%eax");
	cfg->add_instr(IRInstr1op::pop, "%rbp");

	return 0;
}
