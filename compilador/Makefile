CC = gcc
BISON = bison
FLEX = flex
ASM=nasm
ALFA=./alfa

BIN = alfa
CFLAGS = -Wall 
CYYFLAGS = 

FLEXFLAGS =

BISONFLAGS = -dyv

ASMFLAGS=-g -f elf32
NASM_LDFLAGS=-m32 -g

ZIPNAME = Fuentes_Perdices_5_compilador.zip
ZIPFILES = *.l *.y *.c *.h Makefile programas_correctos/* programas_error/* ficheros_correccion/* ficheros_correccion_errores/* pytest.py correccion alfalib.o

OBJ = tablaSimbolos.o tablaHash.o generacion.o

# Compilacion de los tests y programas de prueba
ALFA_SRC=$(wildcard programas_correctos/*.alfa)
ALFA_SRC+=$(wildcard ficheros_correccion/*.alfa)
NASM_SRC=$(patsubst %.alfa, %.asm, $(ALFA_SRC))
NASM_BIN=$(patsubst %.asm, %, $(NASM_SRC))
NASM_OBJ=$(patsubst %, %.o, $(NASM_BIN))
NASM_LIB=alfalib.o

# Compilacion de los programas erroneos
TEST_INPUT=$(wildcard ficheros_correccion/*.input)
TESTS=$(patsubst %_*, %, $(TEST_INPUT))
ALFA2_SRC=$(wildcard ficheros_correccion_errores/*.alfa)
#ALFA2_SRC+=$(wildcard programas_error/*.alfa)
NASM2_SRC=$(patsubst %.alfa, %.asm, $(ALFA2_SRC))

all: ${BIN}

asm: $(BIN) $(NASM_BIN)

errores: clean_error $(NASM2_SRC) clean_error

clean_error:
	@rm -rf $(NASM2_SRC)

alfa: y.tab.o lex.yy.o compilador.o $(OBJ)
	$(CC) -o $(ALFA) $^

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

$(NASM2_SRC):%.asm: %.alfa
	@python pytest.py $(ALFA) --args $< $@ --output $<.output;

$(NASM_OBJ):%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

$(NASM_BIN):%: %.o $(NASM_LIB)
	$(CC) $(NASM_LDFLAGS) -o $@ $^

clean: clean_asm
	@rm -rvf $(ZIPNAME) $(BIN) $(OBJ) lex.yy.c lex.yy.o y.tab.h y.tab.c y.tab.o y.output alfa

clean_asm: clean_error
	@echo 'Cleaning asm...'
	@rm -rf $(NASM_BIN) $(NASM_OBJ) $(NASM_SRC) $(NASM2_SRC)

test: asm
	echo 'Running normal execution test'
	@awk '{system("python pytest.py " ((NF==3)? ("--input "$$3) :("") ) " --output "$$2" "$$1)}' correccion

zip: clean
	zip $(ZIPNAME) $(ZIPFILES)
