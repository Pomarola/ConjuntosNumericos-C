#include "glist.h"

GList glist_crear() {
  return NULL;
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