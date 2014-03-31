#include "struct.h"

Pagina inicializaPagina() {
	Pagina res = NULL;

	res = (Pagina)malloc(sizeof(NPagina));
	res->titulo = NULL;
	res->data = NULL;
	res->autor = NULL;
	res->seccoes = createLinkedList(NULL,NULL);
	res->linkint = createLinkedList(NULL,NULL);
	res->linkext = createLinkedList(NULL,NULL);

	return res;
}

void insereTitulo(Pagina pag, char *tit) {
	pag->titulo = strdup(tit);
}

void insereData(Pagina pag, char *date) {
	pag->data = strdup(date);
}

void insereAutor(Pagina pag, char *autor) {
	pag->autor = strdup(autor);
}

void insereSeccao(Pagina pag, char* sec) {
	tailInsertLinkedList(pag->seccoes, strdup(sec));
}

void insereLinkInt(Pagina pag, char* url) {
	tailInsertLinkedList(pag->linkint, strdup(url));
}

void insereLinkExt(Pagina pag, char* url) {
	tailInsertLinkedList(pag->linkext, strdup(url));
}

void inserePaginaLL(LinkedList lpags, Pagina pag) {
	pushLinkedList(lpags, pag);
}

void imprimeLL(LinkedList lpags) {
	LinkedList aux = lpags;
	Pagina res = NULL;

	while(aux->elems) {
		res = aux->elems->data;
		printf("%s\n", res->titulo);

		aux->elems = aux->elems->next;
	}

	printf("NUM: %d\n", lpags->nrelems);
}