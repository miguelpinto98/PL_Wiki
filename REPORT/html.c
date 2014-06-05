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

  if(r->subtitulo)
    fprintf(fp,"<div class=\"subtitulo\">%s</div>",r->subtitulo);
  
  fprintf(fp,"<div class=\"data\">%s</div>",r->date);
}

void criaAutores(LinkedList la, FILE* fp){
  LinkedElem aux = la->elems;

   fputs("<div class=\"autores\"><ul>", fp);
    while(aux){
      Autor a = (Autor) aux->data;
      
      fputs("<li><div class=\"nome\">",fp);
      fprintf(fp,"<strong>%s</strong></div>",a->nome);
      if(a->id)
        fprintf(fp,"<div class=\"nid\">%s</div>",a->id);
      if(a->email)
        fprintf(fp,"<div class=\"email\">%s</div>",a->email);
      if(a->url)
        fprintf(fp,"<div class=\"url\">%s</div>",a->url);
      if(a->affiliation)
        fprintf(fp,"<div class=\"afiliacao\">%s</div></li>",a->affiliation);
      
      aux=aux->next;
    }
  fputs("</ul></div>", fp);
}

void criaResumo(Report r, FILE* fp){
  fputs("<div class=\"container well\">",fp);
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span11\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Resumo</h2>",fp);
  fprintf(fp,"<p>%s</p>",r->resumo);
  fputs("</div></div>",fp);
}

void criaAgradecimentos(Report r, FILE* fp){
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span11\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Agradecimentos</h2>",fp);
  fprintf(fp,"<p>%s</p>",r->agradecimentos);
  fputs("</div></div>",fp);
}
        
void criaPalavras(LinkedList lp, FILE* fp){
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span11\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Palavras-Chave</h2>",fp);
  fputs("<ul>",fp);

  LinkedElem p = lp->elems;
  while(p){
    fprintf(fp,"<li>%s</li>",p->data);
    p=p->next;
  }
  fputs("</ul>",fp);
  fputs("</div></div>",fp);
}

void criaIndice(LinkedElem lp, FILE* fp){
  int c=1;
  int sc=1;
  fputs("<div class=\"row\" style=\"margin-bottom:60px;\">",fp);
  fputs("<div class=\"span11 indice\">",fp);
  fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">Índice</h2>",fp);
  fputs("<ul>",fp);
  
  LinkedElem p = lp;
  while(p) {
    Capitulo cap = (Capitulo) p->data;
    fprintf(fp,"<li><a class=\"scroll\" href=\"#c%d\">%s</a></li>",c,cap->nome);
    c++;
    
    /*
    LinkedElem sub = p->elems;
    fputs("<ul>", fp);
      while(sub){
        fprintf(fp,"<li><a class=\"scroll\" href=\"relatorio.html#c%d%d\">%s</a></li>",c,sc,sub->nome);
        sc++;
        sub=sub->next;  
      }*/
    
    fputs("</ul>", fp);
    p=p->next;
  }
  fputs("</ul>",fp);
  fputs("</div></div>",fp);
  fputs("<div class=\"divider\"></div>",fp);
}

void fechaCaixa(FILE* fp){
  fputs("</div>",fp);
}
/*
void criaImagem(FILE* fp){
  fprinf(fp,"<img src=\"%s\" height=\"%d\" width=\"%d\">",path, a,l);
}
*/
void criaCapitulos(LinkedElem lc, FILE* fp){
  int c=1, sc=1;
  fputs("<div class=\"container well\">",fp);
  LinkedElem aux = lc;
  
  while(aux) {
    Capitulo cap = (Capitulo) aux->data;

    fprintf(fp,"<div id=\"%d\" class=\"row\" style=\"margin-bottom:60px;\">",c);
    fputs("<div class=\"span11\">", fp);
    fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">", fp);
    
    fprintf(fp,"<span>%d </span>%s</h2>",c,cap->nome);
    c++;
    
    LinkedElem sub = cap->elementos->elems;
    while(sub){
      Elemento e = (Elemento) sub->data;
      
      if(e->para) {
        Paragrafo p = (Paragrafo) e->para;

        fputs("<h3 style=\"color:#F39C12; margin-bottom:10px;\">", fp);
        fprintf(fp, "<span></span>%s</h3>",p->item);
      }
        //PARAGRAFOS
        sc++;
        sub=sub->next;  
      }
      fputs("</div>", fp);
      fputs("</ul>", fp);
    
    aux=aux->next;
  }
  fputs("</div></div></body></html>", fp);
}


void criaPagina(Report r, LinkedList lautores, LinkedList lchaves, LinkedList lcaps) {
  FILE *fp = NULL;
  fp = fopen("teste.html", "w");

  criaHeader(r->titulo, fp);
  criaCabecalho(r, fp);
  criaContent(r,fp);
  criaAutores(lautores,fp);
  criaResumo(r,fp);
  criaAgradecimentos(r,fp);
  criaPalavras(lchaves,fp);

  if(r->toc) {
    criaIndice(lcaps->elems,fp);
    fechaCaixa(fp);
  }
  
  criaCapitulos(lcaps->elems,fp);
  
  fclose(fp);
}