#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <stdio.h>

#define MIN(X, Y) ((X) < (Y))? X : Y

typedef struct sNodo
{
    void *dato;
    size_t tamElem;
    struct sNodo *sig;
}Nodo;


typedef Nodo *Lista;

typedef void (*Accion) (void*, void*);
typedef int (*Cmp) (const void*, const void *);

void crearLista(Lista *pl);
int ponerAlFinalLista(Lista *pl, const void *pd, size_t tam);
int ponerAlComienzoLista(Lista *pl, const void *pd, size_t tam);
int ponerEnPosicionLista(Lista* pl, const void* pd, size_t tam, unsigned pos);
int ponerEnOrdenLista(Lista *pl, const void *pd, size_t tam, Cmp cmp);

int sacarInicioLista(Lista *pl, void *pd, size_t tam);
int sacarFinal(Lista *pl, void *pd, size_t tam);
int sacarElementoParticular(Lista* pl, void* pd, size_t tam, void *elemSacar, Cmp cmp);


void ordenarLista(Lista *pl, int cmp(const void *d1, const void *d2));
void recorrerLista(const Lista *pl, void *extra, Accion accion);


#endif // LISTASIMPLE_H_INCLUDED