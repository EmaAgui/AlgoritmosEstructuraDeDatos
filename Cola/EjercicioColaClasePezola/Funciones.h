#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include "../ColaDinamica/ColaDinamica.h"

#define NOM_ARCH_PED "Pedidos.txt"
#define NOM_ARCH_MAY "PedidosMay.txt"
#define NOM_ARCH_MEN "PedidosMen.txt"

typedef struct
{
    char numeroPed[4];
    char codProd[20];
    unsigned cantidadPedida;
    float precio;
}Pedido;


void actualizarArchivos(const char *nombArchPedTxt, const char *nombreMasCien, const  char *nombreMenCien);
void trozarPed(const char *cad, Pedido *ped);

#endif // FUNCIONES_H_INCLUDED
