#include <stdio.h>
#include <stdlib.h>

#include "../PilaDinamica/PilaDinamica.h"

#define NOMB_ARCH_BIN     "empleados.dat"
#define NOMB_ARCH_BIN_ORD "empleadosOrd.dat"

typedef struct
{
    int leg;
    char nya[50];
    float sueldo;
    char sexo;
}Empleado;


void crearLote(const char *nombreArch);
void recorrerArchBinGen(const char *nombreArch, size_t tamBytes, void recorrer(const void *d));
void mostrarArchEmp(const void *dato);
void ordenarArchPilaBin(const char *nombreArch, const char *nombreArchOrd, size_t tamBytes, int cmp(const void *d1, const void *d2));
int comparaEmpleados(const void *d1, const void *d2);


int main()
{
    crearLote(NOMB_ARCH_BIN);


    recorrerArchBinGen(NOMB_ARCH_BIN, sizeof(Empleado), mostrarArchEmp);

    ordenarArchPilaBin(NOMB_ARCH_BIN, NOMB_ARCH_BIN_ORD, sizeof(Empleado), comparaEmpleados);
    printf("ORDENADOS\n");
    recorrerArchBinGen(NOMB_ARCH_BIN_ORD, sizeof(Empleado), mostrarArchEmp);

    return 0;
}


int comparaEmpleados(const void *d1, const void *d2)
{
    const Empleado *emp1 = (const Empleado *)d1;
    const Empleado *emp2 = (const Empleado *)d2;

    return emp1->leg - emp2->leg;
}


void ordenarArchPilaBin(const char *nombreArch, const char *nombreArchOrd, size_t tamBytes, int cmp(const void *d1, const void *d2))
{
    FILE *pArch, *pArchOrd;
    Pila pilaMay, pilaMen;
    void *dato, *tope;

    crearPila(&pilaMay);
    crearPila(&pilaMen);

    pArch = fopen(nombreArch, "rb");
    if(!pArch)
        return;

    dato = malloc(tamBytes);
    if(!dato)
    {
        fclose(pArch);
        return;
    }
    tope = malloc(tamBytes);
    if(!tope)
    {
        fclose(pArch);
        free(dato);
        return;
    }

    fread(dato, tamBytes, 1, pArch);
    while(!feof(pArch))
    {
        ponerEnPila(&pilaMay, dato, tamBytes);
        fread(dato, tamBytes, 1, pArch);

        while(verTope(&pilaMay, tope, tamBytes) && (cmp(tope, dato) < 0))
        {
            sacarDePila(&pilaMay, tope, tamBytes);
            ponerEnPila(&pilaMen, tope, tamBytes);
        }

        while(verTope(&pilaMen, tope, tamBytes) && (cmp(tope, dato) > 0))
        {
            sacarDePila(&pilaMen, tope, tamBytes);
            ponerEnPila(&pilaMay, tope, tamBytes);
        }

    }

    while(sacarDePila(&pilaMen, dato, tamBytes))
        ponerEnPila(&pilaMay, dato, tamBytes);

    pArchOrd = fopen(nombreArchOrd, "wb");
    if(!pArchOrd)
    {
        fclose(pArch);
        free(dato);
        free(tope);
        return;
    }

    while(!pilaVacia(&pilaMay))
    {
        sacarDePila(&pilaMay, dato, tamBytes);
        fwrite(dato, tamBytes, 1, pArchOrd);
    }


    fclose(pArch);
    fclose(pArchOrd);
    free(dato);
    free(tope);
}


void mostrarArchEmp(const void *dato)
{
    const Empleado *emp = (const Empleado*)dato;

    printf("Legajo: [%d], Nombre y Apellido: [%s], Sueldo: [%.2f US], Sexo: [%c]\n",
            emp->leg, emp->nya, emp->sueldo, emp->sexo);

}

void recorrerArchBinGen(const char *nombreArch, size_t tamBytes, void recorrer(const void *d))
{
    void *dato = malloc(tamBytes);
    FILE *arch = fopen(nombreArch, "rb");

    if(!dato || !arch)
    {
        fclose(arch);
        free(dato);
        return;
    }

    fread(dato, tamBytes, 1, arch);
    while(!feof(arch))
    {
        recorrer(dato);
        fread(dato, tamBytes, 1, arch);
    }

    fclose(arch);
    free(dato);
}


void crearLote(const char *nombreArch)
{
    FILE *pArch;
    Empleado vEmp[] =
    {
        {103, "Carlos Gomez", 4200.0, 'M'},
        {110, "Laura Fernandez", 3200.0, 'F'},
        {105, "Pedro Martinez", 3800.0, 'M'},
        {102, "Maria Lopez", 2800.0, 'F'},
        {117, "Diego Sanchez", 5000.0, 'M'},
        {106, "Ana Rodriguez", 3100.0, 'F'},
        {112, "Luis Perez", 4400.0, 'M'},
        {116, "Elena Hernandez", 4900.0, 'F'},
        {101, "Juan Perez", 3500.0, 'M'},
        {113, "Sofia Gonzalez", 4700.0, 'F'},
        {118, "Andres Ramirez", 5300.0, 'M'},
        {115, "Julia Lopez", 4600.0, 'F'},
        {109, "Manuel Torres", 3000.0, 'M'},
        {120, "Alejandra Diaz", 5500.0, 'F'},
        {107, "Martin Garcia", 3300.0, 'M'},
        {111, "Carolina Fernandez", 4100.0, 'F'},
        {114, "Fernando Martinez", 4800.0, 'M'},
        {108, "Isabel Rodriguez", 3400.0, 'F'},
        {104, "Miguel Gonzalez", 3900.0, 'M'},
        {119, "Rocio Perez", 5200.0, 'F'}
    };

    pArch = fopen(nombreArch, "wb");
    if(!pArch)
        return;


    fwrite(vEmp, sizeof(Empleado), sizeof(vEmp) / sizeof(Empleado), pArch);

    fclose(pArch);
}
