CC=gcc
ASM=nasm

ASMFLAGS=-g -f elf32
LDFLAGS=-m32

BIN = analisis1 analisis2 analisis3 analisis4 analisis5
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
