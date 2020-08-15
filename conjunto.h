#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__
#include "dlist.h"
#include <limits.h>

typedef struct _Intervalo {
    int inicio;
    int final;
} Intervalo;

typedef DList* Conjunto;

// Crea un intervalo en memoria con los extremos recibidos y devuelve un puntero a este.
Intervalo *crear_intervalo(int inicio, int final);

// Devuelve 1 si se trata de un intervalo valido, 0 si no lo es.
int intervalo_valido(int inicio, int final);

// Imprime en pantalla el intervalo.
void imprimir_intervalo(void *intervalo);

int conjunto_comparar_string(void* conjunto, void* dato);
int conjunto_comparar_nombre(void* conjunto, void* dato);
int intervalo_comparar (void* intervalo1, void* intervalo2);

// Libera el espacio en memoria ocupado por el intervalo.
void liberar_intervalo(void *intervalo);

// Dados sus extremos; devuelve 1 si los intervalos se intersecan, 0 si no lo hacen.
int intersecar(int inicio1, int final1, int inicio2, int final2);

// Dados 2 punteros a intervalos devuelve el segundo con el resultado de la union entre ambos.
void unificar_intervalos(Intervalo* nodo, Intervalo* aux);

// Dados un char* y 2 conjuntos, crea un conjunto bajo ese nombre, con los intervalos de la union entre los conjuntos.
Conjunto conjunto_union(char* nombre, Conjunto lista1, Conjunto lista2);

// Dados un char* y 2 conjuntos, crea un conjunto bajo ese nombre, con los intervalos de la interseccion entre los conjuntos.
Conjunto conjunto_interseccion(char* nombre, Conjunto lista1, Conjunto lista2);

// Dados un char* y un conjunto, crea un conjunto bajo ese nombre, siendo el complemento de este.
Conjunto conjunto_complemento(char *nombre, Conjunto lista);

// Dados un char* y 2 conjuntos, crea un conjunto bajo ese nombre, con los intervalos de la resta entre los conjuntos.
Conjunto conjunto_resta(char *nombre, Conjunto lista1, Conjunto lista2);

#endif /* __CONJUNTO_H__ */