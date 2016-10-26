BIN = pruebaMorfo
CFLAGS = -Wall -ansi -pedantic
FLEXFLAGS =

all: ${BIN}

${BIN}:%: lex.yy.o %.o
	gcc -o $@ $^

lex.yy.o: lex.yy.c
	gcc ${FLEXFLAGS} -c -o $@ $<

%.o: %.c
	gcc ${CFLAGS} -c -o $@ $<

lex.yy.c: alfa.l
	flex $<

.PHONY: clean

clean:
	rm -v ${BIN} *.o lex.yy.c
