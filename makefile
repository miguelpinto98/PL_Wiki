SRC = htmlpage.c linkedlist/linkedlist.c auxstruct.c lex.yy.c
CCFLAGS = -O2 -Wextra
CCC = gcc
FILE = xWiki

$(FILE): $(SRC:.c=.o)
	flex wiki.fl
	$(CCC) -o $(FILE) $(CCFLAGS) $(SRC)

clean:
	rm -f *.o 