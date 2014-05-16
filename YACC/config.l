%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <ctype.h>
    void yyerror(char *);
%}

%option noyywrap
%option yylineno

%%

"=titulo="				{ return TITULO; }

"=nprovas="				{ return NPROVAS; }

"=N="					{ return NN; }

[ a-zA-Z0-9]+ {
	//printf("%c\n",yytext[1] ); 
	if(isdigit(yytext[1])!=0) {
		yylval.n = atoi(yytext);
		return INT;
	} else {
		yylval.s=strdup(yytext+1); 
		return STRING;
	}
}

[\t\n]					;

. 						{ yyerror("Unknown character"); }

%%