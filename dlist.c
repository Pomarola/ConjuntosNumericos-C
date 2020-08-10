#include "dlist.h"

DoubleList dlist_crear(char *nombre) {
  DoubleList lista = malloc(sizeof(DList));
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
  strcpy(lista->nombre, nombre);
  return lista;
}

void dlist_destruir(DoubleList lista) {
  DNodo *nodoAEliminar;
  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
  free(lista->nombre);
  free(lista);
}

void dlist_insertar_final(DoubleList lista, void *dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;

  if (lista->ultimo != NULL) {
    lista->ultimo->sig = nuevoNodo;
  }
  if (lista->primero == NULL) {
    lista->primero = nuevoNodo;
  }
  lista->ultimo = nuevoNodo;
}

DNodo *dividir_lista(DNodo * primero) {
  DNodo *saltoDe2 = primero;
  DNodo *saltoDe1 = primero;

  while (saltoDe2->sig && saltoDe2->sig->sig) {
    saltoDe2 = saltoDe2->sig->sig;
    saltoDe1 = saltoDe1->sig;
  }
  DNodo *mitad = saltoDe1->sig;
  saltoDe1->sig = NULL;

  return mitad;
}

DNodo *merge(DNodo * primero, DNodo * segundo, FuncionCompara comparar) {
  if (primero == NULL)
    return segundo;
  if (segundo == NULL)
    return primero;

  if (comparar(primero->dato, segundo->dato) <= 0) {
    primero->sig = merge(primero->sig, segundo, comparar);
    primero->sig->ant = primero;
    primero->ant = NULL;
    return primero;
  } else {
    segundo->sig = merge(primero, segundo->sig, comparar);
    segundo->sig->ant = segundo;
    segundo->ant = NULL;
    return segundo;
  }
}

DNodo *merge_sort(DNodo * primero, FuncionCompara comparar) {
  if (primero == NULL || primero->sig == NULL)
    return primero;

  DNodo *mitad = dividir_lista(primero);

  primero = merge_sort(primero, comparar);
  mitad = merge_sort(mitad, comparar);

  return merge(primero, mitad, comparar);
}

void dlist_merge_sort(DoubleList lista, FuncionCompara comparar) {
  if (lista->primero != NULL) {

    DNodo *nodo = lista->primero;

    nodo = merge_sort(nodo, comparar);

    lista->primero = nodo;

    for (; nodo != NULL; nodo = nodo->sig)
      lista->ultimo = nodo;
  }
}