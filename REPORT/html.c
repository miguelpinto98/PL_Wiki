#include "structs.h"

void criaHeader(char *tit, FILE* fp) {
  fputs("<!DOCTYPE html><html lang=\"pt\"><head>",fp);
  fprintf(fp, "<title>%s</title>", tit);
  fputs("<meta charset=\"utf-8\" />",fp);
  fputs("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />",fp);
  fputs("<link rel=\"stylesheet\" href=\"assets/css/css1.css\" />",fp);
  fputs("<link rel=\"stylesheet\" href=\"assets/css/css2.css\" />",fp);
  fputs("<link rel=\"stylesheet\" href=\"assets/css/css3.css\" />",fp);
  fputs("<link rel=\"stylesheet\" href=\"assets/css/vendor.css\" />",fp);
  fputs("</head>",fp);
}

void criaCabecalho(Report r, FILE* fp) {
  fputs("<body><header class=\"header\">",fp);
  fprintf(fp,"<div class=\"cabecalho\">%s",r->institution);
  fprintf(fp,"<span>%s</span>",r->titulo);
  fputs("</div></header>",fp);
}

void criaContent(Report r, FILE* fp){
  fprintf(fp,"<div class=\"titulo\"><strong>%s</strong></div>",r->titulo);
  fprintf(fp,"<div class=\"subtitulo\">%s</div>",r->subtitulo);
  fprintf(fp,"<div class=\"data\">%s</div>",r->date);
}


void criaAutores(LinkedList la, FILE* fp){
  LinkedElem a = la->elems;

   fputs("<div class=\"autores\"><ul>", fp);
    while(a){
      fputs("<li><div class=\"nome\">",fp);
      fprintf(fp,"<strong>%s</strong></div>",a->nome);
      fprintf(fp,"<div class=\"nid\">%s</div>",a->id);
      fprintf(fp,"<div class=\"email\">%s</div>",a->email);
      fprintf(fp,"<div class=\"url\">%s</div>",a->url);
      fprintf(fp,"<div class=\"afiliacao\">%s</div></li>",a->affiliation);
      a=a->next;
    }
  fputs("</ul></div>", fp);
}

void criaResumo(LinkedList lp, FILE* fp){
  fputs("<div class=\"container well\">",fp);
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span4\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Resumo</h2>",fp);

  LinkedElem p = lp->elems;
  while(p){
    fprintf(fp,"<p>%s</p>",p->item);
    p=p->next;
  }
  fputs("</div></div>",fp);
}


void criaAgradecimentos(LinkedList lp, FILE* fp){
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span4\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Agradecimentos</h2>",fp);

  LinkedElem p = lp->elems;
  while(p){
    fprintf(fp,"<p>%s</p>",p->item);
    p=p->next;
  }
  fputs("</div></div>",fp);
}
        

void criaPalavras(LinkedList lp, FILE* fp){
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span4\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Palavras-Chave</h2>",fp);
  fputs("<ul>",fp);
  LinkedElem p = lp->elems;
  while(p){
    fprintf(fp,"<li>%s</li>",p->item);
    p=p->next;
  }
  fputs("</ul>",fp);
  fputs("</div></div>",fp);
}


void criaIndice(LinkedList lp, FILE* fp){
  int c=1;
  int sc=1;
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span4 indice\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Índice</h2>",fp);
  fputs("<ul>",fp);
  LinkedElem p = lp->elems;
  while(p){
    fprintf(fp,"<li><a class=\"scroll\" href=\"relatorio.html#c%d\">%s</a></li>",c,p->nome);
    c++;
    LinkedElem sub = p->elems;
    fputs("<ul>", fp);
      while(sub){
        fprintf(fp,"<li><a class=\"scroll\" href=\"relatorio.html#c%d%d\">%s</a></li>",c,sc,sub->nome);
        sc++;
        sub=sub->next;  
      }
      fputs("</ul>", fp);
    p=p->next;
  }
  fputs("</ul>",fp);
  fputs("</div></div></div>",fp);
  fputs("<div class=\"divider\"></div>",fp);
}

void criaImagem(FILE* fp){
  fprinf(fp,"<img src=\"%s\" height=\"%d\" width=\"%d\">",path, a,l);
}

void criaCapitulos(LinkedList lc, FILE* fp){
  int c=1, sc=1;
  fputs("<div class=\"container well\">",fp);
  LinkedElem p = lc->elems;
  while(p){
    fprintf(fp,"<div id=\"%d\" class=\"row\" style=\"margin-bottom:60px;\">",c);
    fputs("<div class=\"span4\">", fp);
    fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">", fp);
     fprints(fp, "<span>%d</span>%s</h2>", %c,p->nome);
    c++;

    LinkedElem sub = p->elems;
      while(sub){
        fputs("<h3 style=\"color:#F39C12; margin-bottom:10px;\">", fp);
        fprints(fp, "<span>%d.%d</span>%s</h3>", %c,%sc,sub->nome);



        /*PARAGRAFOS*/
        sc++;
        sub=sub->next;  
      }
      fputs("</div>", fp);
      fputs("</ul>", fp);
    p=p->next;
  }
  fputs("</div></div></body></html>", fp);
}


void criaPagina(Report r, LinkedList la, Capitulo c, FILE *fp) {
  criaHeader(r->titulo, fp);
  criaCabecalho(r, fp);
  criaContent(r,fp);
  criaAutores(a,fp);
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
                   

   /* <!-- JAVASCRIPT INSERTS -->
        <script src="assets/js/jquery.js"></script>
        <script src="assets/js/bootstrap-alert.js"></script>
        <script src="assets/js/bootstrap-collapse.js"></script>
        <script src="assets/js/bootstrap-dropdown.js"></script>
        <script src="assets/js/bootstrap-modal.js"></script>
        <script src="assets/js/bootstrap-tab.ja"></script>
        <script src="assets/js/bootstrap-prettify.js"></script>
        <script src="assets/js/bootstrap-tooltip.js"></script>
        <script src="assets/js/bootstrap-transition.js"></script>
        <script src="assets/js/bootstrap-typeahead.js"></script>
        <script src="assets/js/5f4fd25b.vendor-util.js"></script>
        <script src="assets/js/5f4fd25b.5917523f.main.js"></script>  
    <!-- JAVASCRIPT INSERTS -->*/