NAME = report
generatedFiles = lex.yy.c y.tab.c y.tab.h
sourceFiles = funcs.c report.h
EXEC = report2007
T=2

$(EXEC): $(NAME).fl $(NAME).y
	flex $(NAME).fl
	yacc -d $(NAME).y 
	gcc $(sourceFiles) $(generatedFiles) -o $(EXEC) pkg-config --cflags --libs glib-2.0`

clean: $(generatedFiles) $(EXEC)
	rm $(generatedFiles) $(EXEC)

test: $(EXEC)
	./$(EXEC) testes/t$(T).txt

