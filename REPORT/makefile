report: report.l report.y
	flex report.l
	yacc -d report.y
	gcc lex.yy.c y.tab.c -o report

clean:
	rm lex.yy.c y.tab.c report