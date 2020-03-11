
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"
#include <string>
#include <iostream>

using namespace std;

Visitor::Visitor(BasicBlock * bb) : ifccVisitor(), block(bb)
{

}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){

	cout << "coucou";

	block->add_instr(IRInstr1op::push, "%rbp");
	block->add_instr(IRInstr2op::movq, "%rsp", "%rbp");
	
	visit(ctx->l());
	
	string retcode = visit(ctx->val());
	
	if(retcode[0] == '$'){
		block->add_instr(IRInstr2op::movl, retcode, "%eax");
	}

	block->add_instr(IRInstr1op::pop, "%rbp");

	return 0;
}

antlrcpp::Any Visitor::visitLDecl(ifccParser::LDeclContext *ctx){
	
	visit(ctx->decl());
	visit(ctx->l());

	return 0;
}

antlrcpp::Any Visitor::visitLAffect(ifccParser::LAffectContext *ctx){

	visit(ctx->affect());
	visit(ctx->l());

	return 0;
}

antlrcpp::Any Visitor::visitLEpsilon(ifccParser::LEpsilonContext *ctx){
	return 0;
}

antlrcpp::Any Visitor::visitDeclMultiple(ifccParser::DeclMultipleContext *ctx){

	//Ajout du symbole dans la table
	string symbole = ctx->TEXT()->getText();
	int offset = (symboles.size()+1)*(-4);

	symboles.insert(pair<string, int>(symbole, offset));

	visit(ctx->decl());

	return 0;
}

antlrcpp::Any Visitor::visitDeclSimple(ifccParser::DeclSimpleContext *ctx){

	//Ajout du symbole dans la table
	string symbole = ctx->TEXT()->getText();
	int offset = (symboles.size()+1)*(-4);

	symboles.insert(pair<string, int>(symbole, offset));

	return 0;
}

antlrcpp::Any Visitor::visitAffect(ifccParser::AffectContext *ctx){

	string val = visit(ctx->val());
	string var = visit(ctx->var());

	block->add_instr(IRInstr2op::movl, val, var);

	return 0;
}

antlrcpp::Any Visitor::visitVarDecl(ifccParser::VarDeclContext *ctx){

	//Ajout du symbole dans la table
	string symbole = ctx->TEXT()->getText();
	int offset = (symboles.size()+1)*(-4);

	symboles.insert(pair<string, int>(symbole, offset));

	return to_string(offset) + "(%rbp)";
}

antlrcpp::Any Visitor::visitVarText(ifccParser::VarTextContext *ctx){

	//Recherche de l'offset dans la table des symboles
	string symbole = ctx->TEXT()->getText();
	int offset = symboles.find(symbole) -> second;

	return to_string(offset) + "(%rbp)";
}

antlrcpp::Any Visitor::visitValConst(ifccParser::ValConstContext *ctx){

	string valeur = ctx->CONST()->getText();
	string retval = "$"+valeur;
	
	return retval;
}

antlrcpp::Any Visitor::visitValText(ifccParser::ValTextContext *ctx){

	//Recherche de l'offset dans la table des symboles
	string symbole = ctx->TEXT()->getText();
	int offset = symboles.find(symbole) -> second;

	string valText = to_string(offset) + "(%rbp)";

	block->add_instr(IRInstr2op::movl, valText, "%eax");

	return "%eax";
}