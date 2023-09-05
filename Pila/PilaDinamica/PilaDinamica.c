#include "PilaDinamica.h"


void crearPila(Pila *pp)
{
    *pp = NULL;
}


int ponerEnPila(Pila *pp, const void *dato, size_t cantBytes)
{
    Nodo *nue;
    nue = (Nodo*)malloc(sizeof(Nodo));

    if(!nue)
        return 0;

    nue->dato = malloc(cantBytes);

    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    nue->tamBytes = cantBytes;
    memcpy(nue->dato, dato, cantBytes);

    nue->sig = *pp;
    *pp = nue;

    return 1;
}


int sacarDePila(Pila *pp, void *dato, size_t cantBytes)
{
    Nodo *elim;

    if(!*pp)
        return 0;

    elim = *pp;
    *pp = elim->sig;

    memcpy(dato, elim->dato, MINIMO(elim->tamBytes, cantBytes));

    free(elim->dato);
    free(elim);

    return 1;
}


int pilaVacia(const Pila *pp)
{
    return *pp == NULL;
}


int pilaLlena(const Pila *pp, size_t cantBytes)
{
    void *nodo = malloc(sizeof(Nodo));
    void *dato = malloc(cantBytes);

    free(nodo);
    free(dato);

    return nodo == NULL || dato == NULL;
}


int verTope(const Pila *pp, void *dato, size_t cantBytes)
{
    Nodo *tope;

    tope = *pp;

    if(!tope)
        return 0;

    memcpy(dato, tope->dato, MINIMO(cantBytes, tope->tamBytes));

    return 1;

}


void vaciarPila(Pila *pp)
{
    Nodo *elim;

    while(*pp)
    {
        elim = *pp;
        *pp = elim->sig;

        free(elim->dato);
        free(elim);
    }
}


