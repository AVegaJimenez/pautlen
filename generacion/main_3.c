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



	declarar_variable(salida, "z", ENTERO, 1);


	escribir_segmento_codigo(salida);
	escribir_inicio_main(salida);

	/* z = x + y */
	escribir_operando(salida,"8",0);
	escribir_operando(salida,"2",0);
	sumar(salida,1,1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);

	/* z = x - y */
	escribir_operando(salida,"8",0);
	escribir_operando(salida,"2",0);
	restar(salida,1,1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);

	/* z = x * y */
	escribir_operando(salida,"8",0);
	escribir_operando(salida,"2",0);
	multiplicar(salida,1,1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);

	/* z = x / y */
	escribir_operando(salida,"8",0);
	escribir_operando(salida,"2",0);
	dividir(salida,1,1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);


	escribir_operando(salida, "8", 0);
	cambiar_signo(salida, 1);
	asignar(salida,"z",1);
	/* printf(z); */
	escribir_operando(salida,"z",1);
	escribir(salida,0,ENTERO);


	escribir_fin(salida);

	fclose(salida);
	return 0;


}
