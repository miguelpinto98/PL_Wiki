%{
	#include <stdio.h>
	#include <string.h>
	
	int yyerror(char *s);
    
    extern FILE* yyin;
    extern int yylineno;
%}

%token INT STRING
%token TITULO NPROVAS NN

%union {
	char* s;
	int i;
}

%type <s> STRING
%type <i> INT

%start z

%%
z: linhas '$'						{ printf("Fim de ficheiro\n"); }

linhas : linhas linhaC '\n'			{ printf("Linha ABC\n"); }
       | 
       ;	

linhaC : TITULO STRING				{printf("T - %s", $2);}
       | NPROVAS INT  				{printf("P - %d", $2);}
       | NN INT						{printf("N - %d", $2);}	
       | STRING 						
       | INT 						
       ;

%%

int yyerror(char *s) {
    fprintf(stderr, "! %s\n", s);
    return 0;
}

int main(){
	FILE *file = fopen("exemplo.txt", "r");
	
	if(file) {
		yyin = file;
		yyparse();
	}
	return 0;
}



