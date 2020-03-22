grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' l '}' ;

l : 'int' decl ';' l # lDecl
  | affect ';' l # lAffect
  | RETURN val ';' # return
  | /*epsilon*/ # lEpsilon
  ; 

decl : TEXT ',' decl # declMultiple
     | TEXT # declSimple
     ;

affect : var '=' expr ;

var : 'int' TEXT # varDecl
    | TEXT # varText
    ;

val : CONST # valConst
    | TEXT # valText
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

RETURN : 'return' ;
CONST : [0-9]+ ;
TEXT : [a-z]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
