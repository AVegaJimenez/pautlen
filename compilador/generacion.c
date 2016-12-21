#include "generacion.h"
/**
 * @brief      Escribe la cabecera de compatibilidad
 *
 * @param      fpasm  Puntero al fichero abierto
 */
void escribir_cabecera_compatibilidad(FILE* fpasm)
{

}

/**
 * @brief      Escribe la subseccion del segmento de datos y variables auxiliares
 *
 * @param      fpasm  The fpasm
 */
void escribir_subseccion_data(FILE* fpasm)
{
	fprintf(fpasm, "segment .data\n");
	fprintf(fpasm, "__index_out_of_bounds db \"****Error de ejecucion: Indice fuera de rango.\", 10, 0\n");
	fprintf(fpasm, "__division_by_zero db \"****Error de ejecucion: Division por cero.\", 10, 0\n");

}

/**
 * @brief      Escribe la subseccion del segmento bss y variables auxiliares
 *
 * @param      fpasm  The fpasm
 */
void escribir_cabecera_bss(FILE* fpasm)
{
	fprintf(fpasm, "segment .bss\n");
	fprintf(fpasm, "__esp resd 1\n");
}

/**
 * @brief      Declara una variable en el segmento actual
 *
 * @param      fpasm   The fpasm
 * @param      nombre  Nombre de la variable
 * @param[in]  tipo    Tipo
 * @param[in]  tamano  tamano
 */
void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano)
{
	fprintf(fpasm, "\t _%s resd  %d\n", nombre, tamano);

}


/**
 * @brief      Escribe el segmento de codigo y variables/declaraciones necesarias
 *
 * @param      fpasm  The fpasm
 */
void escribir_segmento_codigo(FILE* fpasm)
{
	fprintf(fpasm, "segment .text\n");
	fprintf(fpasm, "global main\n");
	fprintf(fpasm, "extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
	fprintf(fpasm, "extern print_endofline, print_blank, print_string\n");
	fprintf(fpasm, "extern alfa_malloc, alfa_free, ld_float\n");


}

/**
 * @brief      Escribe el inicio de la función main
 *
 * @param      fpasm  The fpasm
 */
void escribir_inicio_main(FILE* fpasm)
{
	fprintf(fpasm, "main:\n");
	fprintf(fpasm, "mov dword [__esp], esp\n");
}

/**
 * @brief      Escribe el final del programa
 *
 * @param      fpasm  The fpasm
 */
void escribir_fin(FILE* fpasm)
{
	fprintf(fpasm, "jmp near _fin\n");
	fprintf(fpasm, "_error_division_zero:\n");
	fprintf(fpasm, "push dword __division_by_zero\n");
	fprintf(fpasm, "call print_string\n");
	fprintf(fpasm, "add esp, 4\n");
	fprintf(fpasm, "jmp near _fin\n");
	fprintf(fpasm, "_error_index_out_of_bounds:\n");
	fprintf(fpasm, "push dword __index_out_of_bounds\n");
	fprintf(fpasm, "call print_string\n");
	fprintf(fpasm, "add esp, 4\n");
	fprintf(fpasm, "_fin: mov dword esp, [__esp]\n");
	fprintf(fpasm, "ret\n");
}

/**
 * @brief      Escribe el operando en la pila
 *
 * @param      fpasm   The fpasm
 * @param      nombre  Nombre de la variable
 * @param[in]  es_var  Si es variable o literal
 */
void escribir_operando(FILE * fpasm, char * nombre, int es_var)
{
	if(es_var){
		fprintf(fpasm, "push dword _%s\n", nombre);
	}
	else{
		fprintf(fpasm, "push dword %s\n", nombre);
	}
}

/**
 * @brief      Asigna lo que este en el tope de la pila a la variable
 *
 * @param      fpasm         The fpasm
 * @param      nombre        Nombre de la variable
 * @param[in]  es_inmediato  Si es inmediato o es direccion de memoria
 */
void asignar(FILE * fpasm, char * nombre, int es_inmediato)
{
	fprintf(fpasm, "pop dword eax\n");
	fprintf(fpasm, "mov dword [_%s], %s\n", nombre, es_inmediato? "eax" : "[eax]");

}

void sumar(FILE * fpasm, int es_inmediato_1, int es_inmediato_2)
{
	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}

	fprintf(fpasm, "add eax, ebx\n");
	fprintf(fpasm, "push dword eax\n");
}


void cambiar_signo(FILE * fpasm, int es_inmediato)
{
	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}

	fprintf(fpasm, "neg eax\n");
	fprintf(fpasm, "push dword eax\n");
}
void no(FILE * fpasm, int es_inmediato, int cuantos_no)
{

	fprintf(fpasm,"pop dword eax\n");
	if(!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm,"cmp eax , 0\n");
	fprintf(fpasm,"jz _poner1_%d\n",cuantos_no);
	fprintf(fpasm,"push dword 0\n");
	fprintf(fpasm,"jmp _no_end_%d\n", cuantos_no);
	fprintf(fpasm,"_poner1_%d:\n",cuantos_no);
	fprintf(fpasm,"push dword 1\n");
	fprintf(fpasm,"_no_end_%d:\n", cuantos_no);


}

/**********************************************************************************/
void leer(FILE * fpasm, char * nombre, int tipo)
{
	/* GENERA EL CÓDIGO PARA LEEER UNA VARIABLE DE NOMBRE nombre Y TIPO tipo (ESTE
	 * AÑO SÓLO USAREMOS ENTERO Y BOOLEANO) DE CONSOLA LLAMANDO A LAS CORRESPONDIENTES
	 * FUNCIONES DE ALFALIB (scan_int Y scan_boolean) */
	/* GR 5 */
	fprintf(fpasm, "push dword _%s\n", nombre);
	fprintf(fpasm, "call scan_%s\n", tipo==ENTERO?"int":"boolean");
	fprintf(fpasm, "add esp, 4\n");

}

/**********************************************************************************/
void escribir(FILE * fpasm, int es_inmediato, int tipo)
{
	/* GENERA EL CÓDIGO PARA ESCRIBIR POR PANTALLA LO QUE HAYA EN LA CIMA DE LA PILA
	 * TENIENDO EN CUENTA QUE PUEDE SER UN VALOR INMEDIATNO (es_inmediato == 1) O UNA
	 * DIRECCION (es_inmediato == 0) Y QUE HAY QUE LLAMAR A LA CORRESPONDIENTE
	 * FUNCIÓN DE ALFALIB (print_int O print_boolean) DEPENDIENTO DEL TIPO (tipo == BOOLEANO
	 * O ENTERO )
	 * */

	if(!es_inmediato) {
		fprintf(fpasm, "pop dword eax\n");
		fprintf(fpasm, "mov eax, [eax]\n");
		fprintf(fpasm, "push dword eax\n");
	}
	fprintf(fpasm, "call print_%s\n", tipo==ENTERO?"int":"boolean");
	fprintf(fpasm, "add esp, 4\n");
	fprintf(fpasm, "call print_endofline\n");

}

/**********************************************************************************/
void restar(FILE * fpasm, int es_inmediato_1, int es_inmediato_2)
{
	/* SIMILAR A SUMAR */
	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}


	fprintf(fpasm, "sub eax, ebx\n");
	fprintf(fpasm, "push dword eax\n");
}
/**********************************************************************************/
void multiplicar(FILE * fpasm, int es_inmediato_1, int es_inmediato_2)
{
	/* SIMILAR A SUMAR (CUIDADO CON EDX) */
	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}

	fprintf(fpasm, "imul ebx\n");
	fprintf(fpasm, "push dword eax\n");

}
/**********************************************************************************/
void dividir(FILE * fpasm, int es_inmediato_1, int es_inmediato_2)
{
	/* SIMILAR A MULTIPLICAR (CUIDADO CON LA EXTENSIÓN DE SIGNO PREVIA) */
	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "cmp ebx, 0\n");
	fprintf(fpasm, "je near _error_division_zero\n");


	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm, "cdq\n");


	fprintf(fpasm, "idiv ebx\n");
	fprintf(fpasm, "push dword eax\n");

}
/**********************************************************************************/
void o(FILE * fpasm, int es_inmediato_1, int es_inmediato_2)
{
	/* SIMILAR A SUMAR */
 

	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}

	fprintf(fpasm, "or eax, ebx\n");
	fprintf(fpasm, "push dword eax\n");
}

/**********************************************************************************/
void y(FILE * fpasm, int es_inmediato_1, int es_inmediato_2)
{
	/* SIMILAR A SUMAR */
	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}


	fprintf(fpasm, "and eax, ebx\n");
	fprintf(fpasm, "push dword eax\n");
}

void comparacion(FILE* fpasm, int es_inmediato_1, int es_inmediato_2) {
	fprintf(fpasm, "pop dword ebx\n");
	if (!es_inmediato_2) {
		fprintf(fpasm, "mov ebx, [ebx]\n");
	}

	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato_1) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}

	fprintf(fpasm, "cmp eax, ebx\n");
}

void distinto(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones) {
	comparacion(fpasm, es_inmediato_1, es_inmediato_2);

	fprintf(fpasm, "jne near __cmp_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "push dword 0\n");
	fprintf(fpasm, "jmp near __cmp_fin_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_%d: push dword 1\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_fin_%d:\n", cuantas_comparaciones);
}

void igual(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones) {
	comparacion(fpasm, es_inmediato_1, es_inmediato_2);

	fprintf(fpasm, "je near __cmp_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "push dword 0\n");
	fprintf(fpasm, "jmp near __cmp_fin_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_%d: push dword 1\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_fin_%d:\n", cuantas_comparaciones);
}

void menor(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones) {
	comparacion(fpasm, es_inmediato_1, es_inmediato_2);

	fprintf(fpasm, "jl near __cmp_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "push dword 0\n");
	fprintf(fpasm, "jmp near __cmp_fin_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_%d: push dword 1\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_fin_%d:\n", cuantas_comparaciones);
}

void mayor(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones) {
	comparacion(fpasm, es_inmediato_1, es_inmediato_2);

	fprintf(fpasm, "jg near __cmp_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "push dword 0\n");
	fprintf(fpasm, "jmp near __cmp_fin_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_%d: push dword 1\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_fin_%d:\n", cuantas_comparaciones);
}

void mayorigual(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones) {
	comparacion(fpasm, es_inmediato_1, es_inmediato_2);

	fprintf(fpasm, "jge near __cmp_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "push dword 0\n");
	fprintf(fpasm, "jmp near __cmp_fin_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_%d: push dword 1\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_fin_%d:\n", cuantas_comparaciones);
}

void menorigual(FILE* fpasm, int es_inmediato_1, int es_inmediato_2, int cuantas_comparaciones) {
	comparacion(fpasm, es_inmediato_1, es_inmediato_2);

	fprintf(fpasm, "jle near __cmp_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "push dword 0\n");
	fprintf(fpasm, "jmp near __cmp_fin_%d\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_%d: push dword 1\n", cuantas_comparaciones);
	fprintf(fpasm, "__cmp_fin_%d:\n", cuantas_comparaciones);
}

void inicio_condicional(FILE* fpasm, int es_inmediato, int cuantos_condicionales) {
	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm, "cmp eax, 1\n");
	fprintf(fpasm, "jne near __final_condicional_%d\n", cuantos_condicionales);
}

void sino_condicional(FILE* fpasm, int cuantos_condicionales) {
	fprintf(fpasm, "jmp near __final_else_condicional_%d\n", cuantos_condicionales);
	fprintf(fpasm, "__final_condicional_%d:\n", cuantos_condicionales);
}

void etiqueta_final_condicional_simple(FILE* fpasm, int cuantos_condicionales) {
	fprintf(fpasm, "__final_condicional_%d:\n", cuantos_condicionales);
}

void etiqueta_final_condicional_compuesto(FILE* fpasm, int cuantos_condicionales) {
	fprintf(fpasm, "__final_else_condicional_%d:\n", cuantos_condicionales);
}

void etiqueta_inicio_while(FILE* fpasm, int cuantos_bucles) {
	fprintf(fpasm, "__inicio_bucle_%d:\n", cuantos_bucles);
}

void inicio_bucle(FILE* fpasm, int es_inmediato, int cuantos_bucles) {
	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm, "cmp eax, 1\n");
	fprintf(fpasm, "jne near __final_bucle_%d\n", cuantos_bucles);
}

void etiqueta_final_while(FILE* fpasm, int cuantos_bucles) {
	fprintf(fpasm, "jmp near __inicio_bucle_%d\n", cuantos_bucles);
	fprintf(fpasm, "__final_bucle_%d:\n", cuantos_bucles);
}

void escribir_operando_array(FILE* fpasm, char* operando, int es_inmediato, int tamano) {
	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm, "cmp eax, 0\n");
	fprintf(fpasm, "jl near _error_index_out_of_bounds\n");
	fprintf(fpasm, "cmp eax, %d\n", tamano);
	fprintf(fpasm, "jg near _error_index_out_of_bounds\n");

	fprintf(fpasm, "mov dword edx, _%s\n", operando);
	fprintf(fpasm, "lea eax, [edx + eax*4]\n");
	fprintf(fpasm, "push dword eax\n");

}

void asignar_vector(FILE* fpasm, int es_inmediato) {
	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}

	fprintf(fpasm, "pop dword edx\n");

	fprintf(fpasm, "mov [edx], eax\n");
}

void declarar_funcion(FILE* fpasm, char* nombre, int n_locales) {
	fprintf(fpasm, "_%s:\n", nombre);
	fprintf(fpasm, "push ebp\n");
	fprintf(fpasm, "mov ebp, esp\n");
	fprintf(fpasm, "sub esp, %d\n", 4*n_locales);
}

void llamar_funcion(FILE* fpasm, char* nombre, int n_param) {
	fprintf(fpasm, "call _%s\n", nombre);
	fprintf(fpasm, "add esp, %d\n", 4*n_param);
	fprintf(fpasm, "push dword eax\n");
}

void escribir_operando_funcion(FILE* fpasm, int n_parametro) {
	fprintf(fpasm, "mov dword eax, ebp\n");
	fprintf(fpasm, "add eax, %d\n", 4*n_parametro);
	fprintf(fpasm, "push dword eax\n");
}

void retorno_funcion(FILE* fpasm, int es_inmediato) {
	fprintf(fpasm, "pop dword eax\n");
	if (!es_inmediato) {
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm, "mov esp, ebp\n");
	fprintf(fpasm, "pop ebp\n");
	fprintf(fpasm, "ret\n");
} 

void asignar_local(FILE * fpasm, int n_local, int es_inmediato)
{
	fprintf(fpasm, "pop dword eax\n");
	fprintf(fpasm, "mov dword [ebp+%d], %s\n", n_local*4, es_inmediato? "eax" : "[eax]");

}

void cambiar_a_valor(FILE* fpasm) {
	fprintf(fpasm, "pop dword eax\n");
	fprintf(fpasm, "push dword [eax]\n");
}

void fin_funcion(FILE* fpasm) {
	fprintf(fpasm, "mov eax, 0\n");
	fprintf(fpasm, "mov esp, ebp\n");
	fprintf(fpasm, "pop ebp\n");
	fprintf(fpasm, "ret\n");
}
