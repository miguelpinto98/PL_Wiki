%{
#include <stdio.h>
#include "report.h"
#include <string.h>

Report r;
Author a;
Paragraph p;
Figure f;
Table t;
Chapter c;
int yyerror(char *s);
extern FILE* yyin;
extern FILE* yyout;


%}

%union {
    char *str;
}

%token BEGIN_REPORT
%token END_REPORT
%token BEGIN_FM
%token END_FM
%token BEGIN_TITLE
%token END_TITLE
%token BEGIN_SUBTITLE
%token END_SUBTITLE
%token BEGIN_DATE
%token END_DATE
%token TODAY
%token BEGIN_AUTHOR
%token END_AUTHOR
%token BEGIN_NAME
%token END_NAME
%token BEGIN_NUMBER
%token END_NUMBER
%token BEGIN_MAIL
%token END_MAIL
%token BEGIN_ABS
%token END_ABS
%token BEGIN_AKN
%token END_AKN

%token BEGIN_BODY
%token END_BODY
%token BEGIN_CHAP
%token END_CHAP
%token BEGIN_PARA
%token END_PARA
%token BEGIN_ELEM
%token END_ELEM
%token BEGIN_FIG
%token END_FIG
%token BEGIN_GRAPH
%token END_GRAPH
%token BEGIN_CAPTION
%token END_CAPTION
%token BEGIN_PATH
%token END_PATH
%token BEGIN_FORMAT
%token END_FORMAT
%token BEGIN_SIZE
%token END_SIZE
%token BEGIN_TABLE
%token END_TABLE

%token <str> TEXT
%type <str> text
%type <str> Title

%%

Report: BEGIN_REPORT FrontMatter Body END_REPORT ;

FrontMatter: BEGIN_FM Title Subtitle Authors Date Abstract Aknow END_FM { r.frontmatter.title = strdup($2);}
	| ;

Title: BEGIN_TITLE text END_TITLE   { $$=$2;};

Subtitle: BEGIN_SUBTITLE text END_SUBTITLE      { r.frontmatter.subtitle = strdup($2);};

Author: BEGIN_AUTHOR Name Number Mail END_AUTHOR    {g_array_append_val(r.frontmatter.authors,a);};

Authors: Author 
	| Authors Author ;

Name: BEGIN_NAME text END_NAME  { a.name = strdup($2);};

Number: BEGIN_NUMBER text END_NUMBER    { a.number = strdup($2);} 
	| ;	

Mail: BEGIN_MAIL text END_MAIL  { a.mail = strdup($2);} 
	|;

Date: BEGIN_DATE text END_DATE  { r.frontmatter.date = strdup($2);}
    | TODAY { r.frontmatter.date = NULL ;};

Abstract: BEGIN_ABS Paragraphs END_ABS { g_array_append_val(r.frontmatter.abstract.paragraphs,p);}

Aknow: BEGIN_AKN Paragraphs END_AKN 
    | ;

Paragraph: BEGIN_PARA text END_PARA { p.texto = strdup($2); } 

Paragraphs: Paragraph 
    | Paragraphs Paragraph ;

Body: BEGIN_BODY Chapters END_BODY
    | ;

Elems: Elem
    | Elems Elem;

Elem: Paragraph
      | Figure 
      | Table ;

Chapter: BEGIN_CHAP Title Elems END_CHAP { c.title = strdup($2);};

Chapters: Chapter
    | Chapters Chapter;

Figure: BEGIN_FIG Graphic Caption Size END_FIG ;

Graphic: BEGIN_GRAPH Path Format END_GRAPH ;

Path: BEGIN_PATH text END_PATH { f.path = strdup($2);};

Format: BEGIN_FORMAT text END_FORMAT { f.format = strdup($2);};
    | ;

Caption: BEGIN_CAPTION text END_CAPTION { f.caption = strdup($2);};

Size: BEGIN_SIZE text END_SIZE { f.size = atof($2);};
    | ;

Table: BEGIN_TABLE Caption END_TABLE ;





text: TEXT {$$=$1;};

%%

int yyerror(char *s){fprintf(stderr,"%s\n",s);}

int main(int argc, char *argv[]){ 
    if(argc > 1) {
    	yyin = fopen(argv[1],"r");
    	yyout = fopen("report.html","w+");
    	initReport();
    	yyparse();
    	printHTML();
    	fclose(yyin);
    }
    else {
    	initReport();
    	yyparse();
    	printHTML();
    	perror("Insira pelo menos o path para um ficheiro a ser convertido\n");
   	}
   return 0;
}