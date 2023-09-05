#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(x,y) (((x) < (y))? (x): (y))

typedef struct sNodo
{
    void* dato;
    size_t tamBytes;
    struct sNodo *sig;
}Nodo;

typedef Nodo *Pila;

void crearPila(Pila *pp);
int ponerEnPila(Pila *pp, const void *dato, size_t cantBytes);
int sacarDePila(Pila *pp, void *dato, size_t cantBytes);
int pilaVacia(const Pila *pp);
int pilaLlena(const Pila *pp, size_t cantBytes);
int verTope(const Pila *pp, void *dato, size_t cantBytes);
void vaciarPila(Pila *pp);

#endif // PILADINAMICA_H_INCLUDED
