NAME = report
generatedFiles = lex.yy.c y.tab.c y.tab.h
sourceFiles = funcs.c report.h
EXEC = report2007
T=11

$(EXEC): $(NAME).fl $(NAME).y
	flex $(NAME).fl
	yacc -d $(NAME).y 
	gcc $(sourceFiles) $(generatedFiles) -o $(EXEC) `pkg-config --cflags --libs glib-2.0`

clean: $(generatedFiles) $(EXEC)
	rm $(generatedFiles) $(EXEC)
	rm -rf css
	rm -rf images

test: $(EXEC)
	./$(EXEC) testes/relatorio.txt -h
	open report.html

delete:
	sudo rm -f /usr/bin/$(EXEC)
	sudo rm -f /usr/share/man/man1/$(EXEC).1
	sudo rm -rf /usr/bin/css/
	sudo rm -rf /usr/bin/images/

install:
	sudo cp $(EXEC).1 /usr/share/man/man1/
	sudo cp $(EXEC) /usr/bin/
	sudo cp -r aux/css/ /usr/bin/css/
	sudo cp -r aux/images/ /usr/bin/images/
	#rm -r ../