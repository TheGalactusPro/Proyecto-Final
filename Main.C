#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    Zona zonas[100];
    int totalZonas = 0;

    LimitesOMS limites;

    int opc;
    int opc2;

    limites.limiteCO2 = 1000;
    limites.limiteSO2 = 75;
    limites.limiteNO2 = 200;
    limites.limitePM25 = 25;

    do
    {
        opc = menu();

        switch (opc)
        {
        case 1:
            if (totalZonas < 100000)
            {
                registrarZona(&zonas[totalZonas]);
                totalZonas++;
                printf("\nZona registrada correctamente.");
            }
            else
            {
                printf("\nNo se pueden registrar mas zonas.");
            }
            break;

        case 2:
            monitoreoActual(zonas, totalZonas, limites);
            break;

        case 3:
            predecir24h(zonas, totalZonas);
            break;

        case 4:
            mostrarPromediosHistoricos(zonas, totalZonas);
            break;

        case 5:
            generarAlertas(zonas, totalZonas, limites);
            break;

        case 6:
            generarRecomendaciones(zonas, totalZonas, limites);
            break;

        case 7:
            generarReporte(zonas, totalZonas);
            break;

        case 8:
            printf("\nSaliendo del sistema...\n");
            return 0;

        default:
            printf("\nOpcion invalida.");
            break;
        }

        printf("\nDesea continuar: 1 (Si) o  2 (No)");
        printf("\n>> ");

        opc2 = validarEntero(1, 2);

    } while (opc2 == 1);

    printf("\nFIN");
    return 0;
}