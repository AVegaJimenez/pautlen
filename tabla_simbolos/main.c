#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaSimbolos.h"

#define BUF_SIZE 1024
#define ALFA_VAL_THRESH -1
#define ALFA_CLOSE_ID "cierre"
#define ALFA_CLOSE_VAL -999

void help() {

}

STATUS alfa_parse(char *buf) {
    INFO_SIMBOLO *info = NULL;
    char *id = NULL;
    int value;
    if(sscanf(buf, "%ms\t%i", &id, &value) == 2) {
        if(value < ALFA_VAL_THRESH) {
            if(!strcmp(id, ALFA_CLOSE_ID) && value == ALFA_CLOSE_VAL) {
                free(id);
                return CerrarFuncion();
            } else {
                info = (INFO_SIMBOLO *) malloc(sizeof(INFO_SIMBOLO));
                if(info == NULL) {
                    free(id);
                    return ERR;
                }
                info->lexema = id;
                info->categoria = FUNCION;
                info->adicional1 = value;
                if(DeclararFuncion(id, info) == ERR) {
                    free(info);
                    free(id);
                    return ERR;
                }
                free(info);
                free(id);
                return OK;
            }
        } else if(value > ALFA_VAL_THRESH) {
            info = (INFO_SIMBOLO *) malloc(sizeof(INFO_SIMBOLO));
            if(info == NULL) {
                free(id);
                return ERR;
            }
            info->lexema = id;
            info->categoria = VARIABLE;
            info->adicional1 = value;
            if(Declarar(id, info) == ERR) {
                free(info);
                free(id);
                return ERR;
            }
            free(info);
            free(id);
            return OK;
        }
    } else if(sscanf(buf, "%ms", &id) == 1) {

    } else {

    }
    return OK;
}

int main(int argc, char **argv) {
    FILE *in = NULL, *out = NULL;
    char buf[BUF_SIZE], **id = NULL;
    INFO_SIMBOLO *info = NULL;
    if(argc != 3) {
        help();
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
    }
}
