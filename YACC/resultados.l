%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <ctype.h>
    void yyerror(char *);
%}

%option noyywrap
%option yylineno

%%

[a-zA-Z]+				{ return ESTADO; }

[0-9]

[\t\n]					;

. 						{ printf("%c\n",*yytext); yyerror("Unknown character");  }

%%