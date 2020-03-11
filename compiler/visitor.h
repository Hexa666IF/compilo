
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
  
  virtual antlrcpp::Any visitL(ifccParser::LContext *ctx) override;
  
  virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;
  
  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;

  virtual antlrcpp::Any visitText(ifccParser::TextContext *ctx) override;
  
};

