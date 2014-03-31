#ifndef __STRUCT
#define __STRUCT

#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct sArtigo {
	char* titulo;
	char* data;
	char* autor;
} *Artigo, NArtigo;

#endif