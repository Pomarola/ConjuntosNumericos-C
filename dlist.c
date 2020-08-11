#include "dlist.h"

DList* dlist_crear(char *nombre) {
  DList* lista = malloc(sizeof(DList));
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
  strcpy(lista->nombre, nombre);
  return lista;
}

void dlist_destruir(DList* lista) {
  DNodo *nodoAEliminar;
  while (lista->primero) {
    nodoAEliminar = lista->primero;
    lista->primero = nodoAEliminar->sig;
    free(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
  free(lista->nombre);
  free(lista);
}

void dlist_insertar_final(DList* lista, void *dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;

  if (lista->ultimo) {
    lista->ultimo->sig = nuevoNodo;
  }
  if (!lista->primero) {
    lista->primero = nuevoNodo;
  }
  lista->ultimo = nuevoNodo;
}

void imprimir_dlist_pantalla(DList * lista, FuncionVisitante imprimir) {
  if (lista) {
    DNodo* nodo = lista->primero;
    if (!nodo)
      printf("Ø\n");
    else {
      for (; nodo->sig != NULL; nodo = nodo->sig) {
          imprimir(nodo->dato);
          printf(",");
      }
      imprimir(nodo->dato);
      printf("\n");
    }
  }
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
  if (!primero)
    return segundo;
  if (!segundo)
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
  if (!primero || !primero->sig)
    return primero;

  DNodo *mitad = dividir_lista(primero);

  primero = merge_sort(primero, comparar);
  mitad = merge_sort(mitad, comparar);

  return merge(primero, mitad, comparar);
}

void dlist_merge_sort(DList* lista, FuncionCompara comparar) {
  if (lista->primero) {

    DNodo *nodo = lista->primero;

    nodo = merge_sort(nodo, comparar);

    lista->primero = nodo;

    for (; nodo != NULL; nodo = nodo->sig)
      lista->ultimo = nodo;
  }
}