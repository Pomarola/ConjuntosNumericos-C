#include "slist.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista, FuncionDestruir destruir) {
  SNodo *nodoAEliminar = lista;

  if (lista) {
    while (lista->sig) {
      nodoAEliminar = lista;
      lista = lista->sig;

      destruir(nodoAEliminar->dato);
      free(nodoAEliminar);
    }
    destruir(lista->dato);
    free(lista);
  }
}

SList slist_insertar(SList lista, void *dato, FuncionComparar comparar,
                     FuncionDestruir destruir) {
  SList comienzo = lista;

  if (!lista) {
    SNodo *nodo = malloc(sizeof(SNodo));
    nodo->dato = dato;
    nodo->sig = NULL;
    return nodo;
  }

  while (lista->sig && !(comparar(lista->dato, dato))) {
    lista = lista->sig;
  }

  if (comparar(lista->dato, dato)) {
    destruir(lista->dato);
    lista->dato = dato;

  } else {
    SNodo *nodo = malloc(sizeof(SNodo));
    nodo->dato = dato;
    nodo->sig = NULL;
    lista->sig = nodo;
  }

  return comienzo;
}

void *slist_buscar(SList lista, void *dato, FuncionComparar comparar) {
  int encontro = 0;

  while (lista && encontro == 0) {
    if (comparar(lista->dato, dato))
      encontro = 1;
    else
      lista = lista->sig;
  }

  if (encontro == 1)
    return lista->dato;
  return NULL;
}
