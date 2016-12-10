CC = gcc
BISON = bison
FLEX = flex
ASM=nasm
ALFA=./alfa

BIN = compilador
CFLAGS = -Wall 
CYYFLAGS = 

FLEXFLAGS =

BISONFLAGS = -dyv

ASMFLAGS=-g -f elf32
NASM_LDFLAGS=-m32

ZIPNAME = Fuentes_Perdices_5_compilador.zip
ZIPFILES = *.l *.y *.c *.h Makefile programas_correctos/* alfalib.o

OBJ = tablaSimbolos.o tablaHash.o generacion.o

ALFA_SRC=$(wildcard programas_correctos/*.alfa)
NASM_SRC=$(patsubst %.alfa, %.asm, $(ALFA_SRC))
NASM_BIN=$(patsubst %.asm, %, $(NASM_SRC))
NASM_OBJ=$(patsubst %, %.o, $(NASM_BIN))
NASM_LIB=alfalib.o

all: ${BIN} clean_asm
	make asm

alfa: ${BIN}

asm: $(NASM_BIN)

${BIN}:%: y.tab.o lex.yy.o %.o $(OBJ)
	$(CC) -o $@ $^
	@mv $@ alfa

lex.yy.o: lex.yy.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

y.tab.o: y.tab.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

%.o: %.c
	$(CC) ${CFLAGS} -c -o $@ $<

y.tab.c: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

y.tab.h: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

lex.yy.c: alfa.l y.tab.h
	$(FLEX) $(FLEXFLAGS) alfa.l

$(NASM_SRC):%.asm: %.alfa
	$(ALFA) $< $@

$(NASM_OBJ):%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

$(NASM_BIN):%: %.o $(NASM_LIB)
	$(CC) $(NASM_LDFLAGS) -o $@ $^

clean: clean_asm
	rm -rvf $(ZIPNAME) $(BIN) $(OBJ) lex.yy.c lex.yy.o y.tab.h y.tab.c y.tab.o y.output alfa

clean_asm:
	rm -rvf $(NASM_BIN) $(NASM_OBJ) $(NASM_SRC)

zip: clean
	zip $(ZIPNAME) $(ZIPFILES)
