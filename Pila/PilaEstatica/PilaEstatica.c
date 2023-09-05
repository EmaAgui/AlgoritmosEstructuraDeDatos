#include "PilaEstatica.h"

void vaciarPila(Pila *pp)
{
    pp->tope = TAM_VEC;
}

int verTope(const Pila *pp, void *dato, size_t cantBytes)
{
    size_t tamInfo;

    if(pp->tope == TAM_VEC) ///Pila Vacia
        return 0;

    memcpy(&tamInfo, pp->vec + pp->tope, sizeof(size_t));

    memcpy(dato, pp->vec + pp->tope, MENOR(cantBytes, tamInfo));

    return 1;
}


int pilaLlena(const Pila *pp, size_t cantBytes)
{
    return pp->tope < (cantBytes + sizeof(size_t));
}


int pilaVacia(const Pila *pp)
{
    return pp->tope == TAM_VEC;
}


int sacarDePila(Pila *pp, void *dato, size_t cantBytes)
{
    if(pp->tope == TAM_VEC) ///Pila Vacia
        return 0;

    memcpy(&cantBytes, pp->vec + pp->tope, sizeof(size_t));
    pp->tope += sizeof(size_t);

    memcpy(dato, pp->vec + pp->tope, MENOR(cantBytes, sizeof(dato)));
    pp->tope += cantBytes;

    return 1;
}


int ponerEnPila(Pila *pp, const void *dato, size_t cantBytes)
{
    if(pp->tope < (cantBytes + sizeof(size_t))) ///si no hay lugar salgo
        return 0;

    pp->tope -= cantBytes;
    memcpy(pp->vec + pp->tope, dato, cantBytes);

    pp->tope -= sizeof(size_t);
    memcpy(pp->vec + pp->tope, &cantBytes, sizeof(size_t));

    return 1;
}

void crearPila(Pila *pp)
{
    pp->tope = TAM_VEC;
}

