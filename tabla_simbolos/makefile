BIN = prueba
OBJ = main.o tablaSimbolos.o tablaHash.o

all: ${BIN}

${BIN}:%: ${OBJ}
	gcc -o $@ $^

%.o: %.c
	gcc -o $@ -c $<

.PHONY: clean

clean:
	rm -v ${BIN} ${OBJ}
