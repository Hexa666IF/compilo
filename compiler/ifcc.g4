grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' L RETURN VAL ';' '}' ;

L : VAR = VAL ; L | */epsilon*/ ;

VAR : int TEXT | TEXT ;

VAL : CONST | TEXT ;


RETURN : 'return' ;
CONST : [0-9]+ ;
TEXT : [a-z]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
