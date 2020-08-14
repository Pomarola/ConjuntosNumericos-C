#include "slist.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista, FuncionDestruir destruir) {
    SNodo* nodoAEliminar;
    while(lista){
        nodoAEliminar = lista;
        lista = lista->sig;
        destruir(nodoAEliminar->dato);
        free(nodoAEliminar);
    }
    destruir(nodoAEliminar->dato);
    free(nodoAEliminar);
}

SList slist_insertar(SList lista, void *dato, FuncionComparar comparar, FuncionDestruir destruir) {
    int encontro = 0;
    SList comienzo = lista;
    while (lista->sig && encontro = 0) {
        if(comparar(lista->dato, dato)){
            destruir(lista->dato);
            lista->dato = dato;
            encontro = 1;
        } else {
            SNodo* nodo = malloc(sizeof(SNodo));
            nodo->dato = dato;
            nodo->sig = NULL;
            lista->sig = nodo
        }
    }
    return comienzo;
}
    
void* slist_buscar(SList lista, void *dato, FuncionComparar comparar) {
    int encontro = 0;
    while (lista && encontro = 0) {
        if(comparar(lista->dato, dato))
            encontro = 1;
        lista = lista->sig;
    }
    if (encontro = 1)
        return lista->dato;
    return NULL;
}
