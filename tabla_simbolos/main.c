#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaSimbolos.h"

#define BUF_SIZE 1024
#define ALFA_VAL_THRESH -1
#define ALFA_CLOSE_ID "cierre"
#define ALFA_CLOSE_VAL -999
#define ALFA_HELP "Modo de empleo: %s ENTRADA SALIDA"

void help(char * argv0) {
    printf(ALFA_HELP "\n", argv0);
}

void alfa_parse(char *buf, FILE *out) {
    INFO_SIMBOLO *info = NULL;
    char *id = NULL;
    int scan, value;
    scan = sscanf(buf, "%ms\t%i", &id, &value);
    if(scan == 2) {
        if(value < ALFA_VAL_THRESH) {
            if(!strcmp(id, ALFA_CLOSE_ID) && value == ALFA_CLOSE_VAL) {
                fprintf(out, ALFA_CLOSE_ID "\n");
                free(id);
                CerrarFuncion();
            } else {
                info = crear_info_simbolo(id, FUNCION, ENTERO, ESCALAR, value, 0);
                if(info == NULL) {
                    free(id);
                    return;
                }
                fprintf(out, DeclararFuncion(id, info) == OK? "%s\n" : "-1\t%s\n", id);
                liberar_info_simbolo(info);
                free(id);
            }
        } else if(value > ALFA_VAL_THRESH) {
            info = crear_info_simbolo(id, VARIABLE, ENTERO, ESCALAR, value, 0);
            if(info == NULL) {
                free(id);
                return;
            }
            fprintf(out, Declarar(id, info) == OK? "%s\n" : "-1\t%s\n", id);
            liberar_info_simbolo(info);
            free(id);
        }
    } else if(scan == 1) {
        info = UsoLocal(id);
        fprintf(out, "%s\t%d\n", id, info == NULL? -1 : info->adicional1);
        free(id);
    }
}

int main(int argc, char **argv) {
    FILE *in = NULL, *out = NULL;
    char buf[BUF_SIZE], **id = NULL;
    if(argc != 3) {
        help(argv[0]);
        return 0;
    }
    in = fopen(argv[1], "r");
    if(in == NULL) {
        perror(argv[1]);
        return 1;
    }
    out = fopen(argv[2], "w");
    if(out == NULL) {
        perror(argv[2]);
        return 1;
    }
    while(fgets(buf, BUF_SIZE, in) != NULL) {
        alfa_parse(buf, out);
    }
    fclose(in);
    fclose(out);
}
