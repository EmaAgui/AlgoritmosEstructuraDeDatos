#include "ColaDinamica.h"
#include <string.h>

int colaLlena(const Cola *pc, size_t tam)
{
    void *nodo = malloc(sizeof(Nodo));
    void *dato = malloc(tam);

    free(nodo);
    free(dato);

    return !nodo || !dato;
}


int colaVacia(const Cola *pc)
{
    return !pc->pri;
}


void vaciarCola(Cola *pc)
{
    Nodo *elim;

    while (pc->pri)
    {
        elim = pc->pri;
        pc->pri = elim->sig;
        free(elim->dato);
        free(elim);
    }

    pc->ult = NULL;
}


int verFrenteCola(const Cola *pc, void *dato, size_t tam)
{
    if(!pc->pri)
        return 0;
    memcpy(dato, pc->pri->dato, MINIMO(tam, pc->pri->tam));
    return 1;
}


int sacarDeCola(Cola *pc, void *dato, size_t tam)
{
    Nodo *elim;
    elim = pc->pri;

    if(!elim)
        return 0;

    memcpy(dato, elim->dato, MINIMO(tam, elim->tam));

    pc->pri = elim->sig;

    if(!pc->pri)
        pc->ult = NULL;

    free(elim->dato);
    free(elim);

    return 1;
}


int ponerEnCola(Cola *pc, const void *dato, size_t tam)
{
    Nodo *nue;
    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;

    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam = tam;
    nue->sig = NULL;

    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;

    pc->ult = nue;

    return 1;
}


void crearCola(Cola *pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}
