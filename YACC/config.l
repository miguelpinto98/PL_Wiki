%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <ctype.h>
    void yyerror(char *);
%}

%option noyywrap
%option yylineno

%%

=titulo=				{ return TITULO; }

=nprovas=				{ return NPROVAS; }

=N=					{ return NN; }

[ a-zA-Z0-9]+				{ 	if(isdigit(atoi(yytext))==0) {
									yylval.s = strdup(yytext);
									return STRING;
								} else {
							  		yylval.i = atoi(yytext);
							  		return INT;
								}
							}

\n 						BEGIN INITIAL;

. 						{ yyerror("Unknown character"); }

%%