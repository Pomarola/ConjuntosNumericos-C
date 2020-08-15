#ifndef __HASH_H__
#define __HASH_H__

#include <math.h>
#include "slist.h"

#define PRIMO 31
#define TAM_TABLA 301

typedef int (*FuncionHash) (void *dato);

int hash_str(void* string);


SList* thash_crear();
void thash_destruir(SList* tabla, FuncionDestruir destruir);
SList* thash_insertar(void* dato, SList* tablaHash, FuncionHash hash, FuncionComparar comparar, FuncionDestruir destruir);
void* thash_buscar(void* dato, SList* tablaHash, FuncionHash hash, FuncionComparar comparar);

#endif /* __HASH_H__ */