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
	fprintf(fpasm, "__index_out_of_bounds db \"Index out of bounds\\n\", 10, 0\n");
	fprintf(fpasm, "__division_by_zero db \"Division by zero\", 10, 0\n");

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

