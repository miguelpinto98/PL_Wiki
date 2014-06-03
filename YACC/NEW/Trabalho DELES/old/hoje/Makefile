NAME = report
generatedFiles = lex.yy.c y.tab.c y.tab.h
sourceFiles = report.h  funcs.c 
EXEC = report2007
T=9

$(EXEC): $(NAME).fl $(NAME).y
	flex $(NAME).fl
	yacc -d $(NAME).y 
	gcc $(sourceFiles) $(generatedFiles) -o $(EXEC) `pkg-config --cflags --libs glib-2.0`

clean: $(generatedFiles) $(EXEC)
	rm $(generatedFiles) $(EXEC)

test: $(EXEC)
	./$(EXEC) testes/t$(T).txt -h

delete:
	sudo rm -f /usr/bin/$(EXEC)
	sudo rm -f /usr/share/man/man1/$(EXEC).1

install:
	sudo cp $(EXEC).1 /usr/share/man/man1/
	sudo cp $(EXEC) /usr/bin/
	#rm -r ../