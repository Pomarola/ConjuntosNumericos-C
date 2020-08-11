#ifndef __DLIST_H__
#define __DLIST_H__
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct _DNodo {
  void *dato;
  struct _DNodo *ant;
  struct _DNodo *sig;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
  char *nombre;
} DList;

typedef void (*FuncionVisitante) (void *dato);

typedef int (*FuncionCompara) (void *dato1, void *dato2);

//  Devuelve una lista vacía.
DList *dlist_crear(char *nombre);

//  Destruccion de la lista.
void dlist_destruir(DList* lista);

//  Agrega un elemento al final de la lista.
void dlist_agregar_final(DList* lista, void *dato);

void imprimir_dlist_pantalla(DList * lista, FuncionVisitante imprimir);

//  Dado el primer nodo de la lista, devuelve el nodo de la mitad de la lista,
//  y corta su ruta al anterior, dividiendo la lista en 2 partes.
DNodo *dividir_lista(DNodo * primero);

// Dado el primer nodo de la lista y el primer nodo de otra lista,
// une las dos listas ordenadamente y devuelve el primer nodo de esta.
DNodo *merge(DNodo * primero, DNodo * segundo, FuncionCompara comparar);

// Dado el primer nodo de la lista, la ordena recursivamente y 
// devuelve el primer nodo de esta lista ordenada.
DNodo *merge_sort(DNodo * primero, FuncionCompara comparar);

//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por merge sort mediante esa funcion.
void dlist_merge_sort(DList* lista, FuncionCompara comparar);


#endif /* __DLIST_H__ */