#ifndef GENERACION_H
#define GENERACION_H

#include <stdio.h>

#define ENTERO      	0
#define BOOLEANO    	1
#define REAL        	2


void escribir_cabecera_compatibilidad(FILE* fpasm);

void escribir_subseccion_data(FILE* fpasm);

void escribir_cabecera_bss(FILE* fpasm);

void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano);

void escribir_segmento_codigo(FILE* fpasm);

void escribir_inicio_main(FILE* fpasm);

void escribir_fin(FILE* fpasm);

void escribir_operando(FILE* fpasm, char * nombre, int es_var);

void asignar(FILE * fpasm, char * nombre, int es_inmediato);

void sumar(FILE * fpasm, int es_inmediato_1, int es_inmediato_2);

void restar(FILE * fpasm, int es_inmediato_1, int es_inmediato_2);

void multiplicar(FILE * fpasm, int es_inmediato_1, int es_inmediato_2);

void dividir(FILE * fpasm, int es_inmediato_1, int es_inmediato_2);

void cambiar_signo(FILE * fpasm, int es_inmediato);

void o(FILE * fpasm, int es_inmediato_1, int es_inmediato_2);

void y(FILE * fpasm, int es_inmediato_1, int es_inmediato_2);

void no(FILE * fpasm, int es_inmediato, int cuantos_no);

void leer(FILE * fpasm, char * nombre, int tipo);

void escribir(FILE * fpasm, int es_inmediato, int tipo);

void distinto(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones);

void igual(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones);

void menorigual(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones);

void mayorigual(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones);

void mayor(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones);

void menor(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones);

void inicio_condicional(FILE* fpasm, int es_inmediato, int cuantos_condicionales);

void sino_condicional(FILE* fpasm, int cuantos_condicionales);

void etiqueta_final_condicional_simple(FILE* fpasm, int cuantos_condicionales);

void etiqueta_final_condicional_compuesto(FILE* fpasm, int cuantos_condicionales);

void etiqueta_inicio_while(FILE* fpasm, int cuantos_bucles);

void inicio_bucle(FILE* fpasm, int es_inmediato, int cuantos_bucles);

void etiqueta_final_while(FILE* fpasm, int cuantos_bucles);

void asignar_vector(FILE* fpasm, int es_inmediato);

void escribir_operando_array(FILE* fpasm, char* operando, int es_inmediato, int tamano);

void declarar_funcion(FILE* fpasm, char* nombre, int n_locales);

void retorno_funcion(FILE* fpasm, int es_inmediato);

void llamar_funcion(FILE* fpasm, char* nombre, int n_param);

void escribir_operando_funcion(FILE* fpasm, int n_parametro);

void retorno_funcion(FILE* fpasm, int es_inmediato);

void fin_funcion(FILE* fpasm);

void asignar_local(FILE * fpasm, int n_local, int es_inmediato);

void cambiar_a_valor(FILE* fpasm);
#endif


