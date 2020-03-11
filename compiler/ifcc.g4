grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' RETURN EXPR ';' '}' ;

EXPR : TERM '+' EXPR | TERM '-' EXPR | TERM;
TERM : F '*' TERM | F '/' TERM | F;
F : CONST | '(' EXPR ')';

RETURN : 'return' ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
