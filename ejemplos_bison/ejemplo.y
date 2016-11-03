%{
#include <stdio.h>
int yylex();
int yyerror();
extern int morf_err;
%}
%token <entero> TOK_CONSTANTE_ENTERA
%token <real> TOK_CONSTANTE_REAL
%token TOK_ERROR

%start exp
%union {
	int entero;
	double real;
}
%left '+' '-'
%left '*' '/'
%right MENOSU
%%

exp: exp '+' exp {printf("REGLA: exp: exp + exp\n");}
	| exp '-' exp {printf("REGLA: exp: exp - exp\n");}
	| exp '*' exp {printf("REGLA: exp: exp * exp\n");}
	| exp '/' exp {printf("REGLA: exp: exp / exp\n");}
	| '-' exp %prec MENOSU {printf("REGLA: exp: - exp\n");}
	| '('exp')' {printf("REGLA: exp: (exp)\n");}
	|constante {printf("REGLA: exp: constante\n");}
	;

constante: TOK_CONSTANTE_ENTERA{printf("REGLA: constante: TOK_CTE_ENTERA\n");}
		 | TOK_CONSTANTE_REAL{printf("REGLA: constante: TOK_CTE_REAL\n");}
		 ;

%%

int yyerror(char* s) {
	if(morf_err==1) return -1;
	printf("\nERROR SINTACTICO\n");
	return -1;
}
