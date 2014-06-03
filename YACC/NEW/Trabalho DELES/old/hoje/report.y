%{
#include <stdio.h>
#include "report.h"
#include <string.h>

Report r;

Author a;
Paragraph p;
Table t;
Chapter c;
Elem e;
SecElem se;
Paragraph_Elem pe;
char* aux;
GArray * paragraphs;
GArray * elems;
GArray * chapters;
Figure fig;
Row row;
Table table;
List list;
Cell cell;

Section section;

int yyerror(char *s);
extern FILE* yyin;
extern FILE* yyout;
extern int yylineno;

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
%token KEYWORDS
%token BEGIN_ROW
%token END_ROW
%token BEGIN_CELL
%token END_CELL
%token END_LIST
%token END_CODEBLOCK
%token BEGIN_INST
%token END_INST
%token INDEX
%token INDEX_F
%token INDEX_T
%token BEGIN_SCALE
%token END_SCALE
%token BEGIN_SEC
%token END_SEC
%token BEGIN_LIST
%token BEGIN_CODEBLOCK
%token BEGIN_SUMMARY
%token END_SUMMARY
%token BEGIN_BACKMATTER
%token END_BACKMATTER
%token BEGIN_FOOTNOTE
%token END_FOOTNOTE
%token BEGIN_REF
%token END_REF
%token BEGIN_XREF
%token END_XREF
%token BEGIN_CITEREF
%token END_CITEREF
%token BEGIN_ITERM
%token END_ITERM
%token BEGIN_BOLD
%token END_BOLD
%token BEGIN_ITALIC
%token END_ITALIC
%token BEGIN_UNDERLINE
%token END_UNDERLINE
%token BEGIN_INLINECODE
%token END_INLINECODE
%token BEGIN_ACRONYM
%token END_CITREF
%token BEGIN_CITREF
%token END_ACRONYM



%token <str> TEXT
%type <str> text
%type <str> Title



%%

Report: BEGIN_REPORT FrontMatter Body BackMatter END_REPORT 
        |  BEGIN_REPORT END_REPORT ;

FrontMatter: BEGIN_FM Title Subtitle Authors Date Institution Keywords Abstract Aknow Toc Lof Lot END_FM  { r.frontmatter.title = strdup($2); };;


Title: BEGIN_TITLE text END_TITLE  {$$=$2;};

Subtitle: BEGIN_SUBTITLE text END_SUBTITLE      { r.frontmatter.subtitle = strdup($2);};

Author: BEGIN_AUTHOR Name Number Mail END_AUTHOR    {g_array_append_val(r.frontmatter.authors,a);};

Authors: Author 
	| Authors Author ;

Name: BEGIN_NAME text END_NAME  { a.name = strdup($2);};

Number: BEGIN_NUMBER text END_NUMBER    { a.number = strdup($2);} 
	| ;	

Mail: BEGIN_MAIL text END_MAIL  { a.mail = strdup($2);} 
	| ;

Date: BEGIN_DATE text END_DATE  { r.frontmatter.date = strdup($2);}
    | TODAY { r.frontmatter.date = NULL ;};

Institution: BEGIN_INST text END_INST {r.frontmatter.institution = strdup($2);}

Keywords: KEYWORDS Words KEYWORDS 
    | ; 

Words: text       {g_array_append_val(r.frontmatter.keywords, ($1));}
     | Words text {g_array_append_val(r.frontmatter.keywords, ($2));};


Abstract: BEGIN_ABS Paragraphs END_ABS {r.frontmatter.abstract.paragraphs = paragraphs; paragraphs= g_array_new(FALSE,FALSE,sizeof(Paragraph));} ;

Aknow: BEGIN_AKN Paragraphs END_AKN {r.frontmatter.aknow.paragraphs = paragraphs; paragraphs= g_array_new(FALSE,FALSE,sizeof(Paragraph));};

Paragraphs: Paragraph {g_array_append_val(paragraphs, p); p.prg_elem = g_array_new(FALSE,FALSE,sizeof(Paragraph_Elem));}
    | Paragraphs Paragraph {g_array_append_val(paragraphs, p); p.prg_elem = g_array_new(FALSE,FALSE,sizeof(Paragraph_Elem));};

Paragraph: BEGIN_PARA Paragraph_Elems END_PARA ;
 
Paragraph_Elems: Paragraph_Elem {g_array_append_val(p.prg_elem, pe);}
    | Paragraph_Elems Paragraph_Elem {g_array_append_val(p.prg_elem, pe);};

Paragraph_Elem: text {pe.id= 7; pe.e.text=strdup($1);}
    | BEGIN_FOOTNOTE text END_FOOTNOTE {pe.id= FOOTNOTE; pe.e.footnote.text = strdup($2);}
    | BEGIN_REF text END_REF {pe.id= REF; pe.e.ref.text = strdup($2);}
    | BEGIN_XREF text END_XREF {pe.id= XREF; pe.e.xref.text = strdup($2);}
    | BEGIN_CITREF text END_CITREF {pe.id=CITREF; pe.e.citref.text = strdup($2);}
    | BEGIN_ITERM text END_ITERM {pe.id= ITERM; pe.e.iterm.text = strdup($2);}
    | BEGIN_BOLD text END_BOLD {pe.id= BOLD; pe.e.bold.text = strdup($2);}
    | BEGIN_ITALIC text END_ITALIC {pe.id= ITALIC; pe.e.italic.text = strdup($2);}
    | BEGIN_UNDERLINE text END_UNDERLINE {pe.id= UNDERLINE; pe.e.underline.text = strdup($2);} 
    | BEGIN_INLINECODE text END_INLINECODE {pe.id= INLINECODE; pe.e.inlineCode.text = strdup($2);}
    | BEGIN_ACRONYM text END_ACRONYM {pe.id= ACRONYM; pe.e.acronym.text = strdup($2);};

Toc: INDEX  {r.frontmatter.index = 1;}
    |  {r.frontmatter.index = 0;};

Lof: INDEX_F    {r.frontmatter.figures_index= 1;}
    |  {r.frontmatter.figures_index= 0;};

Lot: INDEX_T    {r.frontmatter.tables_index = 1;}
    |  {r.frontmatter.tables_index = 0;};


BackMatter: BEGIN_BACKMATTER Paragraphs END_BACKMATTER {r.backMatter.paragraphs = paragraphs; paragraphs= g_array_new(FALSE,FALSE,sizeof(Paragraph));};

Body: BEGIN_BODY Chapters END_BODY {r.body.chapters = chapters; chapters= g_array_new(FALSE,FALSE,sizeof(Chapter));} ;
    | ;


Chapters: Chapter {g_array_append_val(chapters, c); c.elems = g_array_new(FALSE,FALSE,sizeof(Elem));}
    | Chapters Chapter {g_array_append_val(chapters, c); c.elems = g_array_new(FALSE,FALSE,sizeof(Elem));};

Chapter: BEGIN_CHAP Title Elems END_CHAP { c.title = strdup($2); c.elems = elems; elems = g_array_new(FALSE,FALSE,sizeof(Elem));};

Elems: Elem     {g_array_append_val(elems, e); e.e.paragraph.prg_elem = g_array_new(FALSE,FALSE,sizeof(Paragraph_Elem));}
    | Elems Elem {g_array_append_val(elems, e); e.e.paragraph.prg_elem = g_array_new(FALSE,FALSE,sizeof(Paragraph_Elem));};

Elem: Paragraph {e.id = PARAGRAPH; e.e.paragraph=p; p.prg_elem = g_array_new(FALSE,FALSE,sizeof(Paragraph_Elem));}
    | Summary {e.id = SUMMARY;}
    | Codeblock {e.id = CODEBLOCK;}
    | BEGIN_LIST List END_LIST  {e.id = LIST; e.e.list.items = list.items; list.items = g_array_new(FALSE,FALSE,sizeof(char*));}
    | Figure {e.id = FIGURE; e.e.fig = fig;}
    | Table {e.id = TABLE;}; 

Table: BEGIN_TABLE TRowList END_TABLE TCaption {e.e.table= table; table.rows = g_array_new(FALSE,FALSE,sizeof(Row));};


TRowList: TRowList BEGIN_ROW TRow END_ROW  {g_array_append_val(table.rows, row); row.cells = g_array_new(FALSE,FALSE,sizeof(Cell));}
    | BEGIN_ROW TRow END_ROW{g_array_append_val(table.rows, row); row.cells = g_array_new(FALSE,FALSE,sizeof(Cell));}
    |;

TRow: BEGIN_CELL text END_CELL { cell.text= strdup($2); g_array_append_val(row.cells, cell); }
    | TRow BEGIN_CELL text END_CELL{ cell.text= strdup($3); g_array_append_val(row.cells, cell); };

TCaption: BEGIN_CAPTION text END_CAPTION {table.caption= strdup($2);};
Summary: BEGIN_SUMMARY text END_SUMMARY {e.e.summary = strdup($2);};

Codeblock: BEGIN_CODEBLOCK text END_CODEBLOCK {e.e.codeblock = strdup($2);};

List: text {g_array_append_val(list.items, $1); }
    | List text {g_array_append_val(list.items, $2); };

text: TEXT {$$=$1;};

Figure:  BEGIN_FIG Graphic FCaption END_FIG
Graphic: BEGIN_GRAPH text END_GRAPH {fig.path= strdup($2);};
FCaption: BEGIN_CAPTION text END_CAPTION {fig.caption= strdup($2); fig.size=100;};

%%

int yyerror(char * s){fprintf(stderr,"%d:%s\n", yylineno, s);}

int main(int argc, char *argv[]){ 
    p.prg_elem = g_array_new(FALSE,FALSE,sizeof(Paragraph_Elem));
    paragraphs = g_array_new(FALSE,FALSE,sizeof(Paragraph));
    elems = g_array_new(FALSE,FALSE,sizeof(Elem));
    chapters = g_array_new(FALSE,FALSE,sizeof(Chapter));
    list.items = g_array_new(FALSE,FALSE,sizeof(char*));
    row.cells = g_array_new(FALSE,FALSE,sizeof(Cell));
    table.rows = g_array_new(FALSE,FALSE,sizeof(Row));
    if(argc > 1) {
    	yyin = fopen(argv[1],"r");
    	yyout = fopen("report.html","w+");
        initReport();
    	yyparse();
        if(argc > 2) {
            if(strcmp(argv[2],"-l")==0){
                //printReportLatex(yyout);
            }
            else if(strcmp(argv[2],"-hl")==0){
                printREPORT(yyout);
            }
            else if(strcmp(argv[2],"-h")==0){
                printREPORT(yyout);
            }
        }
    	fclose(yyin);
    }
    else {
    	initReport();
    	yyparse();
    	printREPORT(yyout);
    	perror("Insira pelo menos o path para um ficheiro a ser convertido\n");
   	}
   return 0;
}