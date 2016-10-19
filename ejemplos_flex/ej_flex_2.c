#include <stdio.h>

int yylex();

int main(int argc, char ** argv) {
    FILE * out = NULL;
    int ret;
    extern FILE * yyin;
    extern char * yytext;
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        return 1;
    }
    out = fopen(argv[2], "w");
    if(out == NULL) {
        fclose(yyin);
        return 1;
    }
    while((ret = yylex()) != 0) {
        fprintf(out, "RECONOCIDO %d: %s\n", ret, yytext);
    }
    fclose(yyin);
    fclose(out);
    return 0;
}
