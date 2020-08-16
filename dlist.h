#ifndef __DLIST_H__
#define __DLIST_H__
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
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

typedef void (*FuncionVisitar) (void *dato);

typedef int (*FuncionComparar) (void *dato1, void *dato2);

typedef int (*FuncionIguales) (void *dato1, void *dato2);

//  Devuelve una lista vacía.
DList *dlist_crear(char *nombre);

//  Destruccion de la lista.
void dlist_destruir(void* lista);

//  Agrega un elemento al final de la lista.
void dlist_insertar_final(DList* lista, void *dato);

void dlist_imprimir(DList * lista, FuncionVisitar imprimir);

//  Dado el primer nodo de la lista, devuelve el nodo de la mitad de la lista,
//  y corta su ruta al anterior, dividiendo la lista en 2 partes.
DNodo *dividir_lista(DNodo * primero);

// Dado el primer nodo de la lista y el primer nodo de otra lista,
// une las dos listas ordenadamente y devuelve el primer nodo de esta.
DNodo *merge(DNodo * primero, DNodo * segundo, FuncionComparar comparar);

// Dado el primer nodo de la lista, la ordena recursivamente y 
// devuelve el primer nodo de esta lista ordenada.
DNodo *merge_sort(DNodo * primero, FuncionComparar comparar);

//  Dadas una dlist y una funcion de comparacion,
//  devuelve una dlist ordenada por merge sort y elimina los intervalos repetidos.
void dlist_merge_sort(DList* lista, FuncionComparar comparar, FuncionIguales iguales);


#endif /* __DLIST_H__ */