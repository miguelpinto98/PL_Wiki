#ifndef __STRUCTS
#define __STRUCTS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "linkedlist/linkedlist.h"

typedef struct sAutor {
	char* nome;
	char* id;
	char* email;
	char* url;
	char* affiliation;
} *Autor, NAutor;

typedef struct sReport {
	char* titulo;
	char* subtitulo;
	char* date;
	char* institution;
	char* resumo;
	char* agradecimentos;
	int toc;
	int lof;
	int lot;
} *Report, NReport;

typedef struct sParagrafo {
	int id;
	char* item;
} *Paragrafo, NParagrafo;

typedef struct sFigura {
	char *caption;
	char *path;
	char *format;
} *Figura, NFigura;

typedef struct sTabela {
	char *caption;
	LinkedList rows;
} *Tabela, NTabela;

typedef struct sRow {
	LinkedList data;
} *Row, NRow;

typedef struct sData {
	char *value;	
} *Data, NData;

typedef struct sLista{
	LinkedList lista;
} *Lista, NLista;

typedef struct sCodeBlock {
	LinkedList lista;
} *CodeBlock, NCodeBlock;

typedef struct sSummary {
	char *item;
} *Summary, NSummary;

typedef struct sElemento {
	Paragrafo para;
	Figura fig;
	Tabela tab;
	Lista lista;
	CodeBlock code;
	Summary summ;
} *Elemento, NElemento;

typedef struct sCapitulo {
	char *nome;
	LinkedList elementos;
} *Capitulo, NCapitulo;

/* ABSTRACT AGRADECIMENTOS KEYWORDS */


int insereAutor(LinkedList, Autor) ;
Autor inicializaAutor() ;
void insereNome(Autor a, char *str) ;
void insereID(Autor a, char *str) ;
void insereEmail(Autor a, char *str) ;
void insereURL(Autor a, char *str) ;
void insereAfiliacao(Autor a, char *str) ;

Report inicializaReport() ;
void adicionaTitulo(Report , char* ) ;
void adicionaSubTitulo(Report , char* ) ;
void adicionaDate(Report , char* ) ;
void adicionaInstitution(Report , char* ) ;
void adicionaResumo(Report, char*) ;
void adicionaAgradece(Report, char* );
void setTOC(Report ) ;
void setLOF(Report ) ;
void setLOT(Report ) ;

Paragrafo inicializaParagrafo(int , char*) ;

Lista criaLista(LinkedList );
int insereLista(LinkedList, Lista );

CodeBlock criaListaCode(LinkedList );

Summary criaSumario(char *) ;

Tabela inicializaTabela() ;
void setCaptionT(Tabela , char *) ;
void setRows(Tabela, LinkedList) ;
Row iniciaRow(LinkedList ) ;
int insereRow(LinkedList , Row ) ;
Data criaData(char *) ;
int insereDataTabela(LinkedList, Data) ;

Figura inicializaFigura() ;
void setCaption(Figura, char *) ;
void setFormat(Figura, char *) ;
void setPath(Figura, char *) ;

Elemento inicializaElemento() ;
void setParagrafo(Elemento , Paragrafo ) ;
void setFigura(Elemento , Figura ) ;
void setTabela(Elemento, Tabela ) ;
void setLista(Elemento, Lista ) ;
void setCode(Elemento, CodeBlock ) ;
void setSumario(Elemento, Summary) ;
int insereElemento(LinkedList , Elemento ) ;

Capitulo criaCapitulo(char *, LinkedList) ;
int insereCapitulo(LinkedList , Capitulo) ;

void lista(LinkedElem ) ;


#endif