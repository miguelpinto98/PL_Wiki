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

/* *************************************************** */

void criaHeader(char *tit, FILE *fp) {
	fputs("<!DOCTYPE html><html lang=\"pt\"><head>",fp);
	fprintf(fp, "<title>%s</title>", tit);
	fputs("<meta charset=\"UTF-8\" /><meta charset=\"UTF-8\" />",fp);
	fputs("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />",fp);
	fputs("<link rel=\"stylesheet\" href=\"assets/css/bootstrap.min.css\" /><link rel=\"stylesheet\" href=\"assets/css/font-awesome.css\" />",fp);
	fputs("<link rel=\"stylesheet\" href=\"assets/css/unicorn.css\" />",fp);
	fputs("</head>",fp);
}

void openContent(Pagina pag, FILE *fp) {
	fputs("<body data-color=\"blue\" class=\"flat\"><div id=\"wrapper\"><div id=\"header\"><h1>",fp);
	fputs("<a href=\"index.html\"></a></h1>	<a id=\"menu-trigger\" href=\"index.html#\"><i class=\"fa fa-bars\"></i></a>",fp);
	fputs("</div><div id=\"sidebar\"><ul><li class=\"active\"><a href=\"index.html\"><i class=\"fa fa-book\"></i> <span>Índice</span></a></li>",fp);
	fputs("<li><a href=\"enunciado.html\"><i class=\"fa fa-file\"></i> <span>Enunciado</span></a></li><li><a href=\"relatorio.html\"><i class=\"fa fa-paste\"></i> <span>Relatório</span></a></li>",fp);
	fputs("<li><a href=\"grupo.html\"><i class=\"fa fa-group\"></i> <span>Grupo</span></a></li></ul></div><div id=\"content\">",fp);
	fprintf(fp, "<div id=\"content-header\"><a href=\"https://pt.wikipedia.org/%s\" ><h1> %s </h1></a></div><div id=\"breadcrumb\">", pag->titulo, pag->titulo);
	fputs("<a class=\"tip-bottom\"><i class=\"fa fa-home\" style=\"margin-bottom:3px\"></i> WikiCenas</a><a href=\"index.html\" title=\"Ir para o índice\">Índice</a>",fp);
	fprintf(fp, "<a href=\"https://pt.wikipedia.org/%s\" class=\"current\"> %s </a></div><div class=\"container-fluid\"><br/>", pag->titulo, pag->titulo);
}

void criaContentPanel1(Pagina pag, FILE *fp){
	fputs("<div class=\"row\"><div class=\"col-xs-12 col-sm-6 col-lg-6\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Informações Relevantes</h5></div>",fp);
	fputs("<div class=\"widget-content nopadding\"><ul class=\"recent-posts\"><li style=\"font-size:12px; color:#3498db;\">Título:",fp);
	fprintf(fp, "<span style=\"color:black;\"> %s</span></li><li style=\"font-size:12px; color:#3498db;\">Autor da última revisão:", pag->titulo);
	fprintf(fp, "<span style=\"color:black;\"> %s</span></li><li style=\"font-size:12px; color:#3498db;\">Data da última revisão:", pag->autor);
	fprintf(fp, "<span style=\"color:black;\"> %s</span></li></ul></div></div></div></div>", pag->data);
}

	/* Imprime Links Internos */
void imprimeLinks(LinkedList link, FILE *fp, int tipo){
	LinkedElem aux = link->elems;

	while(aux) {
		if(tipo==1)
			fprintf(fp, "<li><a href=\"https://pt.wikipedia.org/wiki/%s\" class=\"current\"> %s </a></li>",aux->data,aux->data);
		if(tipo==2)
			fprintf(fp, "<li> %s </li>",aux->data);
		aux=aux->next;
	}

}

void criaContentPanel2(Pagina pag, FILE *fp){
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Links Internos</h5>",fp);
	fprintf(fp, "<span title=\"Número total de links internos\" class=\"label label-info tip-left\"> %d </span></div><div class=\"widget-content\"><ul>", pag->linkint->nrelems);
	/* Imprime Links Internos */
	imprimeLinks(pag->linkint,fp,1);
	fputs("</ul></div></div></div></div>",fp);

}

void criaContentPanel3(Pagina pag, FILE *fp){
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Links Externos</h5>",fp);
	fprintf(fp, "<span title=\"Número total de links externos\" class=\"label label-info tip-left\"> %d </span></div><div class=\"widget-content\"><ul>", pag->linkext->nrelems);
	/* Imprime Links Externos */
	imprimeLinks(pag->linkext,fp,1);
	fputs("</ul></div></div></div></div>",fp);
}

void criaContentPanel4(Pagina pag, FILE *fp) {
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Secções</h5>",fp);
	fprintf(fp, "<span title=\"Número total de secções\" class=\"label label-info tip-left\"> %d </span></div><div class=\"widget-content\"><ul>", pag->seccoes->nrelems);
	/* Imprime Links Externos */
	imprimeLinks(pag->seccoes,fp,2);
	fputs("</ul></div></div></div></div>",fp);
}

void closeFooter(FILE *fp) {
	fputs("</div></div><div class=\"row\"><div id=\"footer\" class=\"col-xs-12\">2013 - 2014 Programação de Linguagens.</br></br></div></div></div></body></html>",fp);
}

void criaPagina(Pagina pag, FILE *fp) {
	criaHeader(pag->titulo, fp);
	openContent(pag,fp);
	criaContentPanel1(pag,fp);
	criaContentPanel2(pag,fp);
	criaContentPanel3(pag,fp);
	criaContentPanel4(pag,fp);
	closeFooter(fp);
}

void criaFicheiroHTML(Pagina pag) {
	FILE *fp = NULL;
	char path[strlen(pag->titulo)+15];
	strcpy(path,"pages/");
	strcat(path,pag->titulo);
	strcat(path,".html");

 	fp = fopen(path, "w");
	if(fp) {
		criaPagina(pag,fp);
		fclose(fp);
	}
}