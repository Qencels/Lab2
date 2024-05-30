lexer grammar TLexer;

INT : [0-9]+;
WS  : [ \t\r]+ -> skip;
NL  : '\n';

PLUS   : '+';
MINUS  : '-';
MULT   : '*';
DIV    : '/';
POPEN  : '(';
PCLOSE : ')';
POW    : '^';
EQ     : '=';

VAR    : [xyz];
USERVAR: [A-Z]+;

PRINT  : 'print';
CALCULATE : 'calculate';
