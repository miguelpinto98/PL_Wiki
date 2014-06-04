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
	char *titulo;
	char *subtitulo;
	char *date;
	char *institution;
	int toc;
	int lof;
	int lot;
} *Report, NReport;

typedef struct sParagrafo {
	int id;
	char *item;
} *Paragrafo, NParagrafo;

typedef struct sElemento {
	LinkedList parags;
} *Elemento, NElemento;

typedef struct sCapitulo {
	char *nome;
	Elemento elem;
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
void setTOC(Report ) ;
void setLOF(Report ) ;
void setLOT(Report ) ;

Paragrafo inicializaParagrafo(int , char*) ;
int insereParagrafo(LinkedList , Paragrafo) ;

Elemento inicializaElemento() ;
void setParagrafos(Elemento , LinkedList ) ;
void listaElementos(LinkedList ) ;

Capitulo criaCapitulo(char *, Elemento) ;
int insereCapitulo(LinkedList , Capitulo) ;

#endif