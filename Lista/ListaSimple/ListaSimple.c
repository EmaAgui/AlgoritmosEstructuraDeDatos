#include "ListaSimple.h"
#include <string.h>
#include <stdlib.h>


void recorrerLista(const Lista *pl, void *extra, Accion accion)
{
    while (*pl)
    {
        accion((*pl)->dato, extra);
        pl = &(*pl)->sig;
    }
}


void ordenarLista(Lista *pl, Cmp cmp)
{
    Lista lOrd = NULL;
    Lista *plOrd;
    Nodo *nodo;

    while (*pl)
    {
        nodo = *pl;
        *pl = nodo->sig;
        plOrd = &lOrd;

        while (*plOrd && cmp(nodo->dato, (*plOrd)->dato) > 0)
            plOrd = &(*plOrd)->sig;
        
        nodo->sig = *plOrd;
        *plOrd = nodo;
    }
    *pl = lOrd;
}


int sacarElementoParticular(Lista* pl, void* pd, size_t tam, void *elemSacar, Cmp cmp)
{
    Nodo *nae;

    if(!*pl)
        return 0;
    
    while (*pl && cmp(elemSacar, (*pl)->dato) != 0)
        pl = &(*pl)->sig;
    
    nae = *pl;

    memcpy(pd, nae->dato, MIN(nae->tamElem, tam));

    *pl = nae->sig;
    
    free(nae->dato);
    free(nae);

    return 1;
}


int sacarFinal(Lista *pl, void *pd, size_t tam)
{
    Nodo *nae;

    if(!*pl)
        return 0;

    while (*pl)
        pl = &(*pl)->sig;
    
    nae = *pl;

    memcpy(pd, nae->dato, MIN(nae->tamElem, tam));

    *pl = NULL;

    free(nae->dato);
    free(nae);

    return 1;
}


int sacarInicioLista(Lista *pl, void *pd, size_t tam)
{
    Nodo *nae;

    if(!*pl)
        return 0;

    nae = *pl;
    
    memcpy(pd, nae->dato, MIN(nae->tamElem, tam));

    *pl = nae->sig;

    free(nae->dato);
    free(nae);

    return 1;
}


int ponerEnOrdenLista(Lista *pl, const void *pd, size_t tam, Cmp cmp)
{
    Nodo *nue;
    int comp;

    while (*pl && (comp = cmp(pd, (*pl)->dato) > 0))
        pl = &(*pl)->sig;
    
    if(!*pl && !comp)
        return -12;
    
    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;
    
    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}


int ponerEnPosicionLista(Lista* pl, const void* pd, size_t tam, unsigned pos)
{
    Nodo *nue;

    while (*pl && pos)
    {
        pl = &(*pl)->sig;
        pos--;
    }
    
    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;
    
    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}


int ponerAlComienzoLista(Lista *pl, const void *pd, size_t tam)
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

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;
    return 1;

}


int ponerAlFinalLista(Lista *pl, const void *pd, size_t tam)
{
    Nodo *nue;

    while(*pl)
        pl = &(*pl)->sig;

    nue = (Nodo*)malloc(sizeof(Nodo));
    if(!nue)
        return 0;
    
    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, pd, tam);
    nue->tamElem = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}


void crearLista(Lista *pl)
{
    *pl = NULL;
}