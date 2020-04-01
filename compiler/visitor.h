
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"

#include <map>

#include "IR.h"
#include "Ast.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor
{
public:
    Visitor();

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

   
  virtual antlrcpp::Any visitLDecl(ifccParser::LDeclContext *ctx) override;

  virtual antlrcpp::Any visitLAffect(ifccParser::LAffectContext *ctx) override;

  virtual antlrcpp::Any visitReturn(ifccParser::ReturnContext *context) override;

  virtual antlrcpp::Any visitLEpsilon(ifccParser::LEpsilonContext *ctx) override;

  virtual antlrcpp::Any visitDeclMultiple(ifccParser::DeclMultipleContext *ctx) override;

  virtual antlrcpp::Any visitDeclSimple(ifccParser::DeclSimpleContext *ctx) override;

  virtual antlrcpp::Any visitAffect(ifccParser::AffectContext *ctx) override;

  virtual antlrcpp::Any visitVarDecl(ifccParser::VarDeclContext *ctx) override;

  virtual antlrcpp::Any visitVarText(ifccParser::VarTextContext *ctx) override;

  virtual antlrcpp::Any visitValConst(ifccParser::ValConstContext *ctx) override;

  virtual antlrcpp::Any visitValText(ifccParser::ValTextContext *ctx) override;

// === Expression computation related methods ===

  virtual antlrcpp::Any visitAdd(ifccParser::AddContext *context) override;

  virtual antlrcpp::Any visitSub(ifccParser::SubContext *context) override;

  virtual antlrcpp::Any visitExpr_single(ifccParser::Expr_singleContext *context) override;

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *context) override;

  virtual antlrcpp::Any visitDiv(ifccParser::DivContext *context) override;

  virtual antlrcpp::Any visitF_single(ifccParser::F_singleContext *context) override;

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *context) override;

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *context) override;


	Ast * getAst() const;

protected:
  
	// Abstract Syntax Tree.
	// This is the semantic representation of the program
	// parsed by the visitor.
	Ast * ast;
};
