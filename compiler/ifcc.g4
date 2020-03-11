grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' l RETURN val ';' '}' ;

l : var '=' val ';' l 
  | /*epsilon*/ 
  ; 

var : 'int' TEXT 
    | TEXT 
    ;

val : CONST # const
    | TEXT # text
    ;


RETURN : 'return' ;
CONST : [0-9]+ ;
TEXT : [a-z]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
