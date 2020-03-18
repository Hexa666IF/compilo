grammar ifcc;

axiom : prog;

prog : 'int' 'main' '(' ')' '{' RETURN expr ';' '}' ;

expr : term '+' expr # add
    | term '-' expr # moins
    | term # expr_single
    ;
term : f '*' term # mult
    | f '/' term # div
    | f # f_single
    ;
f : CONST # const
    | '(' expr ')' # par
    ;

RETURN : 'return' ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);