#ifndef _ALFA_H_

#define _ALFA_H_
#define MAX_LONG 100
struct _tipo_atributos {
	char nombre[MAX_LONG + 1];
	int tipo;
	int valor_numerico;
	int etiqueta;
	int direcciones;
};
typedef struct _tipo_atributos tipo_atributos;
#endif
