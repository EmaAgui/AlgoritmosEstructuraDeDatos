#ifndef PILAESTATICA_H_INCLUDED
#define PILAESTATICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENOR(X,Y) ((X) < (Y)? (X) : (Y))
#define TAM_VEC 10000

typedef struct
{
    char vec[TAM_VEC];
    unsigned tope;
}Pila;

void crearPila(Pila *pp);
int ponerEnPila(Pila *pp, const void *dato, size_t cantBytes);
int sacarDePila(Pila *pp, void *dato, size_t cantBytes);
int pilaVacia(const Pila *pp);
int pilaLlena(const Pila *pp, size_t cantBytes);
int verTope(const Pila *pp, void *dato, size_t cantBytes);
void vaciarPila(Pila *pp);

#endif // PILAESTATICA_H_INCLUDED
