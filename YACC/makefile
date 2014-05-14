config: y.tab.c lex.yy.c
	cc -o config y.tab.c -lm

y.tab.c: config.y
	yacc config.y

lex.yy.c: config.l
	flex config.l