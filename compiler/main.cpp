#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"
#include "Errors.h"
#include "ArgProcessor.h"
#include "IR.h"

using namespace antlr4;
using namespace std;


int main(int argn, const char **argv) {
	int ret = 0;
	stringstream in;
	// process arguments
	ArgProcessor argProc(argn, argv);
	// read file
	ifstream lecture(ArgProcessor::getArg("file_path"));
	in << lecture.rdbuf();

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

	Visitor visitor;

	try
	{
		visitor.visit(tree);
	}
	catch(ErrorCode e)
	{
  		Errors::printErrors();
		return e; 
	}

	//const unordered_set<string> & unuseds = visitor.getAst()->getUnuseds();
	//for(string var : unuseds)
	//		cerr << "WARNING : " << var << " is declared but never used." << endl;

	Ast * ast = visitor.getAst();
	vector<CFG *> * graphs = ast->gen_instr();
	for(CFG * cfg : * graphs)
		cfg->gen_asm();
	
	// errorFree <=> 0.
	return errorFree;
}
