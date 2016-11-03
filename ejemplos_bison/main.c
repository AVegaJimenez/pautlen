#include <stdio.h>
int yyparse();

int main(int argc, char** argv) {
	extern FILE* yyin;
	yyin = fopen(argv[1], "r");
	if(argc!=2) {
		return -1;
	}
	if(yyparse()!=0){
		printf("EXPRESION INCORRECTA\n");
	} else {
		printf("EXPRESION CORRECTA\n");
	}
}
