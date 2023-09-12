#include "Funciones.h"
#include <string.h>

void actualizarArchivos(const char *nombArchPedTxt, const char *nombreMasCien, const  char *nombreMenCien)
{
    FILE *pArchPed, *pArchMay, *pArchMen;
    char aux[1000];
    Cola cola, colaMay, colaMen;
    Pedido ped, pedAux;
    unsigned total = 0;


    crearCola(&cola);
    crearCola(&colaMay);
    crearCola(&colaMen);

    pArchPed = fopen(nombArchPedTxt, "rt");

    if(!pArchPed)
        return;

    pArchMay = fopen(nombreMasCien, "wt");

    if(!pArchMay)
    {
        fclose(pArchPed);
        return;
    }

    pArchMen = fopen(nombreMenCien, "wt");
    if(!pArchMen)
    {
        fclose(pArchPed);
        fclose(pArchMen);
        return;
    }

    while (fgets(aux, sizeof(aux), pArchPed))
    {
        trozarPed(aux, &ped);

        ponerEnCola(&cola, &ped, sizeof(ped));
        verFrenteCola(&cola, &pedAux, sizeof(pedAux));

        if(strcmp(pedAux.numeroPed, ped.numeroPed) == 0)
        {
            total += (ped.cantidadPedida * ped.precio);
        }
        else
        {
            if(total >= 100)
            {
                while (verFrenteCola(&cola, &ped, sizeof(ped)) && (strcmp(pedAux.numeroPed, ped.numeroPed) == 0))
                {
                    sacarDeCola(&cola, &ped, sizeof(ped));
                    ponerEnCola(&colaMay, &ped, sizeof(ped));
                }
            }

            if(total < 100)
            {
                while (verFrenteCola(&cola, &ped, sizeof(ped)) && (strcmp(pedAux.numeroPed, ped.numeroPed) == 0))
                {
                    sacarDeCola(&cola, &ped, sizeof(ped));
                    ponerEnCola(&colaMen, &ped, sizeof(ped));
                }
            }

            total = 0;
            verFrenteCola(&cola, &ped, sizeof(ped));
            total += (ped.cantidadPedida * ped.precio);
        }
    }

    if(total >= 100)
    {
        while (verFrenteCola(&cola, &ped, sizeof(ped)))
        {
            sacarDeCola(&cola, &ped, sizeof(ped));
            ponerEnCola(&colaMay, &ped, sizeof(ped));
        }
    }

    if(total < 100)
    {
        while (verFrenteCola(&cola, &ped, sizeof(ped)))
        {
            sacarDeCola(&cola, &ped, sizeof(ped));
            ponerEnCola(&colaMen, &ped, sizeof(ped));
        }
    }


    while (sacarDeCola(&colaMay, &ped, sizeof(ped)))
    {
        fprintf(pArchMay, "%s|%s|%u|%.2f\n", ped.numeroPed, ped.codProd, ped.cantidadPedida, ped.precio);
    }

    while (sacarDeCola(&colaMen, &ped, sizeof(ped)))
    {
        fprintf(pArchMen, "%s|%s|%u|%.2f\n", ped.numeroPed, ped.codProd, ped.cantidadPedida, ped.precio);
    }


    fclose(pArchPed);
    fclose(pArchMen);
    fclose(pArchMay);
}


void trozarPed(const char *cad, Pedido *ped)
{
    char *aux = strchr(cad, '\n');
    *aux = '\0';

    /** Precio **/
    aux = strrchr(cad, '|');
    sscanf(aux + 1,"%f", &ped->precio);
    *aux = '\0';

    /** Cantidad Pedida */
    aux = strrchr(cad, '|');
    sscanf(aux + 1, "%u", &ped->cantidadPedida);
    *aux = '\0';

    /** Numero de Pedido*/
    aux = strrchr(cad, '|');
    strcpy(ped->codProd, aux + 1);
    *aux = '\0';

    /**Codigo de Producto */
    strcpy(ped->numeroPed, cad);

}
