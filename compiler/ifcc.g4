grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' l RETURN val ';' '}' ;

l : 'int' decl ';' l # lDecl
  | affect ';' l # lAffect
  | /*epsilon*/ # lEpsilon
  ; 

decl : TEXT ',' decl # declMultiple
     | TEXT # declSimple
     ;

affect : var '=' val ;

var : 'int' TEXT # varDecl
    | TEXT # varText
    ;

val : CONST # valConst
    | TEXT # valText
    ;

RETURN : 'return' ;
CONST : [0-9]+ ;
TEXT : [a-z]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
