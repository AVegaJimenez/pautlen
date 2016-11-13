#include <stdio.h>
#include <string.h>

int yylex();
int yyparse();

int main(int argc, char ** argv) {
    FILE * out = NULL;
    int ret;
    extern FILE * yyin;
    extern char * yytext;
    extern int yyleng;
    extern long yylin, yycol;
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        return 1;
    }
    out = fopen(argv[2], "w");
    if(out == NULL) {
        fclose(yyin);
        return 1;
    }

    if(yyparse()!=0){
        printf("EXPRESION INCORRECTA\n");
    } else {
        printf("EXPRESION CORRECTA\n");
    }

    fclose(yyin);
    fclose(out);
    return 0;
}
