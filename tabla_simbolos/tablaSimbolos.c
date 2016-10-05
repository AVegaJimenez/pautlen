#include <stdio.h>
#include "tablaSimbolos.h"

TABLA_HASH *TablaSimbolosGlobal = NULL;
TABLA_HASH *TablaSimbolosLocal = NULL;

STATUS DeclararGlobal(const char *id, INFO_SIMBOLO *desc_id) {
    if(TablaSimbolosGlobal == NULL) {
        TablaSimbolosGlobal = crear_tabla(TABLA_SIMBOLOS_GLOBAL_TAM);
        if(TablaSimbolosGlobal == NULL) {
            return ERR;
        }
    }
    if(buscar_simbolo(TablaSimbolosGlobal, id) == NULL) {
        return insertar_simbolo(TablaSimbolosGlobal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2);
    }
    return ERR;
}

STATUS DeclararLocal(const char *id, INFO_SIMBOLO *desc_id) {
    if(buscar_simbolo(TablaSimbolosLocal, id) == NULL) {
        return insertar_simbolo(TablaSimbolosLocal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2);
    }
    return ERR;
}

INFO_SIMBOLO *UsoGlobal(const char *id) {
    return buscar_simbolo(TablaSimbolosGlobal, id);
}

INFO_SIMBOLO *UsoLocal(const char *id) {
    INFO_SIMBOLO *dato = buscar_simbolo(TablaSimbolosLocal, id);
    return dato == NULL? UsoGlobal(id) : dato;
}

STATUS DeclararFuncion(const char *id, INFO_SIMBOLO *desc_id) {
    if(buscar_simbolo(TablaSimbolosGlobal, id) == NULL) {
        if(insertar_simbolo(TablaSimbolosGlobal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2) == ERR) {
            return ERR;
        }
        liberar_tabla(TablaSimbolosLocal);
        TablaSimbolosLocal = crear_tabla(TABLA_SIMBOLOS_LOCAL_TAM);
        if(TablaSimbolosLocal == NULL) {
            return ERR;
        }
        return insertar_simbolo(TablaSimbolosLocal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2);
    }
    return ERR;
}
