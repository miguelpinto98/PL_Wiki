#include "structs.h"

void inserePackages(FILE* f) {
	fputs("\\documentclass[12pt,letterpaper]{article}\n", f);
	fputs("\\usepackage[portuguese]{babel}\n", f);
	fputs("\\usepackage[utf8x]{inputenc}\n", f);
	fputs("\\usepackage{indentfirst}\n", f);
	fputs("\\usepackage{geometry}\n", f);
	fputs("\\usepackage{ucs}\n", f);
	fputs("\\usepackage{amsmath}\n", f);
	fputs("\\usepackage{amsfonts}\n", f);
	fputs("\\usepackage{amssymb}\n", f);
	fputs("\\usepackage{graphicx}\n", f);
	fputs("\\usepackage[lofdepth,lotdepth]{subfig}\n", f);
	fputs("\\usepackage{unitsdef}\n", f);
	fputs("\\usepackage{float}\n", f);
	fputs("\\usepackage{booktabs}\n", f);
	fputs("\\usepackage{lastpage}\n", f);
	fputs("\\usepackage{fancyhdr}\n", f);
	fputs("\\geometry{left=18mm,right=18mm,top=21mm,bottom=21mm}\n", f);
	fputs("\\renewcommand{\\unitvaluesep}{\\hspace*{4pt}}\n", f);
	fputs("\\batchmode\n", f);
	fputs("\\bibliographystyle{plain}\n", f);
	fputs("\\pagestyle{plain}\n", f);
	fputs("\\pagenumbering{arabic}\n", f);
	fputs("\\pagestyle{fancy}\n", f);
	fputs("\\usepackage{lmodern}\n", f);
	fputs("\\newcommand*{\\escape}[1]{\\texttt{\\textbackslash#1}}\n", f);
	fputs("\\newcommand*{\\escapeI}[1]{\\texttt{\\expandafter\\string\\csname #1\\endcsname}}\n", f);
	fputs("\\newcommand*{\\escapeII}[1]{\\texttt{\\char`\\\\#1}}\n", f);
}
    
void criaAutoresTex(FILE* f, LinkedElem la){
	LinkedElem aux = la;
	fputs("\\author{", f);
	while(aux) {
		Autor a = (Autor) aux->data;
		fprintf(f,"%s\\\\", a->nome);

		if(a->id)
			fprintf(f,"\\texttt{%s}\\\\",a->id);
		if(a->email)
			fprintf(f,"\\texttt{%s}\\\\",a->email);
		if(a->url)
			fprintf(f,"\\texttt{%s}\\\\",a->url);
		if(a->affiliation)
			fprintf(f,"\\texttt{%s}\\\\",a->affiliation);

		fputs("\\and",f);
		aux=aux->next;
	}
	fprintf(f,"%s\\\\", "");
	fputs("\\vspace*{2.0in}\n", f);
	fputs("}", f);
}

void criaTitulo(Report r, FILE*f){

	if(r->institution) {
		fprintf(f, "\\title{ %s\\\\",r->institution);
		fputs("\\vspace*{0.60in}", f);
	}
	fprintf(f, "%s\\\\",r->titulo);
	
	if(r->subtitulo) {
		fprintf(f, "{\\small %s}",r->subtitulo);
		fputs("\\vspace*{1.55in}}", f);
	}
	if(r->date)
		fprintf(f, "\\date{%s}\n",r->date);
}

void ambienteResumo(FILE  *f) {
	fputs("\\newenvironment{resumo}\n", f);
	fputs("{\n", f);
	fputs("\\begin{center}\n", f);
	fputs("\\begin{minipage}[t]{500 pt}\n", f);
	fputs("\\vspace{5mm}\n", f);
	fputs("\\emph{\\textbf{Resumo}}\n", f);
	fputs("\\\\[-2mm]\n", f);
	fputs("\\line(1,0){500}\n", f);
	fputs("\\\\[-4.25 mm]\n", f);
	fputs("\\line(1,0){500}\n", f);
	fputs("\\\\\n", f);
	fputs("}\n", f);
	fputs("{\n", f);
	fputs("\\normalsize\n", f);
	fputs("\\\\[2mm]\n", f);
	fputs("\\footnotesize\\textbf{Palavras-Chave: \\footnotesize\\@palabras}",f);
	fputs("\\\\[-2mm]",f);
	fputs("\\line(1,0){500}",f);
	fputs("\\\\[0.5cm]",f);
	fputs("\\end{minipage}",f);
	fputs("\\end{center}",f);
	fputs("}",f);
}
/*	
\def\palabras#1{\gdef\@palabras{#1}}
\palabras{Palavras.}
*/

void criaCabecalhoTEX(Report r, FILE* f) {
	fprintf(f, "\\lhead{%s - %s}",r->titulo, r->subtitulo);
	if(r->institution)
		fprintf(f, "\\rhead{%s}",r->institution);
	fputs("\\cfoot{\\thepage\\ de \\pageref{LastPage}}\n", f);
}


void criaResumoTEX(Report r, FILE*f){
	fputs("\\begin{document}\n", f);
	fputs("\\maketitle\n", f);
	fputs("\\newpage\n", f);

	if(r->toc) {
		fputs("\\tableofcontents\n", f);
		fputs("\\newpage", f);
	}
	if(r->lof) {
		fputs("\\listoffigures\n", f);
		fputs("\\newpage", f);
	}
	if(r->lot) {
		fputs("\\listoftables\n", f);
		fputs("\\newpage", f);
	}
	fputs("\\begin{resumo}\n", f);
	fprintf(f,"%s",r->resumo);
	fputs("\\end{resumo}\n", f);
}

void escrever(LinkedList lcaps, FILE *fp) {
	LinkedElem aux = lcaps->elems;

	while(aux) {
		Capitulo c = (Capitulo) aux->data;
		fputs("\\newpage\n", fp);
		fprintf(fp,"\\section{%s}\n",c->nome);

		LinkedElem aux2 = c->elementos->elems;
		while(aux2) {
			Elemento e = (Elemento) aux2->data;

			if(e->para) {
				fprintf(fp,"%s\n\n",e->para->item);
			}
			aux2 = aux2->next;
		}
		aux = aux->next;
	}

}

/*
void criaSection(char* t, char* texto, FILE* f){
	
	
	fprintf(f,"%s",texto);
}

void criaSubSection(char* t, char* texto, FILE* f){
	fprintf(f,"\\subsection{%s}",t);
	fprintf(f,"%s",texto);
}


void criaFigure(char* img, FILE* f){
	fputs("\\begin{figure}[H]",f);
	fprintf(f, "\\includegraphics[scale=0.41]{%s.png}",img);
	fputs("\\end{figure}[H]",f);
}
*/
void fechar(FILE* f){
	fputs("\\end{document}", f);
}


void criaPaginaPDF(LinkedList laut, Report r, LinkedList lcaps) {
	FILE *fp = NULL;
  	fp = fopen("zzz.tex", "w");

  	inserePackages(fp);
  	criaAutoresTex(fp,laut->elems);
  	criaTitulo(r,fp);
  	ambienteResumo(fp);
  	criaCabecalhoTEX(r,fp);
  	criaResumoTEX(r,fp);
  	escrever(lcaps,fp);

  	fechar(fp);

  	fclose(fp);
}



