OUTPUT=output
GENERATED=antlr4-generated
GRAMMAR=ifcc.g4

#override with your local installation
ANTLR4_BINDIR=/shares/public/tp/ANTLR4-CPP/bin
ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

all: ifcc

ifcc: dirs antlr  main.cpp visitor.cpp visitor.h IR.cpp IR.h
	$(CC) $(CCARGS) main.cpp  -o $(OUTPUT)/main.o 
	$(CC) $(CCARGS) IR.cpp -o $(OUTPUT)/IR.o
	$(CC) $(CCARGS) Asmx86.cpp -o $(OUTPUT)/Asmx86.o
	$(CC) $(CCARGS) AsmARM.cpp -o $(OUTPUT)/AsmARM.o
	$(CC) $(CCARGS) ArgProcessor.cpp -o $(OUTPUT)/ArgProcessor.o
	$(CC) $(CCARGS) AsmMSP430.cpp -o $(OUTPUT)/AsmMSP430.o
	$(CC) $(CCARGS) Ast.cpp -o $(OUTPUT)/Ast.o
	$(CC) $(CCARGS) Errors.cpp -o $(OUTPUT)/Errors.o
	$(CC) $(CCARGS) $(GENERATED)/ifccBaseVisitor.cpp -o $(OUTPUT)/ifccBaseVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccLexer.cpp -o $(OUTPUT)/ifccLexer.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccVisitor.cpp -o $(OUTPUT)/ifccVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccParser.cpp -o $(OUTPUT)/ifccParser.o 
	$(CC) $(CCARGS) visitor.cpp -o $(OUTPUT)/visitor.o 
	$(CC) $(LDARGS) $(OUTPUT)/main.o $(OUTPUT)/IR.o $(OUTPUT)/Asmx86.o $(OUTPUT)/AsmARM.o $(OUTPUT)/AsmMSP430.o $(OUTPUT)/ArgProcessor.o $(OUTPUT)/Ast.o $(OUTPUT)/Errors.o $(OUTPUT)/ifccBaseVisitor.o $(OUTPUT)/ifccLexer.o $(OUTPUT)/ifccVisitor.o $(OUTPUT)/ifccParser.o $(OUTPUT)/visitor.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT) 
	mkdir -p $(GENERATED) 

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
