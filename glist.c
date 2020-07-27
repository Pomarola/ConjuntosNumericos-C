#include "glist.h"

GList glist_crear() {
  return NULL;
}

void glist_destruir(GList list, FuncionVisitante liberar) {
  GNodo* nodoAEliminar = list;

  while (nodoAEliminar != NULL) {
    list = list->sig;
    liberar(nodoAEliminar->dato);
    free(nodoAEliminar);
    nodoAEliminar = list;
  }
}

GList glist_insertar_ordenado(GList lista, void* dato) { 
    GNodo* nuevoNodo = malloc(sizeof(GNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;
  
    // si la lista es vacia
    if (lista == NULL) 
        lista = nuevoNodo; 
  
    else if (comparar(lista->dato, nuevoNodo->dato) > 0) { 
        nuevoNodo->sig = lista; 
        lista->ant = nuevoNodo; 
        lista = nuevoNodo; 
    } else { 
        GList nodoMovil = lista; 
  
        // locate the node after which the new node 
        // is to be inserted 
        while (nodoMovil->sig != NULL && comparar(nodoMovil->sig->dato, nuevoNodo->dato) < 0) 
            nodoMovil = nodoMovil->sig; 
    
        nuevoNodo->sig = nodoMovil->sig;

        // if the new node is not inserted 
        // at the end of the list 
        if (nodoMovil->sig != NULL) 
            nodoMovil->sig->ant = nuevoNodo; 
  
        nodoMovil->sig = nuevoNodo; 
        nuevoNodo->ant = nodoMovil; 
    }

    return lista; 
} 

GList glist_push(GList lista, void* dato) {  
    GNodo* nuevoNodo = malloc(sizeof(GNodo));
    nuevoNodo->dato = dato;
  
    nuevoNodo->sig = lista;  
    nuevoNodo->ant = NULL;  
  
    if (lista != NULL)  
        lista->ant = nuevoNodo;  
  
    return nuevoNodo;  
}

GList glist_merge(GList lista1, GList lista2, FuncionCompara comparar) {
    if (lista1 == NULL)
        return lista2;
    if (lista2 == NULL)
        return lista1;

    if (comparar(lista1->dato, lista2->dato) < 0) {
        lista1->sig = merge(lista1->sig, lista2, comparar);
        lista1->sig->ant = lista1;
        lista1->ant = NULL;
        return lista1;
    } else {
        lista2->sig = merge(lista1, lista2->sig, comparar);
        lista2->sig->ant = lista2;
        lista2->ant = NULL;
        return lista2;
    }
}

GList dividir_lista(GList lista) {
    GNodo* saltoDe2 = lista;
    GNodo* saltoDe1 = lista;

    while (saltoDe2->sig && saltoDe2->sig->sig) {
        saltoDe2 = saltoDe2->sig->sig;
        saltoDe1 = saltoDe1->sig;
    }

    GNodo* mitad = saltoDe1->sig;
    saltoDe1->sig = NULL;

    return mitad;
}

GList glist_merge_sort(GList lista, FuncionCompara comparar) {
    if (lista == NULL || lista->sig == NULL)
        return lista;
    GList lista2 = dividir_lista(lista);

    lista = glist_merge_sort(lista, comparar);
    lista2 = glist_merge_sort(lista2, comparar);

    return glist_merge(lista, lista2, comparar);
}