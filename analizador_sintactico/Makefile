BIN = pruebaSintactico

CFLAGS = -Wall -ansi -pedantic
CFLEXBISONFLAGS = 

BISON_FLAGS = -dyv
FLEX_FLAGS =

CC = gcc
BISON = bison
FLEX = flex

ZIP_NAME = Fuentes_Perdices_5_sintactico.zip

all: ${BIN}

${BIN}:%: y.tab.o lex.yy.o %.o
	$(CC) -o $@ $^

lex.yy.o: lex.yy.c
	$(CC) ${CFLEXBISONFLAGS} -c -o $@ $<

y.tab.o: y.tab.c
	$(CC) ${CFLEXBISONFLAGS} -c -o $@ $<

%.o: %.c
	$(CC) ${CFLAGS} -c -o $@ $<

y.tab.c: alfa.y
	$(BISON) $(BISON_FLAGS) alfa.y

y.tab.h: alfa.y
	$(BISON) $(BISON_FLAGS) alfa.y

lex.yy.c: alfa.l y.tab.h
	$(FLEX) $(FLEX_FLAGS) alfa.l

clean:
	rm -rvf $(BIN) *.o $(ZIP_NAME) lex.yy.c y.tab.h y.tab.c y.output

zip: clean
	zip Fuentes_Perdices_5_sintactico.zip *.l *.y *.c *.h Makefile