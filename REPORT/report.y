%{
	#include <stdio.h>
	#include <string.h>
	#include "linkedlist/linkedlist.h"
	#include "structs.h"
	
	int yyerror(char *s);
    
    extern int yylex();
    extern FILE* yyin;
    extern int yylineno;

    LinkedList la = NULL;
    LinkedList lp = NULL;
    LinkedList lc = NULL;

    Autor a = NULL;
    Report r = NULL;
    Paragrafo p = NULL;
    Elemento e = NULL;
    Capitulo c = NULL;
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
%type<s> Title;

%%

Report : BEGINREPORT FrontMatter Body BackMatter ENDREPORT
	   ;

FrontMatter : BEGINFM Title SubTitle Authors Date Institution Keywords Abstract Aknowledgements Toc Lof Lot ENDFM
			  { adicionaTitulo(r,$2); lp = createLinkedList(NULL,NULL); }
			;

/* BEGIN - FRONTMATTER */
Title : BEGINTITLE texto ENDTITLE 		{ $$=$2; }
	  ;

SubTitle : BEGINSUBTITLE texto ENDSUBTITLE	{ adicionaSubTitulo(r,$2); }
		 |
		 ;

Authors : Authors Author
		| Author
		;

/* BEGIN - Dados Autor */
Author : BEGINAUTHOR Name Nident Email Url Affiliation ENDAUTHOR	{ insereAutor(la,a); }
	   ;

Name : BEGINNAME texto ENDNAME		{ a = inicializaAutor(); insereNome(a,$2); }
	 ;

Nident : BEGINNID texto ENDNID		{ insereID(a,$2); }
	   |
	   ;

Email : BEGINEMAIL texto ENDEMAIL 	{ insereEmail(a,$2); }
	  |
	  ;

Url : BEGINURL texto ENDURL 		{ insereURL(a,$2); }
	|
	;

Affiliation : BEGINAFFILIATION texto ENDAFFILIATION		{ insereAfiliacao(a,$2); }
			|
			;
/* END - Dados Autor */

Date : BEGINDATE texto ENDDATE		{ adicionaDate(r,$2); }
	 ;

Institution : BEGININSTITUTION texto ENDINSTITUTION		{ adicionaInstitution(r,$2); }
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

Toc : ICONTENT 		{ setTOC(r); }
	|
	;

Lof : IFIGURE		{ setLOF(r); }
	|
	;

Lot : ITABLE		{ setLOT(r); }
	|
	;
/* END - FRONTMATTER */
/* BEGIN - BODY */	
Body : BEGINBODY ChapterList ENDBODY
	 ;

ChapterList : ChapterList Chapter
            | Chapter
            ;

Chapter : BEGINCHAP Title ElemList ENDCHAP	{ c = criaCapitulo($2,e); 
											  insereCapitulo(lc,c);
											  e = inicializaElemento();
											  lp = createLinkedList(NULL,NULL);
											}
		;

ElemList : ElemList Elem
		 | Elem
		 ;

Elem : Paragraph							{ setParagrafos(e,lp); listaElementos(e->parags); }
	 | Float
	 | List
	 | CodeBlock
	 | Section
	 | Summary 
	 ;

Paragraph : BEGINPARA ParaContent ENDPARA	{ insereParagrafo(lp,p); }
		  ;

ParaContent : ParaContent texto			{ p = inicializaParagrafo(0,$2); }
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

Footnote : BEGINFOOT texto ENDFOOT		{ p = inicializaParagrafo(1,$2); }
		 ;

Ref : BEGINREF texto ENDREF 			{ p = inicializaParagrafo(2,$2); }	
	;

Xref : BEGINXREF texto ENDXREF			{ p = inicializaParagrafo(3,$2); }
	 ;

Citref : BEGINCIT texto ENDCIT 			{ p = inicializaParagrafo(4,$2);}
	   ;

Iterm : BEGINITERM texto ENDITERM		{ p = inicializaParagrafo(5,$2); }
	  ;

Bold : BEGINBOLD BContent ENDBOLD
	 ;

BContent : BContent texto				{ p = inicializaParagrafo(6,$2); }
		 | BContent Italic
		 | BContent Underline
		 |
		 ;

Italic : BEGINITALIC IContent ENDITALIC
	   ;

IContent : IContent texto				{ p = inicializaParagrafo(7,$2); }
		 | IContent Bold
		 | IContent Underline
		 |
		 ;

Underline : BEGINUNDERLINE UContent ENDUNDERLINE
		  ;

UContent : UContent texto				{ p = inicializaParagrafo(8,$2); }
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
	r = inicializaReport();
	e = inicializaElemento();

	la = createLinkedList(NULL,NULL);
	lp = createLinkedList(NULL,NULL);
	lc = createLinkedList(NULL,NULL);

	FILE *file = fopen("exemplo1.txt", "r");
	
	if(file) {
		yyin = file;
		yyparse();
	}
	return 0;
}
