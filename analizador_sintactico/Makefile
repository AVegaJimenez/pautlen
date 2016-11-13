all: y.tab.c yy.lex.c
	gcc *.c -Wall -ansi -pedantic
y.tab.c: alfa.y
	bison -dyv alfa.y

yy.lex.c: alfa.l
	flex alfa.l
clean:
	rm -rf lex.yy.c y.tab.c y.tab.h y.output a.out
