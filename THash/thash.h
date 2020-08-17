#ifndef __HASH_H__
#define __HASH_H__

#include <math.h>
#include "../SList/slist.h"

#define TAM_TABLA 301

typedef int (*FuncionHash) (void *dato);

// Devuelve una key para la tabla hash segun un string dado.
int hash_str(void* string);

// Crea una tabla hash vacia.
SList* thash_crear();

// Destruccion de la tabla hash
void thash_destruir(SList* tabla, FuncionDestruir destruir);

// Agrega un elemento a la tabla, comparando con los elementos de esta, 
// si coinciden, el elemento es destruido y reemplazado por el nuevo.
// Devuelve el inicio de la tabla.
SList* thash_insertar(void* dato, SList* tablaHash, FuncionHash hash, FuncionComparar comparar, FuncionDestruir destruir);

// Busca un elemento en la tabla segun una funcion de comparacion y lo devuelve.
void* thash_buscar(void* dato, SList* tablaHash, FuncionHash hash, FuncionComparar comparar);

#endif /* __HASH_H__ */