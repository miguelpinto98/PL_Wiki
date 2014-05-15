config: config.l config.y
	flex config.l
	yacc -d config.y
	gcc lex.yy.c y.tab.c -o config

clean:
	rm lex.yy.c y.tab.c config