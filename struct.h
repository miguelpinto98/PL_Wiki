#ifndef __STRUCT
#define __STRUCT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist/linkedlist.h"

typedef struct sPagina {
	char* titulo;
	char* data;
	char* autor;
	LinkedList seccoes;
	LinkedList linkint;
	LinkedList linkext;
} *Pagina, NPagina;

Pagina inicializaPagina() ;
void insereTitulo(Pagina, char*) ;
void insereData(Pagina, char*) ;
void insereAutor(Pagina, char*) ;
void insereSeccao(Pagina, char*) ;
void insereLinkInt(Pagina, char*) ;
void insereLinkExt(Pagina, char*) ;

void inserePaginaLL(LinkedList, Pagina) ;
void imprimeLL(LinkedList) ;

#endif