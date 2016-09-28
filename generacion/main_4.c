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



	declarar_variable(salida, "z", BOOLEANO, 1);


	escribir_segmento_codigo(salida);
	escribir_inicio_main(salida);

	/* scanf(&x); */
	/* scanf(&y); */


	/* z = x || y */
	escribir_operando(salida,"1",0);
	escribir_operando(salida,"0",0);
	o(salida,1,1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,BOOLEANO);

	/* z = x && y */
	escribir_operando(salida,"1",0);
	escribir_operando(salida,"0",0);
	y(salida,1,1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,BOOLEANO);

	/* z =  not x */
	escribir_operando(salida,"1",0);
	no(salida,1, 0);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,BOOLEANO);


	escribir_fin(salida);

	fclose(salida);
	return 0;


}
