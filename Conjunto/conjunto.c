#include "conjunto.h"

Intervalo *crear_intervalo(int inicio, int final) {
  Intervalo *nuevoIntervalo = malloc(sizeof(Intervalo));
  nuevoIntervalo->inicio = inicio;
  nuevoIntervalo->final = final;

  return nuevoIntervalo;
}

int intervalo_valido(int inicio, int final) {
  return (final >= inicio);
}

void imprimir_intervalo(void *intervalo) {
  if (((Intervalo *) intervalo)->inicio == ((Intervalo *) intervalo)->final)
    printf("%d", ((Intervalo *) intervalo)->inicio);
  else
    printf("%d:%d", ((Intervalo *) intervalo)->inicio,
           ((Intervalo *) intervalo)->final);
}

int conjunto_comparar_string(void *conjunto, void *string) {
  if (strcmp(((Conjunto) conjunto)->nombre, ((char *) string)) == 0)
    return 1;
  return 0;
}

int conjunto_comparar_nombre(void *conjunto1, void *conjunto2) {
  if (strcmp(((Conjunto) conjunto1)->nombre, ((Conjunto) conjunto2)->nombre) ==
      0)
    return 1;
  return 0;
}

int intervalo_comparar(void *intervalo1, void *intervalo2) {
  return (((Intervalo *) intervalo1)->inicio >
          ((Intervalo *) intervalo2)->inicio);
}

int intervalo_igual(void *intervalo1, void *intervalo2) {
  return (((Intervalo *) intervalo1)->inicio ==
          ((Intervalo *) intervalo2)->inicio);
}

int intersecar(int inicio1, int final1, int inicio2, int final2) {
  return !(final1 < inicio2 || inicio1 > final2);
}

void unificar_intervalos(Intervalo * nodo, Intervalo * aux) {
  aux->inicio = nodo->inicio <= aux->inicio ? nodo->inicio : aux->inicio;
  aux->final = nodo->final >= aux->final ? nodo->final : aux->final;
}

Conjunto conjunto_union(char *nombre, Conjunto lista1, Conjunto lista2) {
  Conjunto unionConjuntos = dlist_crear(nombre);
  DNodo *nodo1 = lista1->primero, *nodo2 = lista2->primero;
  Intervalo *intervaloAux = NULL;
  int aux1, aux2;

  while (nodo1 || nodo2) {
    if (!intervaloAux) {
      if (nodo1) {
        intervaloAux =
            crear_intervalo(((Intervalo *) (nodo1->dato))->inicio,
                            ((Intervalo *) (nodo1->dato))->final);
        nodo1 = nodo1->sig;
      } else {
        intervaloAux =
            crear_intervalo(((Intervalo *) (nodo2->dato))->inicio,
                            ((Intervalo *) (nodo2->dato))->final);
        nodo2 = nodo2->sig;
      }
    } else {
      if (nodo1 && intersecar(((Intervalo *) (nodo1->dato))->inicio,
          ((Intervalo *) (nodo1->dato))->final, 
          (aux1 = intervaloAux->inicio == INT_MAX ? INT_MAX : intervaloAux->inicio + 1),
          (aux2 = intervaloAux->final == INT_MAX ? INT_MAX : intervaloAux->final + 1))) {
        unificar_intervalos(nodo1->dato, intervaloAux);
        nodo1 = nodo1->sig;
      } else if (nodo2 && intersecar(((Intervalo *) (nodo2->dato))->inicio,
                 ((Intervalo *) (nodo2->dato))->final, 
                 (aux1 = intervaloAux->inicio == INT_MAX ? INT_MAX : intervaloAux->inicio + 1),
                 (aux2 = intervaloAux->final == INT_MAX ? INT_MAX : intervaloAux->final + 1))) {
        unificar_intervalos(nodo2->dato, intervaloAux);
        nodo2 = nodo2->sig;
      } else {
        dlist_insertar_final(unionConjuntos, intervaloAux);
        intervaloAux = NULL;
      }
    }
  }
  if (intervaloAux)
    dlist_insertar_final(unionConjuntos, intervaloAux);
  return unionConjuntos;
}

Conjunto conjunto_interseccion(char *nombre, Conjunto lista1, Conjunto lista2) {
  Conjunto interseccionConjuntos = dlist_crear(nombre);
  DNodo *nodo1 = lista1->primero, *nodo2 = lista2->primero;
  Intervalo *intervaloAux;
  int auxInicio, auxFinal;

  while (nodo1 && nodo2) {
    if (intersecar
        (((Intervalo *) (nodo1->dato))->inicio,
         ((Intervalo *) (nodo1->dato))->final,
         ((Intervalo *) (nodo2->dato))->inicio,
         ((Intervalo *) (nodo2->dato))->final)) {
      auxInicio =
          ((Intervalo *) (nodo1->dato))->inicio >=
          ((Intervalo *) (nodo2->dato))->
          inicio ? ((Intervalo *) (nodo1->dato))->
          inicio : ((Intervalo *) (nodo2->dato))->inicio;
      auxFinal =
          ((Intervalo *) (nodo1->dato))->final <=
          ((Intervalo *) (nodo2->dato))->final ? ((Intervalo *) (nodo1->dato))->
          final : ((Intervalo *) (nodo2->dato))->final;

      if (intervalo_valido(auxInicio, auxFinal)) {
        intervaloAux = crear_intervalo(auxInicio, auxFinal);
        dlist_insertar_final(interseccionConjuntos, intervaloAux);
      }

      if (((Intervalo *) (nodo1->dato))->final == auxFinal)
        nodo1 = nodo1->sig;
      else
        nodo2 = nodo2->sig;

    } else {
      if (((Intervalo *) (nodo1->dato))->inicio <
          ((Intervalo *) (nodo2->dato))->inicio)
        nodo1 = nodo1->sig;
      else
        nodo2 = nodo2->sig;
    }
  }
  return interseccionConjuntos;
}

Conjunto conjunto_complemento(char *nombre, Conjunto lista) {
  Conjunto complementoConjunto = dlist_crear(nombre);
  Intervalo *intervaloAux;
  DNodo *nodo = lista->primero;

  if (!nodo) {
    intervaloAux = crear_intervalo(INT_MIN, INT_MAX);
    dlist_insertar_final(complementoConjunto, intervaloAux);

  } else {
    if (((Intervalo *) (nodo->dato))->inicio != INT_MIN) {
      intervaloAux =
          crear_intervalo(INT_MIN, (((Intervalo *) (nodo->dato))->inicio - 1));
      dlist_insertar_final(complementoConjunto, intervaloAux);
    }
    for (; nodo->sig != NULL; nodo = nodo->sig) {
      if (intervalo_valido
          ((((Intervalo *) (nodo->dato))->final + 1),
           (((Intervalo *) (nodo->sig->dato))->inicio - 1))) {
        intervaloAux =
            crear_intervalo((((Intervalo *) (nodo->dato))->final + 1),
                            (((Intervalo *) (nodo->sig->dato))->inicio - 1));
        dlist_insertar_final(complementoConjunto, intervaloAux);
      }
    }
    if (((Intervalo *) (nodo->dato))->final != INT_MAX) {
      intervaloAux =
          crear_intervalo((((Intervalo *) (nodo->dato))->final + 1), INT_MAX);
      dlist_insertar_final(complementoConjunto, intervaloAux);
    }
  }
  return complementoConjunto;
}


Conjunto conjunto_resta(char *nombre, Conjunto lista1, Conjunto lista2) {
  Conjunto conjuntoAux = conjunto_complemento("conjuntoAux", lista2);
  Conjunto restaConjuntos = conjunto_interseccion(nombre, lista1, conjuntoAux);

  dlist_destruir(conjuntoAux);
  return restaConjuntos;
}
