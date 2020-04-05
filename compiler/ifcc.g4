grammar ifcc;

axiom : prog;

prog : function prog #progFunction
	 | /*epsilon*/ #progEpsilon
	 ;

function : 'int' TEXT '(' ')' block;

block : '{' l '}' ;

l : 'int' decl ';' l # lDecl
  | affect ';' l # lAffect
  | call ';' l #lCall
  | RETURN expr ';' l # return
  | ifblock l # lIf
  | whileblock l # lWhile
  | /*epsilon*/ # lEpsilon
  ; 

whileblock : 'while' '(' condition ')' block;

ifblock : 'if' '(' condition ')' block # ifBlock
        | 'if' '(' condition ')' block 'else' block # ifElseBlock;

condition : expr COMPARISON expr;

decl : TEXT ',' decl # declMultiple
     | TEXT # declSimple
     ;

affect : var '=' expr 
    ;

var : 'int' TEXT # varDecl
    | TEXT # varText
    ;

val : CONST # valConst
    | TEXT # valText
    | call # valCall
    ;

expr : term '+' expr # add
    | term '-' expr # sub
    | term # expr_single
    ;

term : f '*' term # mult
    | f '/' term # div
    | f # f_single
    ;

f : val # const
    | '(' expr ')' # par
	;

call : TEXT '(' ')' # callNoParam
     | TEXT '(' param ')' # callParam
     ;

param : expr ',' param # paramMultiple
      | expr # paramSimple
      ;

RETURN : 'return' ;
CONST : [0-9]+ ;
TEXT : [a-z]+ ;
COMPARISON : '>' | '>=' | '<' | '<=' | '==';
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
