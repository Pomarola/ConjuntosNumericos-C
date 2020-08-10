#include "conjunto.h"

Intervalo *crear_intervalo(Intervalo dato) {
  Intervalo *nuevoIntervalo = malloc(sizeof(Intervalo));
  nuevoIntervalo->inicio = dato.inicio;
  nuevoIntervalo->final = dato.final;

  return nuevoIntervalo;
}

int intervalo_valido(Intervalo dato) {
  if (dato.inicio > dato.final)
    return 0;
  return 1;
}

int intersecar(Intervalo primero, Intervalo segundo) {
  return !(primero.final < segundo.inicio || primero.inicio > segundo.final);
}

DoubleList insertar_intervalo_final(DoubleList lista, Intervalo dato) {
    Intervalo* nuevoIntervalo = crear_intervalo(dato);
    dlist_insertar_final(lista, nuevoIntervalo);
    return lista;
}

DoubleList conjunto_union(char* nombre, DoubleList lista1, DoubleList lista2){
    DoubleList unionConjuntos = dlist_crear(nombre);
    DNodo* nodo1 = lista1->primero,* nodo2 = lista2->primero;
    Intervalo intervaloAux;

    int iniNodo1, finNodo1, iniNodo2, finNodo2;
    while(nodo1 && nodo2){
        intervaloAux.inicio = ((Intervalo*) (nodo1->dato))->inicio <= ((Intervalo*) (nodo2->dato))->inicio ?
         ((Intervalo*) (nodo1->dato))->inicio : ((Intervalo*) (nodo2->dato))->inicio;
        if


        insertar_intervalo_final(unionConjuntos, intervaloAux);
    }
}