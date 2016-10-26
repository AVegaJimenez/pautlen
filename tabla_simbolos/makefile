BIN = prueba_tabla
OBJ = main.o tablaSimbolos.o tablaHash.o

all: ${BIN}

${BIN}:%: ${OBJ}
	gcc -o $@ $^ -g -Wall

%.o: %.c
	gcc -o $@ -c $< -g -Wall

.PHONY: clean

clean:
	rm -v ${BIN} ${OBJ}
