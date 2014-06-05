%{
	#include <stdio.h>
	#include <string.h>
	#include "linkedlist/linkedlist.h"
	#include "structs.h"
	#include "latexFile.h"
	#include "htmlFile.h"

	int yyerror(char *s);
    
    extern int yylex();
    extern FILE* yyin;
    extern int yylineno;

    LinkedList la = NULL;
    LinkedList le = NULL;
    LinkedList lc = NULL;
    LinkedList ls = NULL;
    LinkedList lcodes = NULL;

    LinkedList lkeys = NULL;

    LinkedList tocs = NULL;
    LinkedList lots = NULL;
	LinkedList lofs = NULL;

    LinkedList tabs = NULL;
    LinkedList lrow = NULL;

    Autor a = NULL;
    Report r = NULL;
    Paragrafo p = NULL;
    Elemento e = NULL;
    Capitulo c = NULL;
    Figura f = NULL;
    Tabela t = NULL;
    Row row = NULL;
    Data dt = NULL;
    Lista l = NULL;
    Summary s = NULL;
    CodeBlock code = NULL;
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
%type<s> Title Caption Line

%%

Report : BEGINREPORT FrontMatter Body BackMatter ENDREPORT /*{lista(lc->elems);}*/ {lista(lc->elems);}
	   ;

FrontMatter : BEGINFM Title SubTitle Authors Date Institution Keywords Abstract Aknowledgements Toc Lof Lot ENDFM
			  { adicionaTitulo(r,$2); t=inicializaTabela(); }
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
Keywords : BEGINKEYWORD Keylist ENDKEYWORD
		 |
		 ;

Keylist : Keylist Line 			{ tailInsertLinkedList(lkeys,strdup($2)); }
		| Line 					{ tailInsertLinkedList(lkeys,strdup($1)); }
		;

/* END - PALAVRAS CHAVE */ 

/* BEGIN - RESUMO */
Abstract : BEGINABS texto ENDABS	{ adicionaResumo(r,$2); }
		 ;

/* BEGIN AGRADECIMENTOS */
Aknowledgements : BEGINAKN texto ENDAKN 	{ adicionaAgradece(r,$2); }
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

Chapter : BEGINCHAP Title ElemList ENDCHAP	{ c = criaCapitulo($2,le);
											  insereCapitulo(lc,c);
											  le = createLinkedList(NULL,NULL);
											}
		;

ElemList : ElemList Elem 					{  e = inicializaElemento(); }
		 | Elem 							{  e = inicializaElemento(); }
		 ;

Elem : Paragraph							{ setParagrafo(e,p); insereElemento(le,e); /*lista(le->elems);*/ }
	 | Float								{ }
	 | List
	 | CodeBlock
	 | Section
	 | Summary 
	 ;

Paragraph : BEGINPARA ParaContent ENDPARA	{ e = inicializaElemento(); }
		  ;

ParaContent : ParaContent texto				{ p = inicializaParagrafo(0,$2); }
			| ParaContent FreeElement		/*{ setParagrafo(e,p); }*/
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

Float : Figure									{ f=inicializaFigura(); e = inicializaElemento(); }
	  | Table									{ t=inicializaTabela(); e = inicializaElemento(); }
	  ;

Figure : BEGINFIG Graphic Caption ENDFIG 		{ setCaption(f,$3); tailInsertLinkedList(lofs,$3); setFigura(e,f); insereElemento(le,e); }
	   ;

Graphic : BEGINGRAPH Path Format ENDGRAPH		
		;

Path : BEGINPATH texto ENDPATH 					{ setPath(f,$2); }
	 ;

Format : BEGINFORMAT texto ENDFORMAT			{ setFormat(f,$2); }
	   ;

Caption : BEGINCAPTION texto ENDCAPTION			{ $$=$2; }
		;

Table : BEGINTABLE Caption TRowList ENDTABLE	{ setCaptionT(t,$2);
												  setRows(t,tabs);
												  setTabela(e,t);
												  tailInsertLinkedList(lots,$2);
												  insereElemento(le,e);
												  tabs = createLinkedList(NULL,NULL);
												}
	  ;

TRowList : TRowList TRow
		 | TRow
		 ;

TRow : BEGINROW ListData ENDROW		{ row = iniciaRow(lrow);
									  insereRow(tabs,row);
									  lrow = createLinkedList(NULL,NULL);
									}
	 ;

ListData : ListData Data
	  	 | Data
	  	 ;

Data : BEGINDATA texto ENDDATA		{ dt = criaData($2); insereDataTabela(lrow,dt); }
	 ;

Summary : BEGINSUM texto ENDSUM		{ s = criaSumario($2);
									  setSumario(e,s);
									  insereElemento(le,e);
									  e = inicializaElemento();
									}
		;

List : BEGINLIST ParaList ENDLIST	{ l = criaLista(ls);
									  setLista(e,l);
									  insereElemento(le,e);
									  ls = createLinkedList(NULL,NULL);
									  e = inicializaElemento();
									}
	 ;

ParaList : ParaList Line 			{ tailInsertLinkedList(ls,strdup($2)); }
		 | Line						{ tailInsertLinkedList(ls,strdup($1)); }
		 ;

Line : texto	{ $$=$1; }

CodeBlock : BEGINCODE ListCode ENDCODE { code = criaListaCode(lcodes);
										 setCode(e,code);
										 insereElemento(le,e);
										 lcodes = createLinkedList(NULL,NULL);										 
										 e = inicializaElemento();
										}
		  ;

ListCode : ListCode Line 			{ tailInsertLinkedList(lcodes,strdup($2)); }
		 | Line 					{ tailInsertLinkedList(lcodes,strdup($1)); }
		 ;

Section : BEGINSEC Title texto ENDSEC
		;
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

int main(int argc, char *argv[]){
	r = inicializaReport();
	f = inicializaFigura();
	la = createLinkedList(NULL,NULL);
	le = createLinkedList(NULL,NULL);
	lc = createLinkedList(NULL,NULL);
	ls = createLinkedList(NULL,NULL);
	lcodes = createLinkedList(NULL,NULL);
	lkeys = createLinkedList(NULL,NULL);
	lrow = createLinkedList(NULL,NULL);
	tabs = createLinkedList(NULL,NULL);
	lots = createLinkedList(NULL,NULL);
	lofs = createLinkedList(NULL,NULL);

	if(argc>1) {
		FILE *file = fopen(argv[1], "r");
	
		if(file) {
			yyin = file;
			yyparse();
		
			criaPagina(r,la,lkeys,lc,lots,lofs);
			criaPaginaPDF(la,r,lc);
		}
	}
	return 0;
}
