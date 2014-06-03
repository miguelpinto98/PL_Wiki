%{
	#include <stdio.h>
	#include <string.h>
	
	int yyerror(char *s);
    
    extern int yylex();
    extern FILE* yyin;
    extern int yylineno;
%}

%token INT STRING
%token TITULO NPROVAS NN CAMPOS

%union {
	char* s;
	int n;
}

%type <s> STRING
%type <n> INT

%start config

%%

config : config linha				{ ; }
       |
       ;	

linha : TITULO STRING				{ printf("%s\n", $2); }
       | NPROVAS INT  				{ printf("%d\n", $2); }
       | NN INT						{ printf("%d\n", $2); }
       | CAMPOS value				
       ;

value : value ';' STRING 			{ printf("%s\n", $3);}
	  | STRING 						{ printf("%s\n", $1);}
	  ;

%%

int yyerror(char *s) {
    fprintf(stderr, "%d! %s\n", yylineno, s);
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



