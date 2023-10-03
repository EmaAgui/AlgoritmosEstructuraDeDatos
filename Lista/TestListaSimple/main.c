#include <stdio.h>
#include <stdlib.h>

#include "../ListaSimple/ListaSimple.h"

#define NOM_ARCH_EMP "empleados.txt"


typedef struct
{
    int legajo;
    char nombreApellido[30];
    double sueldo;
    char sexo;
}Empleado;


void mostrarInt(void *d);
void crearLoteEmpleadosEnLista(Lista *lista);
void mostrarEmpleado(void *d, void *d1);
void grabarListaEnArchivoTxt(Lista *pl, const char* nombreArch);
void grabarArchTxtEmp(void *dato, void *pArch);


int main()
{

    Lista l;

    crearLista(&l);

    crearLoteEmpleadosEnLista(&l);

    recorrerLista(&l, NULL, mostrarEmpleado);

    grabarListaEnArchivoTxt(&l, NOM_ARCH_EMP);

    return 0;
}


void grabarArchTxtEmp(void *dato, void *pArch)
{
    Empleado *emp = (Empleado*)dato;
    FILE *arch = (FILE*)pArch;

    fprintf(arch, "%d|%s|%.2f|%c\n", emp->legajo, emp->nombreApellido, emp->sueldo, emp->sexo);
}


void grabarListaEnArchivoTxt(Lista *pl, const char* nombreArch)
{
    FILE *pArch;

    pArch = fopen(nombreArch, "wt");

    if(!pArch)
        return;

    recorrerLista(pl, pArch, grabarArchTxtEmp);

    fclose(pArch);
}


void mostrarEmpleado(void *d, void *d1)
{
    Empleado *emp = (Empleado*)d;

    printf("Legajo: [%d], Nombre: [%s], Sueldo: [%.2f], Sexo: [%c]\n", emp->legajo, emp->nombreApellido, emp->sueldo, emp->sexo);
}


void crearLoteEmpleadosEnLista(Lista *lista)
{
    Empleado e[] =
    {
        {1, "Maria Pia", 10000, 'F'},
        {2, "Juan Perez", 20000, 'M'},
        {3, "Ana Lopez", 30000, 'F'},
        {4, "Pedro Gomez", 40000, 'M'},
        {5, "Jose Martinez", 50000, 'M'},
        {6, "Marta Sanchez", 60000, 'F'},
        {7, "Carlos Gonzalez", 70000, 'M'},
        {8, "Lucia Rodriguez", 80000, 'F'},
        {9, "Alberto Fernandez", 90000, 'M'},
        {10, "Florencia Fernandez", 100000, 'F'}
    };
    int ce, i;

    ce = sizeof(e) / sizeof(*e);

    for(i = 0; i < ce; i++)
        ponerAlFinalLista(lista, e + i, sizeof(*e));


}


void mostrarInt(void *d)
{
    int *a = (int*)d;
    printf("%d\n", *a);
}
