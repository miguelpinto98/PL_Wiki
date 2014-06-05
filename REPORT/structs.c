#include "structs.h"

Autor inicializaAutor() {
	Autor res = NULL;

	res = (Autor)malloc(sizeof(NAutor));
	res->nome = NULL;
	res->id = NULL;
	res->email = NULL;
	res->url = NULL;
	res->affiliation = NULL;

	return res;
}

void insereNome(Autor a, char *str) {
	a->nome = strdup(str);
}

void insereID(Autor a, char *str) {
	a->id = strdup(str);
}

void insereEmail(Autor a, char *str) {
	a->email = strdup(str);
}

void insereURL(Autor a, char *str) {
	a->url = strdup(str);
}

void insereAfiliacao(Autor a, char *str) {
	a->affiliation = strdup(str);
}

int insereAutor(LinkedList lautor, Autor a) {
	return tailInsertLinkedList(lautor,a);
}

Report inicializaReport() {
	Report res;

	res = (Report)malloc(sizeof(NReport));
	res->titulo = NULL;
	res->subtitulo = NULL;
	res->date = NULL;
	res->institution = NULL;
	res->resumo = NULL;
	res->agradecimentos = NULL;
	res->toc = 0;
	res->lof = 0;
	res->lot = 0;

	return res;
}

void adicionaTitulo(Report r, char* str) {
	r->titulo = strdup(str);
}

void adicionaSubTitulo(Report r, char* str) {
	r->subtitulo = strdup(str);
}

void adicionaDate(Report r, char* str) {
	r->date = strdup(str);
}

void adicionaInstitution(Report r, char* str) {
	r->institution = strdup(str);
}

void adicionaResumo(Report r, char* str) {
	r->resumo = strdup(str);
}

void adicionaAgradece(Report r, char *str) {
	r->agradecimentos = strdup(str);
}

void setTOC(Report r) {
	r->toc = 1;
}

void setLOF(Report r) {
	r->lof = 1;
}

void setLOT(Report r) {
	r->lot = 1;
}

Paragrafo inicializaParagrafo(int n, char *str) {
	Paragrafo res;

	res = (Paragrafo)malloc(sizeof(NParagrafo));
	res->id = n;
	res->item = strdup(str);

	return res;
}

Elemento inicializaElemento() {
	Elemento res;

	res = (Elemento)malloc(sizeof(NElemento));
	res->para = NULL;
	res->fig = NULL;
	res->tab = NULL;

	return res;
}

void setParagrafo(Elemento e, Paragrafo p) {
	e->para = p;
}

void setFigura(Elemento e, Figura f) {
	e->fig = f;
}

void setTabela(Elemento e, Tabela t) {
	e->tab = t;
}

Tabela inicializaTabela() {
	Tabela res;

	res = (Tabela)malloc(sizeof(NTabela));
	res->caption = NULL;
	res->rows = createLinkedList(NULL,NULL);

	return res;
}

void setCaptionT(Tabela t, char *str) {
	t->caption = strdup(str);
}

void setRows(Tabela t, LinkedList l) {
	t->rows = l;
}

Row iniciaRow(LinkedList ll) {
	Row res;

	res = (Row)malloc(sizeof(NRow));
	res->data = ll;

	return res;
}

int insereRow(LinkedList list, Row r) {
	return tailInsertLinkedList(list,r);
}

Data criaData(char *valor) {
	Data res;

	res = (Data)malloc(sizeof(NData));
	res->value = valor;

	return res; 
}

int insereDataTabela(LinkedList ll, Data d) {
	return tailInsertLinkedList(ll,d);
}

Figura inicializaFigura() {
	Figura res;

	res = (Figura)malloc(sizeof(NFigura));
	res->caption = NULL;
	res->path = NULL;
	res->format = NULL;

	return res;
}

void setCaption(Figura f, char *res) {
	f->caption = strdup(res);
}

void setFormat(Figura f, char *res) {
	f->format = strdup(res);
}

void setPath(Figura f, char *res) {
	f->path = strdup(res);
}

int insereElemento(LinkedList le, Elemento e) {
	return tailInsertLinkedList(le,e);
}

Capitulo criaCapitulo(char *tit, LinkedList list) {
	Capitulo res;

	res = (Capitulo)malloc(sizeof(NCapitulo));
	res->nome = strdup(tit);
	res->elementos = list;

	return res;
}

int insereCapitulo(LinkedList list, Capitulo c) {
	return tailInsertLinkedList(list,c);
}

void lista(LinkedElem le) {
	LinkedElem aux = le;

	while(aux) {
	/*	Elemento e = (Elemento) aux->data;

		Paragrafo p = e->para;
		printf("%d\n",p->id);
		printf("%s\n",p->item);

		if(e->fig != NULL)
			printf("FIG\n");

		if(e->tab != NULL)
			printf("TAB\n");

		printf("ABCXXX\n");
	//	aux = aux->next;
	//}*/

	Capitulo c = (Capitulo) aux->data;

		printf("%s\n",c->nome);
		LinkedElem aux2 = c->elementos->elems;
		while(aux2) {
			Elemento e = (Elemento) aux2->data;

			/*
			if(e->para != NULL)
			printf("PARA %s\n",e->para->item);

			if(e->fig != NULL)
				printf("FIG %s\n",e->fig->caption );
			*/


			aux2 = aux2->next;
		}

	aux = aux->next;
	}
}

