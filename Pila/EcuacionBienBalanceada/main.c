#include <stdio.h>
#include <stdlib.h>

#include "../PilaEstatica/PilaEstatica.h"

char verificar(const char *letra);
int verificarMatriz(const char *dato);
int verificarEcuacion(const char *ecuacion, Pila *pilaEcuacion);


int main()
{
    const char *ecuacion = "{[()+()]}";
    Pila ecuacionPila;

    crearPila(&ecuacionPila);

    if(verificarEcuacion(ecuacion, &ecuacionPila))
        printf("Ecuacion Bien Balanceada");
    else
        printf("Ecuacion No Balanceada");

    return 0;
}

char verificar(const char *letra)
{
    int i;
    const char matEcu[][3] =
    {
        {'(', '[', '{'},
        {')', ']', '}'}
    };

    for(i = 0; i < 3; i++)
        if(matEcu[1][i] == *letra)
            return matEcu[0][i];
    return '\0';
}


int verificarMatriz(const char *dato)
{
    int i;
    const char ecuAbrir[] =
        {'(', '[', '{'};
    const char ecuCerrar[] =
        {')', ']', '}'};

    for(i = 0; i < 3; i++)
        if(ecuAbrir[i] == *dato)
            return 1;

    for(i = 0; i < 3; i++)
        if(ecuCerrar[i] == *dato)
            return -1;

    return 0;
}


int verificarEcuacion(const char *ecuacion, Pila *pilaEcuacion)
{
    char dato;
    while(*ecuacion)
    {
        if(verificarMatriz(ecuacion) == 1)
            ponerEnPila(pilaEcuacion, ecuacion, sizeof(*ecuacion));

        if(verificarMatriz(ecuacion) == -1)
        {
            sacarDePila(pilaEcuacion, &dato, sizeof(dato));
            if(verificar(ecuacion) != dato)
                return 0;

        }

        ecuacion++;
    }

    if(sacarDePila(pilaEcuacion, &dato, sizeof(dato)))
        return 0;

    return 1;
}
