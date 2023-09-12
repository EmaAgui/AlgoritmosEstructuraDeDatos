#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../ColaDinamica/ColaDinamica.h"

/**
    Resuelva la simulación de la cola de espera en un cajero automático.
Suponga que cada cliente demora en el mismo un tiempo aleatorio de 1, 3 ó, 5 minutos
con igual probabilidad, y que los clientes llegan al mismo de a uno,
con intervalo de arribo aleatorio de 1, 5 o 9 minutos, con igual probabilidad.
La simulación termina después que la cola queda vacía cinco veces.
**/

typedef struct
{
    char nombre[30];
    unsigned tiempo;
} Cliente;


unsigned calcularTiempoEnCAjero();
void generarCliente(Cliente* cliente);
unsigned calcularTiempoDeArribo();

int main()
{
    unsigned tiempoArribo = calcularTiempoDeArribo();
    Cliente clienteEncajero, cliente;
    int cajeroOcupado = 0; ///0 Falso, 1 Verdadero
    unsigned cantDeVecesColaVacia = 0;
    unsigned minuto = 0;

    Cola colaCajero;
    crearCola(&colaCajero);

    while (cantDeVecesColaVacia < 5)
    {
        printf("Minuto %d\n", minuto);

        if(tiempoArribo == 0)
        {
            generarCliente(&cliente);

            if(!cajeroOcupado)
            {
                cajeroOcupado = 1;
                clienteEncajero = cliente;
                printf("Llego el cliente %s e ingreso al cajero. Va a usar el cajero %d minutos\n", cliente.nombre, cliente.tiempo);
            }
            else
            {
                ponerEnCola(&colaCajero, &cliente, sizeof(cliente));
                printf("Llego el cliente %s e ingreso a la cola. Va a usar el cajero %d minutos\n", cliente.nombre, cliente.tiempo);
            }
            tiempoArribo = calcularTiempoDeArribo();
        }
        if(cajeroOcupado)
        {
            clienteEncajero.tiempo--;
            if(clienteEncajero.tiempo == 0)
            {
                printf("El cliente %s termino de usar el cajero", clienteEncajero.nombre);
                cajeroOcupado = 0;
                if(!colaVacia(&colaCajero))
                {
                    sacarDeCola(&colaCajero, &clienteEncajero, sizeof(clienteEncajero));
                    cajeroOcupado = 1;
                    printf("El Cliente %s, que estaba en la cola ingreso al cajero\n", clienteEncajero.nombre);
                    if(colaVacia(&colaCajero))
                        cantDeVecesColaVacia++;
                }
            }
        }
        minuto++;
        tiempoArribo--;
    }



    return 0;
}

unsigned calcularTiempoDeArribo()
{
    static const unsigned ta[] = {1, 5, 9}; ///vector de tiempo

    return ta[rand() % 3]; ///da uno de los tres valores del vector ta
}


void generarCliente(Cliente* cliente)
{
    char nombres[][30] = {"Juan", "Pedro", "Adrian", "Bernardo", "Carlos", "Dario", "Andrea", "Brenda", "Carla", "Daniela", "Esteban", "Fernanda", "Fernando", "Gaston", "Graciela"};
    strcpy(cliente->nombre, nombres[rand() % 15]);

    cliente->tiempo = calcularTiempoEnCAjero();
}


unsigned calcularTiempoEnCAjero()
{
    unsigned tc[] = {1, 3, 5}; ///vector de tiempo

    return tc[rand() % 3]; ///da uno de los tres valores del vector ta

}
