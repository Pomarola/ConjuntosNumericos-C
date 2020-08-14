#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdlib.h>
#include <stddef.h>
#include <math.h>

typedef struct _SNodo {
  void *dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

typedef void (*FuncionDestruir) (void *dato);

typedef int (*FuncionComparar) (void *dato1, void *dato2);

SList slist_crear();

void slist_destruir(SList lista, FuncionDestruir destruir);

SList slist_insertar(SList lista, void *dato, FuncionComparar comparar, FuncionDestruir destruir);

void* slist_buscar(SList lista, void *dato, FuncionComparar comparar);



#endif /* __SLIST_H__ */