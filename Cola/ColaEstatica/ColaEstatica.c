#include "ColaEstatica.h"
#include "string.h"


void* copiarAVector(void *vecLIzq, void *vecLDer, void *destino, const void* origen, size_t tamDato);
void* copiarDeVector(const void *vecLIzq, const void *vecLDer, void *destino, const void* origen, size_t tamDatoDestino, size_t tamDatoOrigen);
void *calcularFinDato(const void *vecLIzq, const void* vecLDer, const void *origen, size_t tamDatoOrigen);


void crearCola(Cola *pc)
{
    pc->frente = pc->fondo = pc->vCola;
    pc->tamDisponible = TAM_COLA;
}


int ponerEnCola(Cola *pc, const void *dato, size_t tam)
{
    if(tam + sizeof(size_t) > pc->tamDisponible)
        return 0;

    pc->fondo = copiarAVector(pc->vCola, pc->vCola + TAM_COLA, pc->fondo, &tam, sizeof(size_t));
    pc->fondo = copiarAVector(pc->vCola, pc->vCola + TAM_COLA, pc->fondo, dato, tam);

    pc->tamDisponible -= tam + sizeof(size_t);

    return 1;
}


int sacarDeCola(Cola *pc, void *dato, size_t tam)
{
    if(pc->tamDisponible == TAM_COLA)
        return 0;

    size_t tamAElemEncolado;

    pc->frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, &tamAElemEncolado, pc->frente, sizeof(size_t), sizeof(size_t));
    pc->frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, dato, pc->frente, tam, tamAElemEncolado);

    pc->tamDisponible += tamAElemEncolado + sizeof(size_t);

    return 1;
}


int verFrenteCola(const Cola *pc, void *dato, size_t tam)
{
    if(pc->tamDisponible == TAM_COLA)
        return 0;

    size_t tamAElemEncolado;

    void* frente = pc->frente;

    frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, &tamAElemEncolado, frente, sizeof(size_t), sizeof(size_t));
    frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, dato, frente, tam, tamAElemEncolado);


    return 1;

}


void vaciarCola(Cola *pc)
{
    pc->frente = pc->fondo = pc->vCola;
    pc->tamDisponible = TAM_COLA;
}


int colaVacia(const Cola *pc)
{
    return pc->tamDisponible == TAM_COLA;
}


int colaLlena(const Cola *pc, size_t tam)
{
    return tam + sizeof(size_t) > pc->tamDisponible;
}


void* copiarAVector(void *vecLIzq, void *vecLDer, void *destino, const void* origen, size_t tamDato)
{
    size_t cantACopiar = tamDato;
    size_t cantACopiar1erMC = vecLDer - destino;

    memcpy(destino, origen, cantACopiar1erMC);
    cantACopiar -= cantACopiar1erMC;

    if(cantACopiar > 0)
    {
        destino = vecLIzq;
        origen += cantACopiar1erMC;
        memcpy(destino, origen, cantACopiar);
    }

    return destino + cantACopiar;
}


void* copiarDeVector(const void *vecLIzq, const void *vecLDer, void *destino, const void* origen, size_t tamDatoDestino, size_t tamDatoOrigen)
{
    size_t cantACopiar = min(tamDatoOrigen, tamDatoDestino);
    size_t cantACopiar1erMC = vecLDer - origen;

    void *finDato = calcularFinDato(vecLIzq, vecLDer, origen, tamDatoOrigen);

    memcpy(destino, origen, cantACopiar1erMC);

    cantACopiar -= cantACopiar1erMC;

    if(cantACopiar > 0)
    {
        origen = vecLIzq;
        destino += cantACopiar1erMC;
        memcpy(destino, origen, cantACopiar);
    }


    return finDato;
}


void *calcularFinDato(const void *vecLIzq, const void* vecLDer, const void *origen, size_t tamDatoOrigen)
{
    const void *finDato = origen + tamDatoOrigen;

    if(finDato > vecLDer)
        finDato = vecLIzq + (finDato - vecLDer);

    return (void*)finDato;
}
