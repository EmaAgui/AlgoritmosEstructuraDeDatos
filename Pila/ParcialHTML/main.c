#include <stdio.h>
#include <stdlib.h>
#include "../PilaDinamica/PilaDinamica.h"


#define NOM_ARCH_HTML "index.txt"
#define ES_LETRA(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))

void mostrarArchivoHTML(const void *nombreArch);

void crearEtiquetas(const void *nombreArch);
int verificaEtiqueta(const char *etiqueta, char *cop);

int main()
{
    Pila *etiqueta;
    mostrarArchivoHTML(NOM_ARCH_HTML);
    crearEtiquetas(NOM_ARCH_HTML);
    return 0;
}

int verificaEtiqueta(const char *etiqueta, char *cop)
{
    const char *iniEtiqueta = etiqueta;
    int cantCaractACopiar = 1;

    while(*iniEtiqueta == ' ')
        iniEtiqueta++;

    if(*iniEtiqueta != '<' || *(iniEtiqueta + 1) == '/')
        return 0;

    etiqueta = iniEtiqueta;

    while(*etiqueta)
    {
        if(*etiqueta == '>')
        {
            strncpy(cop, iniEtiqueta, cantCaractACopiar);
            *(cop + cantCaractACopiar) = '\0';
            return 1;
        }

        cantCaractACopiar++;
        etiqueta++;
    }
    return 0;
}

void crearEtiquetas(const void *nombreArch)
{
    FILE *pArch = fopen(nombreArch, "rt");
    char aux[500];
    char etiqueta[30];
    char vEtiquetaIni[30][30];
    char vEtiquetaCie[30][30];
    int i = 0;


    if(!pArch)
        return;

    while(fgets(aux, 500, pArch))
    {
        if(verificaEtiqueta(aux, etiqueta))
        {
            strcpy(vEtiquetaIni[i], etiqueta);
            i++;
        }

    }
    for(int j = 0; j < i; j++)
    {
        if(j == 1)
            *vEtiquetaCie[j] = '/';
        printf("%s\n", vEtiquetaIni[j]);
    }


    fclose(pArch);
}


void mostrarArchivoHTML(const void *nombreArch)
{
    FILE *pArch = fopen(nombreArch, "rt");
    char aux[500];

    if(!pArch)
        return;

    while(fgets(aux, 500, pArch))
    {
        printf("%s", aux);
    }

    fclose(pArch);
}



