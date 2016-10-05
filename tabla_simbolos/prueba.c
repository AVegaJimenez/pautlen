#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "tablaHash.h"



int main (int argc, char ** argv)
{

	int i;
	TABLA_HASH * p_t1;
	TABLA_HASH * p_t2;
	INFO_SIMBOLO * p_sim;
	

	char * str;

	p_t1 = crear_tabla(100);
	p_t2 = crear_tabla(100);


	str = strdup("Hola amigos");

	for (i= 0 ; i< argc; i++)
	{
		insertar_simbolo(p_t1, argv[i], VARIABLE, ENTERO, ESCALAR , 1,2);
		p_sim = buscar_simbolo(p_t1,argv[i]);
		if ( p_sim != NULL )
		{
			fprintf(stdout,"Encontrado %s\n", p_sim->lexema);
			insertar_simbolo(p_t2, p_sim->lexema, p_sim->categoria, p_sim->tipo, p_sim->clase, p_sim->adicional1, p_sim->adicional2);
			borrar_simbolo(p_t1, argv[i]);
		}
		

	}


	for (i=0; i< argc; i++)
	{
		p_sim = buscar_simbolo(p_t2, argv[i]);
		if ( p_sim != NULL )
		{
			fprintf(stdout,"Encontrado %s\n", p_sim->lexema);
			borrar_simbolo(p_t2, argv[i]);
		}
		
		
	}

	free(str);

	liberar_tabla(p_t1);
	liberar_tabla(p_t2);
	return 0;

}