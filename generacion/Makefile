CC=gcc
ASM=nasm

ASMFLAGS=-g -f elf32
LDFLAGS=-m32

SRC=$(wildcard *.asm)
BIN=$(patsubst %.asm, %, $(SRC))
OBJ=$(patsubst %, %.o, $(BIN))
LIB=alfalib.o

MAINS_SRC=$(wildcard main*.c)
MAINS_BIN=$(patsubst %.c, %, $(MAINS_SRC))
MAINS_OBJ=$(patsubst %, %.o, $(MAINS_BIN))
MAINS_LIB=generacion.o

GEN = $(patsubst %, %_gen.asm, $(MAINS_BIN))

all: $(MAINS_BIN) $(GEN)
	@echo "Make asm to compile the asm files"

asm: $(BIN)

$(GEN):%_gen.asm: %
	@echo "\t>> Generating $@"
	./$^ $@
	@SRC=$(wildcard *.asm)
	@BIN=$(patsubst %.asm, %, $(SRC))
	@OBJ=$(patsubst %, %.o, $(BIN))


$(MAINS_BIN):%: %.o generacion.o
	$(CC) -o $@ $^

$(MAINS_OBJ):%.o: %.c
	$(CC) -c -o $@ $<

$(OBJ):%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

$(BIN):%: %.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rfv $(BIN) $(OBJ) $(MAINS_BIN) $(MAINS_OBJ) $(GEN)
