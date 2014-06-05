#include "structs.h"

void inserePackages(FILE* f) {
	fputs("\\documentclass[12pt,letterpaper]{article}", f);
	fputs("\\usepackage[portuguese]{babel} ", f);
	fputs("\\usepackage[utf8x]{inputenc}", f);
	fputs("\\usepackage{indentfirst}", f);
	fputs("\\usepackage{geometry}", f);
	fputs("\\usepackage{ucs}", f);
	fputs("\\usepackage{amssymb}", f);
	fputs("\\usepackage[lofdepth,lotdepth]{subfig}", f);
	fputs("\\usepackage{unitsdef}", f);
	fputs("\\usepackage{float}", f);
	fputs("\\usepackage{booktabs}", f);
	fputs("\\usepackage{lastpage}", f);
	fputs("\\usepackage{fancyhdr}", f);
	fputs("\\geometry{left=18mm,right=18mm,top=21mm,bottom=21mm}", f);
	fputs("\\renewcommand{\\unitvaluesep}{\\hspace*{4pt}}", f);
	fputs("\\batchmode", f);
	fputs("\\bibliographystyle{plain}", f);
	fputs("\\pagestyle{plain}", f);
	fputs("\\pagenumbering{arabic}", f);
	fputs("\\pagestyle{fancy}", f);
	fputs("\\usepackage{lmodern}", f);
	fputs("\\newcommand*{\\escape}[1]{\\texttt{\\textbackslash#1}}", f);
	fputs("\\newcommand*{\\escapeI}[1]{\\texttt{\expandafter\\string\\csname #1\\endcsname}}", f);
	fputs("\\newcommand*{\\escapeII}[1]{\\texttt{\\char\\#1}}", f);
}
/*     
void criaAutores(FILE* f, LinkedList la){
	LinkedElem a = la->elems;

	while(elems){
	fputs("\\author{", f);
	fprintf(f,"%s\\\\ \\texttt{%s}\\\\ \\texttt{%s}\\\\ \\texttt{%s}\\\\ \\texttt{%s}\\\\ ",a->nome, a->id, a->email, a->url, a->affiliation);
	fputs("\\and");
	elems=elems->next;
	}
	fputs("\\vspace*{2.0in}", f);
}


void criaTitulo(Report r, FILE*f){
	fprintf(f, "\\title{ %s\\",r->institution);
	fputs("\\vspace*{0.60in}", f);
	fprintf(f, "%s",r->titulo);
	fprintf(f, "{\\small %s}",r->subtitulo);
	fputs("\\vspace*{1.55in}}", f);
	fprintf(f, "\\date{%s}",r->date);
}



void ambienteResumo(){
	fputs("\\newenvironment{resumo}", f);
	fputs("{", f);
	fputs("\\begin{center}", f);
	fputs("\\begin{minipage}[t]{500 pt}", f);
	fputs("\\vspace{5mm}", f);
	fputs("\\emph{\textbf{Resumo}}", f);
	fputs("\\\\[-2mm]", f);
	fputs("\\\\line(1,0){500}", f);
	fputs("\\\\[-4.25 mm]", f);
	fputs("\\line(1,0){500}", f);
	fputs("\\\\", f);
	fputs("}", f);
	fputs("{", f);
	fputs("\\normalsize", f);
	fputs("\\\\[2mm]", f);

}


	\footnotesize\textbf{Palavras-Chave: \footnotesize\@palabras}
	\\[-2mm]
	\line(1,0){500}
	\\[0.5cm]
	\end{minipage}
	\end{center}
}
\def\palabras#1{\gdef\@palabras{#1}}
\palabras{Palavras.}

void criaCabecalho(Report r, FILE* f){
	fprintf(f, "\\lhead{%s - %s}",r->titulo, r->subtitulo);
	fprintf(f, "\\rhead{%s}",r->institution);
	fputs("\\cfoot{\thepage\\ de \\pageref{LastPage}}", f);
}


void criaResumo(char* resumo, FILE*f){
	fputs("\\begin{document}", f);
	fputs("\\maketitle", f);
	fputs("\\newpage", f);
	fputs("\\tableofcontents", f);
	fputs("\\newpage", f);
	fputs("\\tableoffigures", f);
	fputs("\\newpage", f);
	fputs("\\tableoftables", f);
	fputs("\\newpage", f);
	fputs("\\begin{resumo}", f);
	fprintf(f,"%s",resumo);
	fputs("\\end{resumo}", f);
}

void criaSection(char* t, char* texto, FILE* f){
	fputs("\\newpage", f);
	fprintf(f,"\\section{%s}",t);
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

void fechar(FILE* f){
	fputs("\\end{document}", f);
}
*/

criaPaginaPDF() {
	FILE *fp = NULL;
  	fp = fopen("zzz.tex", "w");

  	inserePackages(fp);


  	fclose(fp);
}



