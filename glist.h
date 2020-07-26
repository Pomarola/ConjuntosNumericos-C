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

GList glist_crear();

GList glist_insertar_ordenado(GList lista, void* dato);


#endif /* __GLIST_H__ */