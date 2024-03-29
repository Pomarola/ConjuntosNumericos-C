#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <limits.h>
#include "../DList/dlist.h"

typedef struct _Intervalo {
  int inicio;
  int final;
} Intervalo;

typedef DList *Conjunto;

// Crea un intervalo en memoria con los extremos recibidos y devuelve un puntero a este.
Intervalo *crear_intervalo(int inicio, int final);

// Devuelve 1 si se trata de un intervalo valido, 0 si no lo es.
int intervalo_valido(int inicio, int final);

// Devuelve 1 si los inicios de los intervalos coinciden, 0 si no.
int intervalo_igual(void *intervalo1, void *intervalo2);

// Imprime en pantalla el intervalo.
void imprimir_intervalo(void *intervalo);

// Devuelve 1 si el string coincide con el nombre del conjunto, 0 si no.
int conjunto_comparar_string(void *conjunto, void *string);

// Devuelve 1 si los nombres de los conjuntos coinciden, 0 si no.
int conjunto_comparar_nombre(void *conjunto1, void *conjunto2);

// Devuelve 1 si el inicio del primer intervalo es mayor al del segundo, 0 si no.
int intervalo_comparar(void *intervalo1, void *intervalo2);

// Dados sus extremos; devuelve 1 si los intervalos se intersecan, 0 si no lo hacen.
int intersecar(int inicio1, int final1, int inicio2, int final2);

// Dados 2 punteros a intervalos devuelve el segundo con el resultado de la union entre ambos.
void unificar_intervalos(Intervalo * nodo, Intervalo * aux);

// Dados un char* y 2 conjuntos, crea un conjunto bajo ese nombre, con los intervalos de la union entre los conjuntos.
Conjunto conjunto_union(char *nombre, Conjunto lista1, Conjunto lista2);

// Dados un char* y 2 conjuntos, crea un conjunto bajo ese nombre, con los intervalos de la interseccion entre los conjuntos.
Conjunto conjunto_interseccion(char *nombre, Conjunto lista1, Conjunto lista2);

// Dados un char* y un conjunto, crea un conjunto bajo ese nombre, siendo el complemento de este.
Conjunto conjunto_complemento(char *nombre, Conjunto lista);

// Dados un char* y 2 conjuntos, crea un conjunto bajo ese nombre, con los intervalos de la resta entre los conjuntos.
Conjunto conjunto_resta(char *nombre, Conjunto lista1, Conjunto lista2);

#endif                          /* __CONJUNTO_H__ */
