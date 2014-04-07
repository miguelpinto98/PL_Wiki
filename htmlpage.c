#include "htmlpage.h"

void criaHeader(char *tit, FILE *fp) {
	fputs("<!DOCTYPE html><html lang=\"pt\"><head>",fp);
	fprintf(fp, "<title>%s</title>", tit);
	fputs("<meta charset=\"UTF-8\" /><meta charset=\"UTF-8\" />",fp);
	fputs("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />",fp);
	fputs("<link rel=\"stylesheet\" href=\"assets/css/bootstrap.min.css\" /><link rel=\"stylesheet\" href=\"assets/css/font-awesome.css\" />",fp);
	fputs("<link rel=\"stylesheet\" href=\"assets/css/unicorn.css\" />",fp);
	fputs("</head>",fp);
}

void openContent(FILE *fp) {
	fputs("<body data-color=\"blue\" class=\"flat\"><div id=\"wrapper\"><div id=\"header\"><h1>",fp);
	fputs("<a href=\"index.html\"></a></h1>	<a id=\"menu-trigger\" href=\"index.html#\"><i class=\"fa fa-bars\"></i></a>",fp);
	fputs("</div><div id=\"sidebar\"><ul><li class=\"active\"><a href=\"index.html\"><i class=\"fa fa-book\"></i> <span>Índice</span></a></li>",fp);
	fputs("<li><a href=\"relatorio.html\"><i class=\"fa fa-file\"></i> <span>Relatório</span></a></li>",fp);
	fputs("<li><a href=\"grupo.html\"><i class=\"fa fa-group\"></i> <span>Grupo</span></a></li></ul></div><div id=\"content\">",fp);
}

void criaContentPanel1(Pagina pag, FILE *fp){
	fprintf(fp, "<div id=\"content-header\"><a href=\"https://pt.wikipedia.org/wiki/%s\" ><h1> %s </h1></a></div><div id=\"breadcrumb\">", pag->titulo, pag->titulo);
	fputs("<a class=\"tip-bottom\"><i class=\"fa fa-home\" style=\"margin-bottom:3px\"></i> Plikipedia</a><a href=\"index.html\" title=\"Ir para o índice\">Índice</a>",fp);
	fprintf(fp, "<a href=\"https://pt.wikipedia.org/wiki/%s\" class=\"current\"> %s </a></div><div class=\"container-fluid\"><br/>", pag->titulo, pag->titulo);
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
			fprintf(fp, "<li><a href=\"http://%s\" class=\"current\"> %s </a></li>",aux->data,aux->data);
		if(tipo==3) {
			char *res = strdup(aux->data);

			if(res[0]=='1' && res[1]=='X' && res[2]=='1')
				fprintf(fp, "<i> > %s </i><br>",(res+3));
			else {
				if(res[0]=='2' && res[1]=='X' && res[2]=='2')
					fprintf(fp, " >> %s <br>",(res+3));
				else {
					if(res[0]=='3' && res[1]=='X' && res[2]=='3')
						fprintf(fp, " >>> %s <br>",(res+3));
					else
						fprintf(fp, "<p></p><b> %s </b><br>",aux->data);
				}
			}
		}
		aux=aux->next;
	}

}

void criaContentPanel2(Pagina pag, FILE *fp){
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Links Internos</h5>",fp);
	fprintf(fp, "<span title=\"Número total de links internos\" class=\"label label-info tip-left\" style=\"height:23px; width: 36px; margin-top: 7px;\"> %d </span></div><div class=\"widget-content\"><ul>", pag->linkint->nrelems);
	/* Imprime Links Internos */
	imprimeLinks(pag->linkint,fp,1);
	fputs("</ul></div></div></div></div>",fp);

}

void criaContentPanel3(Pagina pag, FILE *fp){
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Links Externos</h5>",fp);
	fprintf(fp, "<span title=\"Número total de links externos\" class=\"label label-info tip-left\" style=\"height:23px; width: 36px; margin-top: 7px;\"> %d </span></div><div class=\"widget-content\"><ul>", pag->linkext->nrelems);
	/* Imprime Links Externos */
	imprimeLinks(pag->linkext,fp,2);
	fputs("</ul></div></div></div></div>",fp);
}

void criaContentPanel4(Pagina pag, FILE *fp) {
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Secções</h5>",fp);
	fprintf(fp, "<span title=\"Número total de secções\" class=\"label label-info tip-left\" style=\"height:23px; width: 36px; margin-top: 7px;\"> %d </span></div><div class=\"widget-content\"><ul>", pag->seccoes->nrelems);
	/* Imprime Links Externos */
	imprimeLinks(pag->seccoes,fp,3);
	fputs("</ul></div></div></div></div>",fp);
}

void closeFooter(FILE *fp) {
	fputs("</div></div><div class=\"row\"><br><div id=\"footer\" class=\"col-xs-12\">2013 - 2014 Programação de Linguagens.</br></br></div></div></div></body></html>",fp);
}

void criaPagina(Pagina pag, FILE *fp) {
	criaHeader(pag->titulo, fp);
	openContent(fp);
	criaContentPanel1(pag,fp);
	criaContentPanel4(pag,fp);
	criaContentPanel2(pag,fp);
	criaContentPanel3(pag,fp);
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

void criaNumPagina(int num, FILE *fp) {
	fputs("<div id=\"content-header\"><h1>Índice</h1></div><div id=\"breadcrumb\"><a class=\"tip-bottom\"><i class=\"fa fa-home\" style=\"margin-bottom:3px\"></i> Plikipedia</a>",fp);
	fputs("<a class=\"current\">Índice</a></div><div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box\"><div class=\"widget-title\"><h5>Artigos Processados</h5>",fp);
	fprintf(fp, "<span title=\"Número total de artigos processados\" class=\"label label-info tip-left\"> %d </span></div></div></div></div>",num );
}

void criaIndexPages(LinkedElem pages, FILE *fp) {
	LinkedElem aux = pages;
	fputs("<div class=\"row\"><div class=\"col-xs-12\"><div class=\"widget-box widget-messages\"><div class=\"widget-title\"><ul class=\"nav nav-tabs pull-left\"><li class=\"active\"><a href=\"#tabA\" data-toggle=\"tab\">A</a></li>",fp);
	char c = 'B', ant;
	while(c<='Z') {
		fprintf(fp,"<li><a href=\"#tab%c\" data-toggle=\"tab\">%c</a></li>", c, c);
		c++;
	}
	fputs("<li><a href=\"#tab1\" data-toggle=\"tab\">Outros</a></li></ul></div></br><div class=\"widget-content padding\" style=\"height:100%\"><div class=\"tab-content\"><div id=\"tabA\" class=\"tab-pane active\"><ul>",fp);
	
	ant='A';
	c = 'A';
	while(aux) {
		char *tit = aux->data;
		c = tit[0];

		if(c<65 || c>90)
			c = '1';

		if(c!=ant) {
			
			fprintf(fp, "</div></ul><div id=\"tab%c\" class=\"tab-pane\"><ul>",c);
		} 
		
		fprintf(fp, "<li><a href=\"%s.html\"> %s </a></li>", tit,tit);
		ant = c;
		aux = aux->next;
	}
	fputs("</div></ul></div></div></div></div></div><div class=\"white-backdrop\">",fp);
    fputs("<script src=\"assets/js/jquery.min.js\"></script><script src=\"assets/js/jquery-ui.custom.js\"></script><script src=\"assets/js/bootstrap.min.js\"></script>",fp);
}

void geraIndex(LinkedList lpages, FILE *fp) {
	criaHeader("index",fp);
	openContent(fp);
	criaNumPagina(lpages->nrelems, fp);
	criaIndexPages(lpages->elems,fp);
	closeFooter(fp);
}

void criaIndexHTML(LinkedList lpages) {
	FILE *fp = NULL;
 	fp = fopen("pages/index.html", "w");

	if(fp) {
		geraIndex(lpages,fp);
		fclose(fp);
	}
}