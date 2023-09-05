#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../PilaEstatica/PilaEstatica.h"

#define NOMB_ARCH_TXT "numeros.txt"
#define NOMB_ARCH_RES "resultado.txt"

/**
    Ejercicio de tarea: programa que sume dos numeros enteros muy grandes(hasta 500 digitos),
    imprimir la suma de los numeros. Los numeros vienen de un archivo de texto,
    el primero en el primer renglon y el segundo en el segundo(opcional).
**/


void leerNumerosDeArchivo(const char *nombreArchTxt, Pila *pilaNum1, Pila *pilaNum2);
void sumarNumeros(Pila *pilaNum1, Pila *pilaNum2, Pila *pilaResu);
void grabarEnArchivo(const char *nombreArch, Pila *pilaResu);


int main()
{
    Pila pilaNum1, pilaNum2, pilaResu;

    crearPila(&pilaNum1);
    crearPila(&pilaNum2);
    crearPila(&pilaResu);

    leerNumerosDeArchivo(NOMB_ARCH_TXT, &pilaNum1, &pilaNum2);

    sumarNumeros(&pilaNum1, &pilaNum2, &pilaResu);

    grabarEnArchivo(NOMB_ARCH_RES, &pilaResu);

    return 0;
}


void grabarEnArchivo(const char *nombreArch, Pila *pilaResu)
{
    FILE *pf;
    int d;

    pf = fopen(nombreArch, "wt");

    if (!pf)
        return;

    while (sacarDePila(pilaResu, &d, sizeof(d)))
        fprintf(pf, "%d", d);

    fprintf(pf, "\n");
    fclose(pf);

}


void sumarNumeros(Pila *pilaNum1, Pila *pilaNum2, Pila *pilaResu)
{
    int acarreo = 0;
    int sum, n1, n2;

    while(verTope(pilaNum1, &n1, sizeof(n1)) && verTope(pilaNum2, &n2, sizeof(n2)))
    {
        sacarDePila(pilaNum1, &n1, sizeof(n1));
        sacarDePila(pilaNum2, &n2, sizeof(n2));
        sum = acarreo + n1 + n2;

        if(sum > 9)
        {
            acarreo = 1;
            sum -= 10;
        }
        else
            acarreo = 0;
        ponerEnPila(pilaResu, &sum, sizeof(sum));
    }

    while(sacarDePila(pilaNum1, &n1, sizeof(n1)))
    {
        sum = acarreo + n1;

        if(sum > 9)
        {
            acarreo = 1;
            sum -= 10;
        }
        else
            acarreo = 0;
        ponerEnPila(pilaResu, &sum, sizeof(sum));
    }

    while(sacarDePila(pilaNum2, &n2, sizeof(n2)))
    {
        sum = acarreo + n2;

        if(sum > 9)
        {
            acarreo = 1;
            sum -= 10;
        }
        else
            acarreo = 0;
        ponerEnPila(pilaResu, &sum, sizeof(sum));
    }

    if(acarreo)
        ponerEnPila(pilaResu, &acarreo, sizeof(acarreo));
}


void leerNumerosDeArchivo(const char *nombreArchTxt, Pila *pilaNum1, Pila *pilaNum2)
{
    char aux[500];
    FILE *pArchTxt;
    int band = 0;
    int d, i;

    pArchTxt = fopen(nombreArchTxt, "rt");

    if(!pArchTxt)
        return;

    while(fgets(aux, 500, pArchTxt))
    {

        if(!band)
        {
            i = 0;
            while(*(aux + i) != '\n')
            {
                d = aux[i] - '0';
                ponerEnPila(pilaNum1, &d, sizeof(d));
                i++;
            }
            band = 1;
        }
        else
        {
            i = 0;
            while(*(aux + i) != '\n')
            {
                d = aux[i] - '0';
                ponerEnPila(pilaNum2, &d, sizeof(d));
                i++;
            }
        }

    }
    fclose(pArchTxt);
}

