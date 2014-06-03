#include <glib.h>

typedef struct sAuthor
{
	char* name;
	char* number;
	char* mail;
} Author;

typedef struct sAbstract
{
	GArray* paragraphs;
} Abstract;

typedef struct sAknowledgements
{
	GArray* paragraphs;
} Aknowls;

typedef struct sFrontMatter {
	char* title;
	char* subtitle;
	GArray* authors;	
	char* date;
	Abstract abstract;
	Aknowls aknow;
} FrontMatter;

typedef struct sChapter
{
	char* title;
	GArray* elems;
} Chapter;

typedef struct sParagraph
{
	char* texto;
} Paragraph;

typedef struct sFigure
{
	char* caption;
	char* path;
	char* format;
	float size;
} Figure;

typedef struct sTable
{
	char* caption;
	int linhas;
	int colunas;
	char*** text; 	
} Table;

typedef struct sSection
{
	char* title;
	GArray* elems;
} Section;

typedef union uElems
{
	Paragraph paragraph;
	Figure fig;
	Table table;
	Section section;
} Elems;

typedef struct sBody
{
	GArray* chapters;
} Body;

typedef struct sReport
{
	FrontMatter frontmatter;
	Body body;
} Report;



void printHTML();
void printAUTORES();
void initReport();
void printDataHtml();
void printFrontMatter();
void printParapraph(Paragraph);
