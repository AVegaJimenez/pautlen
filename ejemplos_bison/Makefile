
all: y.tab.c yy.lex.c
	gcc *.c
y.tab.c: ejemplo.y
	bison -dyv ejemplo.y

yy.lex.c: ejemplo.l
	flex ejemplo.l
clean:
	rm -rf yy.lex.c y.tab.c y.tab.h y.output
