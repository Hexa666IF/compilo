#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv) {
  int ret = 0;
  stringstream in;
  if (argn==2) {
     ifstream lecture(argv[1]);
     in << lecture.rdbuf();
  }
  ANTLRInputStream input(in.str());
  ifccLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
//  for (auto token : tokens.getTokens()) {
//    std::cout << token->toString() << std::endl;
//  }

  if(lexer.getNumberOfSyntaxErrors() != 0)
  {
	cout << "Error during lexer operation... ! " << endl;
	return lexer.getNumberOfSyntaxErrors();
  }

  ifccParser parser(&tokens);
  tree::ParseTree* tree = parser.axiom();
  
  if(parser.getNumberOfSyntaxErrors() != 0) 
  {
	cout << "Error during parsing operation... ! " << endl;
	return parser.getNumberOfSyntaxErrors();
  }
  Visitor visitor;
  visitor.visit(tree);
  
  return 0;
}
