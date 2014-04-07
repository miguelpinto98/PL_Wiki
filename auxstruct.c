#include "auxstruct.h"

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

char *verificaData(char *data) {
	data[10]=' ';
	data[19]='\0';
	return data;
}

void insereData(Pagina pag, char *date) {
	pag->data = verificaData(strdup(date));
}

void insereAutor(Pagina pag, char *autor) {
	pag->autor = strdup(autor);
}

void insereSeccao(int tipo, Pagina pag, char* sec) {
	char *res = strdup(sec);
	int x = strlen(res);

	if(tipo==0)
		tailInsertLinkedList(pag->seccoes, res);
	else {
		if(tipo==1) {
			char aux[x+4];

			strcpy(aux,"1X1");
			strcat(aux,res);
			aux[x+4] = '\0';

			tailInsertLinkedList(pag->seccoes, strdup(aux));
			pag->seccoes->nrelems--;
		} else {
			if (tipo==2) {
				char aux[x+4];

				strcpy(aux,"2X2");
				strcat(aux,res);
				aux[x+4] = '\0';

				tailInsertLinkedList(pag->seccoes, strdup(aux));
				pag->seccoes->nrelems--;
			}
		}
	}
}

void insereLinkInt(Pagina pag, char* url) {
	tailInsertLinkedList(pag->linkint, strdup(url));
}

void insereLinkExt(Pagina pag, char* url) {
	tailInsertLinkedList(pag->linkext, strdup(url));
}

char verificaMaiuscula(char c){
	if(islower(c))
		return toupper(c);

	return c;
}

int comparaTitulos(void* tit1, void* tit2){
	char * s1 = strdup(tit1);
	char * s2 = strdup(tit2);

	s1[0] = verificaMaiuscula(s1[0]);
	s2[0] = verificaMaiuscula(s2[0]);
 	
	if(isdigit(s1[0]) || isdigit(s2[0]))
		return strcmp(s2,s1);

    return strcmp(s1,s2);
}

void* getChar(void* tit){
	return strdup(tit);
}

LinkedList iniciaIndiceTitulo() {
	return createLinkedList(getChar, comparaTitulos);
}

void insereTituloIndice(LinkedList lpages, char *tit) {
	ordInsertLinkedList(lpages, tit);
}