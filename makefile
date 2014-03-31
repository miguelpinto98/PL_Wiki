V=wiki

$V: $V.fl
	flex $V.fl
	cc -o $V linkedlist/linkedlist.c lex.yy.c struct.c