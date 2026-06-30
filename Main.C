#include <stdio.h>
#include "Funciones.H"

int main(int argc, char *argv[])
{
    Zona zonas[100];
    int totalZonas = 0;

    LimitesOMS limites;

    int opc;
    int opc2;

    limites.limiteCO2 = 1000;
    limites.limiteSO2 = 40;
    limites.limiteNO2 = 25;
    limites.limitePM25 = 15;

    do
    {
        opc = menu();

        switch (opc)
        {
        case 1:
            registrarZona(&zonas[totalZonas]);
            totalZonas++;
            printf("\nZona registrada correctamente.");
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