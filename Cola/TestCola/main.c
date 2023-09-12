#include <stdio.h>
#include <stdlib.h>
#include "../ColaDinamica/ColaDinamica.h"

int main()
{
    Cola cola;
    int i, num;

    crearCola(&cola);

    for(i = 0; i < 6; i++)
        ponerEnCola(&cola, &i, sizeof(i));

    while(sacarDeCola(&cola, &num, sizeof(num)))
    {
        printf("%d ", num);
    }

    if(colaVacia(&cola))
        printf("\nLa Cola esta vacia\n");
    else
        printf("\nLa Cola no esta vacia\n");

    return 0;
}
