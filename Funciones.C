#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu()
{
    int opc;

    printf("\n1. Registrar zona");
    printf("\n2. Monitorear contaminacion actual");
    printf("\n3. Predecir contaminacion a 24 horas");
    printf("\n4. Mostrar promedios historicos");
    printf("\n5. Generar alertas");
    printf("\n6. Generar recomendaciones");
    printf("\n7. Exportar reporte");
    printf("\n8. Salir");
    printf("\n>> ");

    opc = validarEntero(1, 8);

    return opc;
}

void leerCadena(char *cadena, int n)
{
    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    cadena[len] = '\0';
}

int validarEntero(int a, int b)
{
    int n;
    int aux;
    do
    {
        aux = scanf("%d", &n);
        while ((getchar()) != '\n');
        if (aux != 1 || n < a || n > b)
        {
            printf("\nError: El valor ingresado es incorrecto");
            printf("\n>> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

float validarFloatRango(float a, float b)
{
    float n;
    int aux;
    do
    {
        aux = scanf("%f", &n);
        while ((getchar()) != '\n');
        if (aux != 1 || n < a || n > b)
        {
            printf("\nError: El valor ingresado es incorrecto");
            printf("\n>> ");
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}

void registrarZona(Zona *z)
{
    printf("\nID de la zona: ");
    (*z).idZona = validarEntero(1, 9999);

    printf("\nNombre de la zona: ");
    leerCadena((*z).nombreZona, 50);

    printf("\n--- Contaminacion actual ---\n");

    printf("\nCO2: ");
    (*z).actual.co2 = validarFloatRango(0, 10000);

    printf("\nSO2: ");
    (*z).actual.so2 = validarFloatRango(0, 10000);

    printf("\nNO2: ");
    (*z).actual.no2 = validarFloatRango(0, 10000);

    printf("\nPM2.5: ");
    (*z).actual.pm25 = validarFloatRango(0, 10000);

    printf("\nDATOS CLIMATICOS\n");

    printf("\nTemperatura: ");
    (*z).climaActual.temperatura = validarFloatRango(-50, 60);

    printf("\nVelocidad del viento: ");
    (*z).climaActual.velocidadViento = validarFloatRango(0, 200);

    printf("\nHumedad: ");
    (*z).climaActual.humedad = validarFloatRango(0, 100);

    printf("\nCantidad de registros historicos (1-30): ");
    (*z).numRegistros = validarEntero(1, 30);

    for (int i = 0; i < (*z).numRegistros; i++)
    {
        printf("\nRegistro %d\n", i + 1);

        printf("\nCO2: ");
        (*z).historial[i].niveles.co2 = validarFloatRango(0, 10000);

        printf("\nSO2: ");
        (*z).historial[i].niveles.so2 = validarFloatRango(0, 10000);

        printf("\nNO2: ");
        (*z).historial[i].niveles.no2 = validarFloatRango(0, 10000);

        printf("\nPM2.5: ");
        (*z).historial[i].niveles.pm25 = validarFloatRango(0, 10000);
    }
}

void monitoreoActual(Zona zonas[], int totalZonas, LimitesOMS limites)
{
    int pos;
    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.");
        return;
    }

    mostrarZonasRegistradas(zonas, totalZonas);

    printf("\nSeleccione una zona: ");
    pos = validarEntero(1, totalZonas) - 1;

    printf("\nMONITOREO DE CONTAMINACION ");
    printf("\nZona: %s\n", zonas[pos].nombreZona);

    if (zonas[pos].actual.co2 > limites.limiteCO2)
    {
        printf("\nCO2 supera el limite permitido.");
    }
    else
    {
        printf("\nCO2 dentro del limite permitido.");
    }

    if (zonas[pos].actual.so2 > limites.limiteSO2)
    {
        printf("\nSO2 supera el limite permitido.");
    }
    else
    {
        printf("\nSO2 dentro del limite permitido.");
    }

    if (zonas[pos].actual.no2 > limites.limiteNO2)
    {
        printf("\nNO2 supera el limite permitido.");
    }
    else
    {
        printf("\nNO2 dentro del limite permitido.");
    }

    if (zonas[pos].actual.pm25 > limites.limitePM25)
    {
        printf("\nPM2.5 supera el limite permitido.");
    }
    else
    {
        printf("\nPM2.5 dentro del limite permitido.");
    }
}

void predecir24h(Zona zonas[], int totalZonas)
{
    int pos;
    float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0, factor = 1.0;

    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.");
        return;
    }

    mostrarZonasRegistradas(zonas, totalZonas);

    printf("\nSeleccione una zona: ");
    pos = validarEntero(1, totalZonas) - 1;

    if (zonas[pos].numRegistros == 0)
    {
        printf("\nNo existen registros historicos.");
        return;
    }

    for (int i = 0; i < zonas[pos].numRegistros; i++)
    {
        sumaCO2 += zonas[pos].historial[i].niveles.co2;
        sumaSO2 += zonas[pos].historial[i].niveles.so2;
        sumaNO2 += zonas[pos].historial[i].niveles.no2;
        sumaPM25 += zonas[pos].historial[i].niveles.pm25;
    }

    if (zonas[pos].climaActual.temperatura > 30)
    {
        factor += 0.10;
    }

    if (zonas[pos].climaActual.velocidadViento < 10)
    {
        factor += 0.15;
    }

    if (zonas[pos].climaActual.humedad > 70)
    {
        factor += 0.05;
    }

    zonas[pos].prediccion24h.co2 = (sumaCO2 / zonas[pos].numRegistros) * factor;

    zonas[pos].prediccion24h.so2 = (sumaSO2 / zonas[pos].numRegistros) * factor;

    zonas[pos].prediccion24h.no2 = (sumaNO2 / zonas[pos].numRegistros) * factor;

    zonas[pos].prediccion24h.pm25 = (sumaPM25 / zonas[pos].numRegistros) * factor;

    printf("\nPREDICCION PARA LAS PROXIMAS 24 HORAS");
    printf("\nZona: %s", zonas[pos].nombreZona);

    printf("\nCO2: %.2f", zonas[pos].prediccion24h.co2);
    printf("\nSO2: %.2f", zonas[pos].prediccion24h.so2);
    printf("\nNO2: %.2f", zonas[pos].prediccion24h.no2);
    printf("\nPM2.5: %.2f\n", zonas[pos].prediccion24h.pm25);
}

void mostrarPromediosHistoricos(Zona zonas[], int totalZonas)
{
    int pos;
    float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0;

    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.");
        return;
    }

    mostrarZonasRegistradas(zonas, totalZonas);

    printf("\nSeleccione una zona: ");
    pos = validarEntero(1, totalZonas) - 1;

    if (zonas[pos].numRegistros == 0)
    {
        printf("\nNo existen registros historicos.");
        return;
    }

    for (int i = 0; i < zonas[pos].numRegistros; i++)
    {
        sumaCO2 += zonas[pos].historial[i].niveles.co2;
        sumaSO2 += zonas[pos].historial[i].niveles.so2;
        sumaNO2 += zonas[pos].historial[i].niveles.no2;
        sumaPM25 += zonas[pos].historial[i].niveles.pm25;
    }

    printf("\nPROMEDIOS HISTORICOS");
    printf("\nZona: %s", zonas[pos].nombreZona);

    printf("\nCO2: %.2f", sumaCO2 / zonas[pos].numRegistros);
    printf("\nSO2: %.2f", sumaSO2 / zonas[pos].numRegistros);
    printf("\nNO2: %.2f", sumaNO2 / zonas[pos].numRegistros);
    printf("\nPM2.5: %.2f\n", sumaPM25 / zonas[pos].numRegistros);
}

void generarAlertas(Zona zonas[], int totalZonas, LimitesOMS limites)
{
    int pos;
    int alerta = 0;

    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.");
        return;
    }

    mostrarZonasRegistradas(zonas, totalZonas);

    printf("\nSeleccione una zona: ");
    pos = validarEntero(1, totalZonas) - 1;

    printf("\nALERTAS PREVENTIVAS");
    printf("\nZona: %s\n", zonas[pos].nombreZona);

    if (zonas[pos].prediccion24h.co2 > limites.limiteCO2)
    {
        printf("\nALERTA: CO2 superara el limite permitido.");
        alerta = 1;
    }

    if (zonas[pos].prediccion24h.so2 > limites.limiteSO2)
    {
        printf("\nALERTA: SO2 superara el limite permitido.");
        alerta = 1;
    }

    if (zonas[pos].prediccion24h.no2 > limites.limiteNO2)
    {
        printf("\nALERTA: NO2 superara el limite permitido.");
        alerta = 1;
    }

    if (zonas[pos].prediccion24h.pm25 > limites.limitePM25)
    {
        printf("\nALERTA: PM2.5 superara el limite permitido.");
        alerta = 1;
    }

    if (alerta == 0)
    {
        printf("\nNo existen alertas para esta zona.");
    }
}

void generarReporte(Zona zonas[], int totalZonas)
{
    FILE *fp;

    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.");
        return;
    }

    fp = fopen("reporte_calidad_aire.txt", "w");

    if (fp == NULL)
    {
        printf("\nError al generar el reporte.");
        return;
    }

    fprintf(fp, "=========================================\n");
    fprintf(fp, " REPORTE DE CONTAMINACION DEL AIRE\n");
    fprintf(fp, "=========================================\n\n");

    for (int i = 0; i < totalZonas; i++)
    {
        fprintf(fp, "Zona %d\n", i + 1);
        fprintf(fp, "ID: %d\n", zonas[i].idZona);
        fprintf(fp, "Nombre: %s\n\n", zonas[i].nombreZona);

        fprintf(fp, "CONTAMINACION ACTUAL\n");
        fprintf(fp, "CO2: %.2f\n", zonas[i].actual.co2);
        fprintf(fp, "SO2: %.2f\n", zonas[i].actual.so2);
        fprintf(fp, "NO2: %.2f\n", zonas[i].actual.no2);
        fprintf(fp, "PM2.5: %.2f\n\n", zonas[i].actual.pm25);

        fprintf(fp, "PREDICCION 24 HORAS\n");
        fprintf(fp, "CO2: %.2f\n", zonas[i].prediccion24h.co2);
        fprintf(fp, "SO2: %.2f\n", zonas[i].prediccion24h.so2);
        fprintf(fp, "NO2: %.2f\n", zonas[i].prediccion24h.no2);
        fprintf(fp, "PM2.5: %.2f\n", zonas[i].prediccion24h.pm25);

        fprintf(fp, "\n-----------------------------------------\n\n");
    }

    fclose(fp);

    printf("\nReporte generado correctamente.");
    printf("\nArchivo: reporte_calidad_aire.txt\n");
}

void generarRecomendaciones(Zona zonas[], int totalZonas, LimitesOMS limites)
{
    int pos;
    int recomendacion = 0;

    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.");
        return;
    }

    mostrarZonasRegistradas(zonas, totalZonas);

    printf("\nSeleccione una zona: ");
    pos = validarEntero(1, totalZonas) - 1;

    printf("\nRECOMENDACIONES");
    printf("\nZona: %s\n", zonas[pos].nombreZona);

    if (zonas[pos].prediccion24h.pm25 > limites.limitePM25)
    {
        printf("\nSuspender actividades al aire libre.");
        printf("\nUso obligatorio de mascarillas.");
        recomendacion = 1;
    }

    if (zonas[pos].prediccion24h.no2 > limites.limiteNO2)
    {
        printf("\nAplicar restricciones vehiculares.");
        recomendacion = 1;
    }

    if (zonas[pos].prediccion24h.so2 > limites.limiteSO2)
    {
        printf("\nReducir temporalmente la actividad industrial.");
        recomendacion = 1;
    }

    if (zonas[pos].prediccion24h.co2 > limites.limiteCO2)
    {
        printf("\nFomentar el uso de transporte publico.");
        recomendacion = 1;
    }

    if (recomendacion == 0)
    {
        printf("\nNo se requieren medidas especiales.");
    }
}

void mostrarZonasRegistradas(Zona zonas[], int totalZonas)
{
    if (totalZonas == 0)
    {
        printf("\nNo existen zonas registradas.\n");
        return;
    }
    printf("\n=====================================================\n");
    printf("#\t\tID\t\tNOMBRE\n");
    printf("=====================================================\n");
    for (int i = 0; i < totalZonas; i++)
    {
        printf("%d\t\t%-10d\t%s\n", i + 1, zonas[i].idZona, zonas[i].nombreZona);
    }
    printf("=====================================================\n");
}