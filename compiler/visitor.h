
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"


/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccVisitor {
public:

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

  // virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override {
  //   ctx->getCONST()->getText();
  //   visitChildren(ctx);
  //   return 0;
  // }

  // virtual antlrcpp::Any visitTerm(eifccParser::TermContext *ctx) override {
  //   return 0;
  // }

  // virtual antlrcpp::Any visitF(ifccParser::FContext *ctx) override {
  //   return 0;
  // }

  virtual antlrcpp::Any visitAdd(ifccParser::AddContext *context) override;

  virtual antlrcpp::Any visitMoins(ifccParser::MoinsContext *context) override;

  virtual antlrcpp::Any visitExpr_single(ifccParser::Expr_singleContext *context) override;

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *context) override;

  virtual antlrcpp::Any visitDiv(ifccParser::DivContext *context) override;

  virtual antlrcpp::Any visitF_single(ifccParser::F_singleContext *context) override;

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *context) override;

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *context) override;

};

