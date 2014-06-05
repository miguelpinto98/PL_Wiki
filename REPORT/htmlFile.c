#include "htmlFile.h"

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
      }
    
    fputs("</ul>", fp);*/
    p=p->next;
  }
  fputs("</ul>",fp);
  fputs("</div></div>",fp);
}

void fechaCaixa(FILE* fp){
  fputs("</div>",fp);
  fputs("<div class=\"divider\"></div>",fp);
}

void Imagem(Figura f, FILE* fp){
  fprintf(fp,"<img src=\"%s\" height=\"%s\" width=\"%s\">",f->path,f->format,f->format);
}

void criaTabela(Tabela lc, FILE* fp){
  int l1=0;
  fputs("<div class=\"table-responsive\">",fp);
  fputs("<table class=\"table table-bordered\">",fp);
  
  LinkedElem linhas = lc->rows->elems;
  while(linhas) {
    Row r = (Row) linhas->data;
    LinkedElem aux = r->data->elems;

    if(l1 == 0)
      fputs("<thead><tr>",fp);
    else
      fputs("<tbody><tr>",fp);

    while(aux) {
      Data d = (Data) aux->data;
        if(l1==0) {
          fprintf(fp, "<th>%s</th>",d->value);
        } else {
          fprintf(fp, "<td>%s</td>",d->value);
        }
      aux = aux->next;
    }
      if(l1==0)
        fputs("</tr></thead>",fp);
      else
        fputs("</tr></tbody>",fp);

    l1=1;
    linhas=linhas->next;
  }
  fputs("</table></div>",fp); 
}

void criaCapitulos(LinkedElem lc, FILE* fp){
  int c=1, sc=1;
  fputs("<div class=\"container well\">",fp);
  LinkedElem aux = lc;
  
  while(aux) {
    Capitulo cap = (Capitulo) aux->data;

    fprintf(fp,"<div id=\"c%d\" class=\"row\">",c);
    fputs("<div class=\"span11\">", fp);
    fputs("<h2 style=\"color:#F39C12; margin-bottom:10px;\">", fp);
    
    fprintf(fp,"<span>%d </span>%s</h2>",c,cap->nome);
    c++;
    
    LinkedElem sub = cap->elementos->elems;
    while(sub){
      Elemento e = (Elemento) sub->data;
      
      if(e->para) {
        Paragrafo p = (Paragrafo) e->para;

        fprintf(fp, "<p>%s</p>",p->item);
      }

      if(e->tab) {
        Tabela t = (Tabela) e->tab;
        criaTabela(t,fp);
      }

      if(e->fig) {
        Figura f = (Figura) e->fig;
        Imagem(f,fp);
      }
      
        //PARAGRAFOS
        sc++;
        sub=sub->next;  
      }
      fputs("</div>", fp);
      fputs("</ul>", fp);
    
    aux=aux->next;
  }
  fputs("</div></div></div>", fp);
}

void fechaBody(FILE* fp){
   fputs("</body></html>", fp);
}

void criaScripts(FILE* fp){
  fputs("<script src=\"assets/js/jquery.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-alert.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-collapse.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-dropdown.js\"></script>", fp);

  fputs("<script src=\"assets/js/bootstrap-modal.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-tab.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-prettify.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-tooltip.js\"></script>", fp);

  fputs("<script src=\"assets/js/bootstrap-transition.js\"></script>", fp);
  fputs("<script src=\"assets/js/bootstrap-typeahead.js\"></script>", fp);
  fputs("<script src=\"assets/js/5f4fd25b.vendor-util.js\"></script>", fp);
  fputs("<script src=\"assets/js/5f4fd25b.5917523f.main.js\"></script>", fp);
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
  fechaBody(fp);
  criaScripts(fp);
  
  fclose(fp);
}


