#include "thash.h"

int hash_str(void* string) {
  long long int key = 0;
  for (int i = 0; ((char*) string)[i] != '\0'; i++)
      key += ((char*) string)[i] * pow(2, (i % 10));
  
  return (int) (key % TAM_TABLA);
}

SList* thash_crear(){
    SList* tablaHash = malloc(sizeof(SList) * TAM_TABLA);
    for (int i = 0; i < TAM_TABLA; i++) {
        tablaHash[i] = slist_crear();
    }
    return tablaHash;
}

void thash_destruir(SList* tablaHash, FuncionDestruir destruir) {
    int i = 0;
    while (i < TAM_TABLA){
        slist_destruir(tablaHash[i], destruir);
        i++;
    }
    free(tablaHash);
}

SList* thash_insertar(void* dato, SList* tablaHash, FuncionHash hash, FuncionComparar comparar, FuncionDestruir destruir) {
    int key = hash(dato);
    tablaHash[key] = slist_insertar(tablaHash[key], dato, comparar, destruir);
    return tablaHash;
}

void* thash_buscar(void* dato, SList* tablaHash, FuncionHash hash, FuncionComparar comparar) {
    int key = hash(dato);
    return slist_buscar(tablaHash[key], dato, comparar);
}
