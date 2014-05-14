%option noyywrap

%%

=titulo=.*				{ yylval.s = strdup(yytext+8);	return TITULO;}
=nprovas=.*				{ yylval.i=atoi(yytext+9);		return NPROVAS;}
=N=.*					{ yylval.i=atoi(yytext+4);		return N;}
[\t ]					{}

. 						{ fprintf(stderr,"ERRO - %s",yytext); }
%%