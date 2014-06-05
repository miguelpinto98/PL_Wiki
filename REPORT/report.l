%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <ctype.h>
    void yyerror(char *);
%}

%option noyywrap
%option yylineno

%x KEYWORD ABS AKN CODE

%%

"BREPORT" 		{ return BEGINREPORT; }
"EREPORT"		{ return ENDREPORT; }

"BFM"			{ return BEGINFM; }
"EFM"			{ return ENDFM; }

"BTITLE" 		{ return BEGINTITLE; }
"ETITLE"		{ return ENDTITLE; }

"BSUBTITLE"		{ return BEGINSUBTITLE; }
"ESUBTITLE"		{ return ENDSUBTITLE; }

"BAUTHOR"		{ return BEGINAUTHOR; }
"EAUTHOR"		{ return ENDAUTHOR; }

"BNAME"			{ return BEGINNAME; }
"ENAME"			{ return ENDNAME; }

"BNID"			{ return BEGINNID; }
"ENID"			{ return ENDNID; }

"BEMAIL"		{ return BEGINEMAIL; }
"EEMAIL"		{ return ENDEMAIL; }

"BURL"			{ return BEGINURL; }
"EURL"			{ return ENDURL; }

"BAFFILIATION"	{ return BEGINAFFILIATION; }
"EAFFILIATION"	{ return ENDAFFILIATION; }

"BDATE"			{ return BEGINDATE; }
"EDATE"			{ return ENDDATE; }

"BINSTITUTION"	{ return BEGININSTITUTION; }
"EINSTITUTION"	{ return ENDINSTITUTION; }

"BKEYWORD"		{ BEGIN KEYWORD; return BEGINKEYWORD; }
<KEYWORD>{
	"EKEYWORD"	BEGIN INITIAL; return ENDKEYWORD;
	[^\n \t].+	yylval.s = strdup(yytext); return texto;
	.|\n 		;
}

"BABS" 			{ BEGIN ABS; return BEGINABS; }
<ABS>{
	"EABS" 		BEGIN INITIAL; return ENDABS;
	[^\n \t].+	yylval.s = strdup(yytext); return texto;
	.|\n 		;
}

"BAKN" 			{ BEGIN AKN; return BEGINAKN; }
<AKN>{
	"EAKN" 		BEGIN INITIAL; return ENDAKN;
	[^\n \t].+	yylval.s = strdup(yytext); return texto;
	.|\n 		;
}

"TOC"			{ return ICONTENT; }
"LOF"			{ return IFIGURE; }
"LOT"			{ return ITABLE; }

"BBODY"			{ return BEGINBODY; }
"EBODY"			{ return ENDBODY; }

"BCHAP" 		{ return BEGINCHAP; }
"ECHAP" 		{ return ENDCHAP; }

"BPARA"			{ return BEGINPARA; }
"EPARA"			{ return ENDPARA; }

"BFOOT"			{ return BEGINFOOT; }
"EFOOT"			{ return ENDFOOT; }

"BREF"			{ return BEGINREF; }
"EREF"			{ return ENDREF; }

"BXREF"			{ return BEGINXREF; }
"EXREF"			{ return ENDXREF; }

"BCIT"			{ return BEGINCIT; }
"ECIT"			{ return ENDCIT; }

"BTERM"			{ return BEGINITERM; }
"ETERM"			{ return ENDITERM;}

"BBOLD"			{ return BEGINBOLD; }
"EBOLD"			{ return ENDBOLD; }

"BITALIC"		{ return BEGINITALIC; }
"EITALIC"		{ return ENDITALIC; }

"BUNDERLINE"	{ return BEGINUNDERLINE; }
"EUNDERLINE"	{ return ENDUNDERLINE; }

"BFIG"			{ return BEGINFIG; }
"EFIG"			{ return ENDFIG; }

"BGRAPH"		{ return BEGINGRAPH; }
"EGRAPH"		{ return ENDGRAPH; }

"BCAPTION"		{ return BEGINCAPTION; }
"ECAPTION"		{ return ENDCAPTION; }

"BPATH"			{ return BEGINPATH; }
"EPATH"			{ return ENDPATH; }

"BFORMAT"		{ return BEGINFORMAT; }
"EFORMAT"		{ return ENDFORMAT; }

"BTABLE"		{ return BEGINTABLE; }
"ETABLE"		{ return ENDTABLE; }

"BROW"			{ return BEGINROW; }
"EROW"			{ return ENDROW; }

"BDATA"			{ return BEGINDATA; }
"EDATA"			{ return ENDDATA; }

"BSUM"			{ return BEGINSUM; }
"ESUM"			{ return ENDSUM; }

"BLIST"			{ return BEGINLIST; }
"ELIST"			{ return ENDLIST; }

"BCODE"			{ BEGIN CODE; return BEGINCODE; }
<CODE>{
	"ECODE"		BEGIN INITIAL; return ENDCODE;
	[^}\n]+		yylval.s = yytext; return texto;
	[ \t\n;]+ 	;
}

"BSEC"			{ return BEGINSEC; }
"ESEC"			{ return ENDSEC; }

"BBM"			{ return BEGINBM; }
"EBM"			{ return ENDBM; }

[^\n \t].+		{ yylval.s = strdup(yytext); return texto; }

[ \t\n]			;

. 				{ printf("%c\n",*yytext); yyerror("Caracter Desconhecido");  }

<<EOF>> 		{ return 0; }

%%
