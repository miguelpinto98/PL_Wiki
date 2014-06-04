%{
	#include <stdio.h>
	#include <string.h>
	
	int yyerror(char *s);
    
    extern int yylex();
    extern FILE* yyin;
    extern int yylineno;
%}

%token texto

%token BEGINREPORT ENDREPORT
%token BEGINFM ENDFM BEGINTITLE ENDTITLE BEGINSUBTITLE ENDSUBTITLE
%token BEGINDATE ENDDATE BEGININSTITUTION ENDINSTITUTION 

%token BEGINAUTHOR ENDAUTHOR 
%token BEGINNAME ENDNAME BEGINNID ENDNID BEGINEMAIL ENDEMAIL BEGINURL ENDURL BEGINAFFILIATION ENDAFFILIATION

%token BEGINKEYWORD ENDKEYWORD
%token BEGINABS ENDABS
%token BEGINAKN ENDAKN
%token ICONTENT IFIGURE ITABLE

%union {
	char* s;
}

%type<s> texto
%type<s> Line
%type<s> ParaList 

%%

Report : BEGINREPORT FrontMatter ENDREPORT
	   ;

FrontMatter : BEGINFM Title SubTitle Authors Date Institution Keywords Abstract Aknowledgements Toc Lof Lot ENDFM
			;

/* BEGIN - FRONTMATTER */
Title : BEGINTITLE texto ENDTITLE { printf("Titulo: %s\n", $2); }
	  ;

SubTitle : BEGINSUBTITLE texto ENDSUBTITLE { printf("Sub Titulo: %s\n", $2); }
		 |
		 ;

Authors : Authors Author
		| Author
		;

/* BEGIN - Dados Autor */
Author : BEGINAUTHOR Name Nident Email Url Affiliation ENDAUTHOR
	   ;

Name : BEGINNAME texto ENDNAME	{printf("Autor Nome: %s\n", $2);}
	 ;

Nident : BEGINNID texto ENDNID	{printf("Autor ID: %s\n", $2);}
	 |
	 ;

Email : BEGINEMAIL texto ENDEMAIL {printf("Autor EMAIL: %s\n", $2);}
	  |
	  ;

Url : BEGINURL texto ENDURL {printf("Autor URL: %s\n", $2);}
	|
	;

Affiliation : BEGINAFFILIATION texto ENDAFFILIATION {printf("Autor Affiliation: %s\n", $2);}
			|
			;
/* END - Dados Autor */

Date : BEGINDATE texto ENDDATE	{ printf("Data: %s\n", $2);}
	 ;

Institution : BEGININSTITUTION texto ENDINSTITUTION  {printf("Inst: %s\n", $2);}
			|
			;

/* BEGIN - PALAVRAS CHAVE */
Keywords : BEGINKEYWORD ParaList ENDKEYWORD {printf("KEY: %s\n",$2);}
		 |
		 ;

ParaList : ParaList Line	{ $$ = $2; }
		 | Line		{$$ = $1; }
		 ;

Line : texto	{ $$ = $1; }
	 ;
/* END - PALAVRAS CHAVE */ 

/* BEGIN - RESUMO */
Abstract : BEGINABS ParaList ENDABS {printf("ABS %s\n", $2);}
		 ;

/* BEGIN AGRADECIMENTOS */
Aknowledgements : BEGINAKN ParaList ENDAKN {printf("Thankz: %s\n",$2 );}
				|
				;

Toc : ICONTENT
	|
	;

Lof : IFIGURE
	|
	;

Lot : ITABLE
	|
	;

/* END - FRONTMATTER */

%%

int yyerror(char *s) {
    fprintf(stderr, "%d! %s\n", yylineno, s);
    return 0;
}

int main(){
	FILE *file = fopen("exemplo1.txt", "r");
	
	if(file) {
		yyin = file;
		yyparse();
	}
	return 0;
}
