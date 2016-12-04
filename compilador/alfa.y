%{
#include <stdio.h>
#include "alfa.h"

int yylex();
void yyerror();
extern FILE * out;
extern long yylin;
extern long yycol;
extern int yymorph;

TIPO tipo_actual;
CLASE clase_actual;
int tamano_vector_actual;

INFO_SIMBOLO* read;

INFO_SIMBOLO inserta;
%}

/* Palabras reservadas */
%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

/* Símbolos */
%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR

/* Identificadores  */
%token <atributos> TOK_IDENTIFICADOR

/* Constantes */
%token <atributos> TOK_CONSTANTE_ENTERA
%token TOK_TRUE
%token TOK_FALSE

/* Errores */
%token TOK_ERROR

%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> constante
%type <atributos> exp

%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_ASTERISCO TOK_DIVISION TOK_AND
%right MENOSU TOK_NOT

%union {
  tipo_atributos atributos;
}
%%

programa: TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escribirTabla funciones escribirMain sentencias TOK_LLAVEDERECHA {fprintf(out, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");}
        ;

declaraciones: declaracion {fprintf(out, ";R2:\t<declaraciones> ::= <declaracion>\n");}
             | declaracion declaraciones {fprintf(out, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}
             ;

declaracion: clase identificadores TOK_PUNTOYCOMA {/* Llamar a la tabla de simbolos*/ fprintf(out, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");}
           ;

clase: clase_escalar {fprintf(out, ";R5:\t<clase> ::= <clase_escalar>\n"); clase_actual=ESCALAR;}
     | clase_vector {fprintf(out, ";R7:\t<clase> ::= <clase_vector>\n"); clase_actual=VECTOR;}
     ;

clase_escalar: tipo {fprintf(out, ";R9:\t<clase_escalar> ::= <tipo>\n");}
             ;

tipo: TOK_INT {tipo_actual=ENTERO; fprintf(out, ";R10:\t<tipo> ::= int\n");}
    | TOK_BOOLEAN {tipo_actual=BOOLEANO; fprintf(out, ";R11:\t<tipo> ::= boolean\n");}
    ;

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {tamano_vector_actual = $4.valor_numerico; fprintf(out, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");}
            ;

identificadores: identificador {fprintf(out, ";R18:\t<identificadores> ::= <identificador>\n");}
               | identificador TOK_COMA identificadores {fprintf(out, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}
               ;

funciones: funcion funciones {fprintf(out, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
         | {fprintf(out, ";R21:\t<funciones> ::=\n");}
         ;

funcion: TOK_FUNCTION tipo identificador TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion sentencias TOK_LLAVEDERECHA {fprintf(out, ";R22:\t<funcion> ::=function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");}
       ;

parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(out, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
                  | {fprintf(out, ";R24:\t<parametros_funcion> ::=\n");}
                  ;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(out, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
                        | {fprintf(out, ";R26:\t<resto_parametros_funcion> ::=\n");}
                        ;

parametro_funcion: tipo TOK_IDENTIFICADOR {fprintf(out, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");}
                 ;

declaraciones_funcion: declaraciones {fprintf(out, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
                     | {fprintf(out, ";R29:\t<declaraciones_funcion> ::=\n");}
                     ;

sentencias: sentencia {fprintf(out, ";R30:\t<sentencias> ::= <sentencia>\n");}
          | sentencia sentencias {fprintf(out, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
          ;

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(out, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
         | bloque {fprintf(out, ";R33:\t<sentencia> ::= <bloque>\n");}
         ;

sentencia_simple: asignacion {fprintf(out, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
                | lectura {fprintf(out, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
                | escritura {fprintf(out, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
                | retorno_funcion {fprintf(out, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
                ;

bloque: condicional {fprintf(out, ";R40:\t<bloque> ::= <condicional>\n");}
      | bucle {fprintf(out, ";R41:\t<bloque> ::= <bucle>\n");}
      ;

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp  {
    read = BuscarSimbolo($1.nombre);
    if(read==NULL) {
      fprintf(stderr, "Error semantico. Identificador no encontrado.\n");
      // return -1;
    } else {
      if(read->categoria == FUNCION) {
        fprintf(stderr, "Error semantico. Identificador %s no valido (funcion).\n", $1.nombre);
        // return -1;
      }
      if(read->clase == VECTOR) {
        fprintf(stderr, "Error semantico. Identificador %s no valido (vector).\n", $1.nombre);
        // return -1;
      }
      if(read->tipo != $3.tipo) {
        fprintf(stderr, "Error semantico. Tipos incompatibles.\n");
        // return -1;
  
        }
      fprintf(out, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
    }
  }

          | elemento_vector TOK_ASIGNACION exp {fprintf(out, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");}
          ;

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {fprintf(out, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");}
               ;

condicional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(out, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");}
           | TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(out, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");}
           ;

bucle: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(out, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");}
     ;

lectura: TOK_SCANF TOK_IDENTIFICADOR {
    read = BuscarSimbolo($2.nombre);
    if(read == NULL) {
      //ERROR
    }
    leer(out, $2.nombre, read->tipo); fprintf(out, ";R54:\t<lectura> ::= scanf <identificador>\n");};

escritura: TOK_PRINTF exp {
    escribir(out, !($2.es_direccion), ($2.tipo));

    fprintf(out, ";R56:\t<escritura> ::= printf <exp>\n");}
         ;

retorno_funcion: TOK_RETURN exp {fprintf(out, ";R61:\t<retorno_funcion> ::= return <exp>\n");}
               ;

exp: exp TOK_MAS exp {fprintf(out, ";R72:\t<exp> ::= <exp> + <exp>\n");}
   | exp TOK_MENOS exp {fprintf(out, ";R73:\t<exp> ::= <exp> - <exp>\n");}
   | exp TOK_DIVISION exp {fprintf(out, ";R74:\t<exp> ::= <exp> / <exp>\n");}
   | exp TOK_ASTERISCO exp {fprintf(out, ";R75:\t<exp> ::= <exp> * <exp>\n");}
   | TOK_MENOS exp %prec MENOSU {fprintf(out, ";R76:\t<exp> ::= - <exp>\n");}
   | exp TOK_AND exp {fprintf(out, ";R77:\t<exp> ::= <exp> && <exp>\n");}
   | exp TOK_OR exp {fprintf(out, ";R78:\t<exp> ::= <exp> || <exp>\n");}
   | TOK_NOT exp {fprintf(out, ";R79:\t<exp> ::= ! <exp>\n");}
   | TOK_IDENTIFICADOR {
    strcpy($$.nombre, $1.nombre);
    read = BuscarSimbolo($1.nombre);
    if(read == NULL) {
      //ERROR
    }
    $$.tipo = read->tipo;
    //$$.clase = read->clase;
    $$.es_direccion = 0;
    escribir_operando(out, $1.nombre, 0);
    fprintf(out, ";R80:\t<exp> ::= <identificador>\n");

  }
   | constante {
    escribir_operando(out, $1.nombre, 1);
    fprintf(out, ";R81:\t<exp> ::= <constante>\n");}
   | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {fprintf(out, ";R82:\t<exp> ::= ( <exp> )\n");}
   | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {fprintf(out, ";R83:\t<exp> ::= ( <comparacion> )\n");}
   | elemento_vector {fprintf(out, ";R85:\t<exp> ::= <elemento_vector>\n");}
   | TOK_IDENTIFICADOR TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {fprintf(out, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");}
   ;

lista_expresiones: exp resto_lista_expresiones {fprintf(out, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");}
                 |   {fprintf(out, ";R90:\t<lista_expresiones> ::=\n");}
                 ;

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {fprintf(out, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");}
                       |   {fprintf(out, ";R92:\t<resto_lista_expresiones> ::=\n");}
                       ;

comparacion: exp TOK_IGUAL exp {fprintf(out, ";R93:\t<comparacion> ::= <exp> == <exp>\n");}
           | exp TOK_DISTINTO exp {fprintf(out, ";R94:\t<comparacion> ::= <exp> != <exp>\n");}
           | exp TOK_MENORIGUAL exp {fprintf(out, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");}
           | exp TOK_MAYORIGUAL exp {fprintf(out, ";R96:\t<comparacion> ::= <exp> >= <exp>\n");}
           | exp TOK_MENOR exp {fprintf(out, ";R97:\t<comparacion> ::= <exp> < <exp>\n");}
           | exp TOK_MAYOR exp {fprintf(out, ";R98:\t<comparacion> ::= <exp> > <exp>\n");}
           ;

constante: constante_entera {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; fprintf(out, ";R99:\t<constante> ::= <constante_logica>\n");}
         | constante_logica {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; fprintf(out, ";R100:\t<constante> ::= <constante_entera>\n");}
         ;

constante_logica: TOK_TRUE {$$.tipo = BOOLEANO; $$.es_direccion = 0; fprintf(out, ";R102:\t<constante_logica> ::= true\n");}
                | TOK_FALSE {$$.tipo = BOOLEANO; $$.es_direccion = 0; fprintf(out, ";R103:\t<constante_logica> ::= false\n");}
                ;

constante_entera: TOK_CONSTANTE_ENTERA { $$.tipo = ENTERO; $$.es_direccion = 0; printf("El valor de la constante es %d\n", $1.valor_numerico); fprintf(out, ";R104:\t<constante_entera> ::= <numero>\n");}
                ;

identificador: TOK_IDENTIFICADOR {
    inserta.lexema = $1.nombre;
    inserta.categoria = VARIABLE;
    inserta.clase = clase_actual;
    inserta.tipo = tipo_actual;
    if(clase_actual == VECTOR) {
      inserta.adicional1 = tamano_vector_actual;

    } else {
      /* valor actual */
    }

    Declarar($1.nombre, &inserta);
    declarar_variable(out, $1.nombre, tipo_actual,  1);

    fprintf(out, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");}
             ;

 
escribirTabla: { /* Escribir tabla de simbolos a nasm */ escribir_segmento_codigo(out); }

escribirMain: { escribir_inicio_main(out);}
%%

void yyerror(const char * s) {
    if(!yymorph) {
        printf("****Error sintactico en [lin %ld, col %ld]\n", yylin, yycol);
    }
}
