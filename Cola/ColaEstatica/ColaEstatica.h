#ifndef COLAESTATICA_H_INCLUDED
#define COLAESTATICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define min(a,b) ((a) < (b) ? (a) : (b))

#define TAM_COLA 5000

typedef struct 
{
    char vCola[TAM_COLA];
    void *frente;
    void *fondo;
    size_t tamDisponible;
}Cola;



int colaLlena(const Cola *pc, size_t tam);
int colaVacia(const Cola *pc);
void vaciarCola(Cola *pc);
int verFrenteCola(const Cola *pc, void *dato, size_t tam);
int sacarDeCola(Cola *pc, void *dato, size_t tam);
int ponerEnCola(Cola *pc, const void *dato, size_t tam);
void crearCola(Cola *pc);



#endif // COLAESTATICA_H_INCLUDED
