#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"
// #include "Errors.h"

#include "IR.h"

using namespace antlr4;
using namespace std;


int main(int argn, const char **argv) {
	int ret = 0;
	std::string asm_choice = "-x86";
	stringstream in;
	if (argn>=2) {
		int pathIndex = 1;
		if (argn==3) {
			pathIndex = 2;
			asm_choice = argv[1];
		}
		ifstream lecture(argv[pathIndex]);
		in << lecture.rdbuf();

	}
	ANTLRInputStream input(in.str());
	ifccLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	tokens.fill();
//	for (auto token : tokens.getTokens()) {
//		std::cout << token->toString() << std::endl;
//	}

	if(lexer.getNumberOfSyntaxErrors() != 0)
	{
		cout << "Error during lexer operation... ! " << endl;
		return lexerSyntaxError;
	}

	ifccParser parser(&tokens);
	tree::ParseTree* tree = parser.axiom();

	if(parser.getNumberOfSyntaxErrors() != 0) 
	{
		cout << "Error during parsing operation... ! " << endl;
		return parserSyntaxError;
	}

	CFG * cfg = new CFG(nullptr, asm_choice);
	Visitor visitor(cfg);

	try
	{
		visitor.visit(tree);
	}
	catch(ErrorCode e)
	{
  		Errors::printErrors();
		return e; 
	}

	cfg->warningsUnusedVar();
	cfg->gen_asm();
	
	// errorFree <=> 0.
	return errorFree;
}
