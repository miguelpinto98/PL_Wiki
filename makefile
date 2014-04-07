SRC = htmlpage.c linkedlist/linkedlist.c auxstruct.c 
CCFLAGS = -O2 -Wextra
CCC = gcc
FILE = PLIKIPEDIA

$(FILE): $(SRC:.c=.o)
	flex parserXML.fl
	$(CCC) -o $(FILE) $(CCFLAGS) lex.yy.c $(SRC)

clean:
	rm -f *.o lex.yy.c