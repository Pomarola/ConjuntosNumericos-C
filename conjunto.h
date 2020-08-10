#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__
#include "dlist.h"
#include <stdlib.h>

typedef struct _Intervalo {
    int inicio;
    int final;
} Intervalo;

// Devuelve 1 si los intervalos se intersecan, 0 si no lo hacen.
int intersecar(Intervalo primero, Intervalo segundo);

// Devuelve 1 si se trata de un intervalo valido, 0 si no lo es.
int intervalo_valido(Intervalo dato);

// Crea un intervalo en memoria con los datos recibidos y devuelve un puntero a este.
Intervalo *crear_intervalo(Intervalo dato);


#endif /* __CONJUNTO_H__ */