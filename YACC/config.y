%{
#include <stdio.h>
#include <string.h>
%}

%token NPROVAS N TITULO
%union {
	char* s;
	int i;
}

%type <s> TITULO
%type <i> NPROVAS N

%start z

%%
z: linhas '$'							{printf("Fim de ficheiro\n");}


linhas: linhas linhaC '\n'				{printf("NOVA LINHA\n");}
      | 
      ;	


linhaC: TITULO					{printf("T - %s", $1);}
      | NPROVAS 				{printf("P - %d", $1);}
      | N 						{printf("N - %d", $1);}			
      ;



%%


#include "lex.yy.c"

int yyerror() {
	fprintf(stderr,"Erro Sintatico - %s\n",yytext);
	return 0;
}

int main(){
	yyparse();
	return 0;
}



