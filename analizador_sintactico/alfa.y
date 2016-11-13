%{
#include <stdio.h>
int yylex();
int yyerror();
extern int morf_err;
FILE* out;
%}

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
%token TOK_IDENTIFICADOR      

/* Constantes */ 

%token TOK_CONSTANTE_ENTERA   
%token TOK_TRUE               
%token TOK_FALSE              

/* Errores */
%token TOK_ERROR
%left '+' '-'
%left '*' '/'
%right MENOSU
%%
              
programa: TOK_MAIN TOK_CORCHETEIZQUIERDO declaraciones funciones sentencias TOK_CORCHETEDERECHO {fprintf(out, "<programa> ::= main {<declaraciones> <funciones> <sentencias> }");}

declaraciones: declaracion 			{fprintf(out, "<declaraciones> ::= <declaracion>");}
	| declaracion declaraciones 	{fprintf(out, "<declaraciones> ::= <declaracion> <declaraciones>");}

declaracion: clase identificadores TOK_PUNTOYCOMA
clase: clase_escalar
	| clase_vector

clase_escalar: tipo

tipo: TOK_INT
	| TOK_BOOLEAN

clase_vector: TOK_ARRAY tipo
	| TOK_ARRAY tipo constante_entera

identificadores: identificador
	| identificador TOK_COMA identificadores

funciones: funcion funciones 					
	|								{/*VER GRAMATICA BIEN*/} 

funcion: TOK_FUNCTION tipo identificador TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_CORCHETEIZQUIERDO declaraciones funciones sentencias TOK_CORCHETEDERECHO

parametros_funcion: parametro_funcion resto_parametros_funcion

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion
	| 														{/*VER GRAMATICA BIEN*/} 

parametro_funcion: tipo identificador

declaraciones_funcion: declaraciones
	|

sentencias: sentencia
	| sentencia sentencias

sentencia: sentencia_simple TOK_PUNTOYCOMA
	| bloque

sentencia_simple: asignacion
	| lectura
	| escritura
	| retorno_funcion

bloque: condicional
	| bucle

asignacion: identificador TOK_ASIGNACION exp
	| elemento_vector TOK_ASIGNACION exp

elemento_vector: identificador
	| identificador exp

condicional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_CORCHETEIZQUIERDO sentencias TOK_CORCHETEDERECHO
	| TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_CORCHETEIZQUIERDO sentencias TOK_CORCHETEDERECHO TOK_ELSE TOK_CORCHETEIZQUIERDO sentencias TOK_CORCHETEDERECHO

bucle: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_CORCHETEIZQUIERDO sentencias TOK_CORCHETEDERECHO

lectura: TOK_SCANF identificador

escritura: TOK_PRINTF exp

retorno_funcion: TOK_RETURN exp

exp: exp TOK_MAS exp
	| exp TOK_MENOS exp
	| exp TOK_DIVISION exp
	| exp TOK_ASTERISCO exp
	| TOK_MENOS exp %prec MENOSU							
	| exp TOK_AND exp
	| exp TOK_OR exp
	| TOK_NOT exp
	| identificador
	| constante
	| TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO							
	| TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO
	| elemento_vector
	| identificador TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO
	;

lista_expresiones: exp resto_lista_expresiones
	|

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones
	|

comparacion: exp TOK_IGUAL exp
	| exp TOK_DISTINTO exp
	| exp TOK_MENORIGUAL exp
	| exp TOK_MAYORIGUAL exp
	| exp TOK_MENOR exp
	| exp TOK_MAYOR exp


constante: constante_entera			{printf("REGLA: constante: TOK_CTE_ENTERA\n");}
		 | constante_logica			{printf("REGLA: constante: TOK_CTE_REAL\n");}
		 ;

constante_logica: TOK_TRUE
	| TOK_FALSE

constante_entera: TOK_CONSTANTE_ENTERA 				{/* REVISAR */}

identificador: TOK_IDENTIFICADOR


%%

int yyerror(char* s) {
	if(morf_err==1) return -1;
	printf("\nERROR SINTACTICO\n");
	return -1;
}
