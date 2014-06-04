%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <ctype.h>
    void yyerror(char *);
%}

%option noyywrap
%option yylineno

%%



[\t\n]					;

. 						{ printf("%c\n",*yytext); yyerror("Unknown character");  }

%%
