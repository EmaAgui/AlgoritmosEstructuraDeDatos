#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"


 /**     
  EJERCICIO:
    nroPed|codProd|cant|precio
        01|  mart |1   | 10
        01|  dest |2   | 20
        01|tornillos |50   | 5
        02|  mart |1   | 10
        02|  clavos|100   | 5
        02|  taladro|1   | 95

        tengo un archivo binario o de texto ordenado por número de pedido
        guardar en un archivos los pedidos que tengan mas de 100 en un archivo
        y menos de 100 en otro

        leer el pedido y guardarlo en una cola
**/




int main()
{
    printf("Hello world!\n");

    actualizarArchivos(NOM_ARCH_PED, NOM_ARCH_MAY, NOM_ARCH_MEN);
    return 0;
}
