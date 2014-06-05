SRC = linkedlist/linkedlist.c structs.c html.c
CCFLAGS = -O2 -Wextra
CCC = gcc
FILE = REPORT

$(FILE): report.l report.y
	flex report.l
	yacc -d report.y
	$(CCC) -o $(FILE) $(CCFLAGS) lex.yy.c y.tab.c $(SRC)

clean:
	rm lex.yy.c y.tab.c report