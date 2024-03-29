#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdlib.h>
#include <stddef.h>

typedef struct _SNodo {
  void *dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

typedef void (*FuncionDestruir)(void *dato);

typedef int (*FuncionComparar)(void *dato1, void *dato2);

// Devuelve una lista vacía.
SList slist_crear();

// Destruccion de la lista.
void slist_destruir(SList lista, FuncionDestruir destruir);

// Agrega un elemento a la lista, comparando con los elementos de esta, 
// si coinciden, el elemento es destruido y reemplazado por el nuevo.
// Devuelve el inicio de la lista.
SList slist_insertar(SList lista, void *dato, FuncionComparar comparar,
                     FuncionDestruir destruir);

// Busca un elemento en la lista segun una funcion de comparacion y lo devuelve.
void *slist_buscar(SList lista, void *dato, FuncionComparar comparar);

#endif                          /* __SLIST_H__ */
