

BIN = generado1 generado2 generado3 generado4
CC=gcc
ASM=nasm

ASMFLAGS=-g -f elf32
LDFLAGS=-m32

OBJ = $(patsubst %, %.o, $(BIN))
LIB=alfalib.o

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	#CC=gcc-6
	ASMFLAGS=-g -f macho32
	LIB=alfalibmac.o
	LDFLAGS=-m32
endif

all: $(BIN)

$(OBJ):%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

$(BIN):%: %.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rfv $(BIN) $(OBJ)

