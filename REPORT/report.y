%{
	#include <stdio.h>
	#include <string.h>
	#include "linkedlist/linkedlist.h"
	#include "struct.h"
	
	int yyerror(char *s);
    
    extern int yylex();
    extern FILE* yyin;
    extern int yylineno;

    LinkedList authors = NULL;
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

%token BEGINBODY ENDBODY BEGINCHAP ENDCHAP BEGINSEC ENDSEC BEGINPARA ENDPARA
%token BEGINFOOT ENDFOOT BEGINREF ENDREF BEGINXREF ENDXREF BEGINCIT ENDCIT BEGINITERM ENDITERM
%token BEGINBOLD ENDBOLD BEGINITALIC ENDITALIC BEGINUNDERLINE ENDUNDERLINE

%token BEGINFIG ENDFIG BEGINGRAPH ENDGRAPH BEGINCAPTION ENDCAPTION BEGINPATH ENDPATH BEGINFORMAT ENDFORMAT 
%token BEGINTABLE ENDTABLE BEGINDATA ENDDATA BEGINROW ENDROW

%token BEGINLIST ENDLIST BEGINSUM ENDSUM BEGINCODE ENDCODE
%token BEGINBM ENDBM

%union {
	char* s;
}

%type<s> texto
%type<s> Line
%type<s> ParaList 

%%

Report : BEGINREPORT FrontMatter Body BackMatter ENDREPORT
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
Keywords : BEGINKEYWORD ParaList ENDKEYWORD
		 |
		 ;

ParaList : ParaList Line	
		 | Line		
		 ;

Line : texto	{printf("X - %s\n",$1 );}
	 ;
/* END - PALAVRAS CHAVE */ 

/* BEGIN - RESUMO */
Abstract : BEGINABS ParaList ENDABS
		 ;

/* BEGIN AGRADECIMENTOS */
Aknowledgements : BEGINAKN ParaList ENDAKN 
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
/* BEGIN - BODY */	
Body : BEGINBODY ChapterList ENDBODY
	 ;

ChapterList : ChapterList Chapter
            | Chapter
            ;

Chapter : BEGINCHAP Title ElemList ENDCHAP
		;

ElemList : ElemList Elem
		 | Elem
		 ;

Elem : Paragraph
	 | Float
	 | List
	 | CodeBlock
	 | Section
	 | Summary 
	 ;

Paragraph : BEGINPARA ParaContent ENDPARA
		  ;

ParaContent : ParaContent texto				{printf("PARA: %s\n",$2 );}
			| ParaContent FreeElement
			|
			;

FreeElement : Footnote 
			| Ref
			| Xref
			| Citref
			| Iterm
			| Bold
			| Italic
			| Underline
//			| InlineCode
//			| Acronym
			;

Footnote : BEGINFOOT texto ENDFOOT
		 ;

Ref : BEGINREF texto ENDREF 		{printf("%s\n",$2 );}
	;

Xref : BEGINXREF texto ENDXREF
	 ;

Citref : BEGINCIT texto ENDCIT
	   ;

Iterm : BEGINITERM texto ENDITERM
	  ;

Bold : BEGINBOLD BContent ENDBOLD
	 ;

BContent : BContent texto
		 | BContent Italic
		 | BContent Underline
		 |
		 ;

Italic : BEGINITALIC IContent ENDITALIC
	   ;

IContent : IContent texto
		 | IContent Bold
		 | IContent Underline
		 |
		 ;

Underline : BEGINUNDERLINE UContent ENDUNDERLINE
		  ;

UContent : UContent texto
		 | UContent Bold
		 | UContent Italic
		 |
		 ;

Float : Figure
	  | Table
	  ;

Figure : BEGINFIG Graphic Caption ENDFIG
	   ;

Graphic : BEGINGRAPH Path Format ENDGRAPH
		;

Path : BEGINPATH texto ENDPATH 
	 ;

Format : BEGINFORMAT texto ENDFORMAT
	   ;

Caption : BEGINCAPTION texto ENDCAPTION
		;

Table : BEGINTABLE Caption TRowList ENDTABLE
	  ;

TRowList : TRowList TRow
		 | TRow
		 ;

TRow : BEGINROW ListData ENDROW
	 ;

ListData : ListData Data
	  	 | Data
	  	 ;

Data : BEGINDATA texto ENDDATA
	 ;

Summary : BEGINSUM texto ENDSUM
		;

List : BEGINLIST ParaList ENDLIST
	 ;

CodeBlock : BEGINCODE ParaList ENDCODE
		  ;

Section : BEGINSEC Title ParaList ENDSEC
		;


/* END - BODY */

/* BEGIN - BM */
BackMatter : BEGINBM texto ENDBM
		   ;

/* END - BM */
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
