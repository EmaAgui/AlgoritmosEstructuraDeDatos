#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MINIMO(X, Y) ((X) < (Y))? (X) : (Y)

typedef struct sNodo
{
    void *dato;
    size_t tam;
    struct sNodo *sig;
}Nodo;


typedef struct
{
    Nodo *pri;
    Nodo *ult;
}Cola;


int colaLlena(const Cola *pc, size_t tam);
int colaVacia(const Cola *pc);
void vaciarCola(Cola *pc);
int verFrenteCola(const Cola *pc, void *dato, size_t tam);
int sacarDeCola(Cola *pc, void *dato, size_t tam);
int ponerEnCola(Cola *pc, const void *dato, size_t tam);
void crearCola(Cola *pc);






#endif // COLADINAMICA_H_INCLUDED
