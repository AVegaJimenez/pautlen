BIN = ej_flex_1 ej_flex_2 ej_flex_3 ej_flex_4

all: ${BIN}

${BIN}:%: %.l %.c
	flex $<
	gcc -o $@ $@.c lex.yy.c
	rm lex.yy.c

.PHONY: clean

clean:
	rm -v ${BIN}
