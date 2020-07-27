#ifndef __GLIST_H__
#define __GLIST_H__
#include <stdlib.h>

typedef struct _GNodo {
  void *dato;
  struct _GNodo *ant;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef int (*Compara) (void *dato1, void *dato2);

typedef void (*FuncionVisitante) (void *dato);

typedef int (*FuncionCompara) (void *dato1, void *dato2);

GList glist_crear();

void glist_destruir(GList list, FuncionVisitante liberar);

GList glist_insertar_ordenado(GList lista, void* dato);

GList glist_push(GList lista, void* dato);

GList glist_merge(GList lista1, GList lista2, FuncionCompara comparar);

GList dividir_lista(GList lista);

GList glist_merge_sort(GList lista, FuncionCompara comparar);


#endif /* __GLIST_H__ */