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

int insereAutor(LinkedList, Autor) ;

#endif