#include <stdio.h>
#include "generacion.h"

int main (int argc, char ** argv)
{
	FILE * salida;
	int num_nots = 0;

	if (argc != 2) {fprintf (stdout, "ERROR POCOS ARGUMENTOS\n"); return -1;}


	salida = fopen(argv[1],"w");


	escribir_cabecera_compatibilidad(salida);
	escribir_subseccion_data(salida);
	escribir_cabecera_bss(salida);



	declarar_variable(salida, "x", ENTERO, 1);
	declarar_variable(salida, "y", ENTERO, 1);
	declarar_variable(salida, "z", ENTERO, 1);


	escribir_segmento_codigo(salida);
	escribir_inicio_main(salida);

	/* scanf(&x); */
	/* scanf(&y); */

	leer(salida, "x", ENTERO);
	leer(salida,"y",ENTERO);

	/* z = x + y */
	escribir_operando(salida,"x",1);
	escribir_operando(salida,"y",1);
	sumar(salida,0,0);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);

	/* z = x - y */
	escribir_operando(salida,"x",1);
	escribir_operando(salida,"y",1);
	restar(salida,0,0);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);

	/* z = x * y */
	escribir_operando(salida,"x",1);
	escribir_operando(salida,"y",1);
	multiplicar(salida,0,0);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);

	/* z = x / y */
	escribir_operando(salida,"x",1);
	escribir_operando(salida,"y",1);
	dividir(salida,0,0);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);




	escribir_fin(salida);

	fclose(salida);
	return 0;


}
