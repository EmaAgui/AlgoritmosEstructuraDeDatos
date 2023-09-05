#include <stdio.h>
#include <stdlib.h>

#include "../PilaDinamica/PilaDinamica.h"

int main()
{
    Pila pila;

    int i, num;

    crearPila(&pila);

    for(i = 0; i < 5;i++)
        ponerEnPila(&pila, &i, sizeof(i));

    for(i = 0; i < 5;i++)
    {
        sacarDePila(&pila,&num, sizeof(num));
        printf("%d\n", num);
    }

    return 0;
}
