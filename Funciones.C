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
    printf("\n--- LIMITES PERMITIDOS (OMS) ---\n");
    printf("CO2: %.2f\n", limites.limiteCO2);
    printf("SO2: %.2f\n", limites.limiteSO2);
    printf("NO2: %.2f\n", limites.limiteNO2);
    printf("PM2.5: %.2f\n", limites.limitePM25);
    printf("\n--- VALORES ACTUALES ---\n");

    if (zonas[pos].actual.co2 > limites.limiteCO2)
    {
        printf("\nCO2: %.2f (SUPERA el limite permitido)", zonas[pos].actual.co2);
    }
    else
    {
        printf("\nCO2: %.2f (Dentro del limite)", zonas[pos].actual.co2);
    }

    if (zonas[pos].actual.so2 > limites.limiteSO2)
    {
        printf("\nSO2: %.2f (SUPERA el limite permitido)", zonas[pos].actual.so2);
    }
    else
    {
        printf("\nSO2: %.2f (Dentro del limite)", zonas[pos].actual.so2);
    }

    if (zonas[pos].actual.no2 > limites.limiteNO2)
    {
        printf("\nNO2: %.2f (SUPERA el limite permitido)", zonas[pos].actual.no2);
    }
    else
    {
        printf("\nNO2: %.2f (Dentro del limite)", zonas[pos].actual.no2);
    }

    if (zonas[pos].actual.pm25 > limites.limitePM25)
    {
        printf("\nPM2.5: %.2f (SUPERA el limite permitido)\n", zonas[pos].actual.pm25);
    }
    else
    {
        printf("\nPM2.5: %.2f (Dentro del limite)\n", zonas[pos].actual.pm25);
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
        factor += 0.10;
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
    printf("\nZona: %s\n", zonas[pos].nombreZona);
    printf("\nCO2: %.2f\n", zonas[pos].prediccion24h.co2);
    printf("\nSO2: %.2f\n", zonas[pos].prediccion24h.so2);
    printf("\nNO2: %.2f\n", zonas[pos].prediccion24h.no2);
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
    printf("\nZona: %s\n", zonas[pos].nombreZona);

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
    printf("\n--- LIMITES PERMITIDOS (OMS) ---\n");
    printf("CO2: %.2f\n", limites.limiteCO2);
    printf("SO2: %.2f\n", limites.limiteSO2);
    printf("NO2: %.2f\n", limites.limiteNO2);
    printf("PM2.5: %.2f\n", limites.limitePM25);

    if (zonas[pos].prediccion24h.co2 > limites.limiteCO2)
    {
        printf("\nALERTA: CO2 %.2f superara el limite de %.2f.", zonas[pos].prediccion24h.co2, limites.limiteCO2);
        alerta = 1;
    }

    if (zonas[pos].prediccion24h.so2 > limites.limiteSO2)
    {
        printf("\nALERTA: SO2 %.2f superara el limite de %.2f.", zonas[pos].prediccion24h.so2, limites.limiteSO2);
        alerta = 1;
    }

    if (zonas[pos].prediccion24h.no2 > limites.limiteNO2)
    {
        printf("\nALERTA: NO2 %.2f superara el limite de %.2f.", zonas[pos].prediccion24h.no2, limites.limiteNO2);
        alerta = 1;
    }

    if (zonas[pos].prediccion24h.pm25 > limites.limitePM25)
    {
        printf("\nALERTA: PM2.5 %.2f superara el limite de %.2f.", zonas[pos].prediccion24h.pm25, limites.limitePM25);
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
        float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0, factor = 1.0;
        int registrosValidos = zonas[i].numRegistros;

        fprintf(fp, "Zona %d\n", i + 1);
        fprintf(fp, "Nombre: %s\n\n", zonas[i].nombreZona);

        fprintf(fp, "CONTAMINACION ACTUAL\n");
        fprintf(fp, "CO2: %.2f\n", zonas[i].actual.co2);
        fprintf(fp, "SO2: %.2f\n", zonas[i].actual.so2);
        fprintf(fp, "NO2: %.2f\n", zonas[i].actual.no2);
        fprintf(fp, "PM2.5: %.2f\n\n", zonas[i].actual.pm25);

        fprintf(fp, "PREDICCION 24 HORAS\n");

        // Calcular predicción de 24 horas sobre la marcha
        if (registrosValidos > 0)
        {
            // Sumar valores del historial
            for (int j = 0; j < registrosValidos; j++)
            {
                sumaCO2 += zonas[i].historial[j].niveles.co2;
                sumaSO2 += zonas[i].historial[j].niveles.so2;
                sumaNO2 += zonas[i].historial[j].niveles.no2;
                sumaPM25 += zonas[i].historial[j].niveles.pm25;
            }

            // Aplicar factor de ajuste según clima
            if (zonas[i].climaActual.temperatura > 30)
                factor += 0.10;

            if (zonas[i].climaActual.velocidadViento < 10)
                factor += 0.10;

            if (zonas[i].climaActual.humedad > 70)
                factor += 0.05;

            // Mostrar predicción calculada
            fprintf(fp, "CO2: %.2f\n", (sumaCO2 / registrosValidos) * factor);
            fprintf(fp, "SO2: %.2f\n", (sumaSO2 / registrosValidos) * factor);
            fprintf(fp, "NO2: %.2f\n", (sumaNO2 / registrosValidos) * factor);
            fprintf(fp, "PM2.5: %.2f\n", (sumaPM25 / registrosValidos) * factor);
        }
        else
        {
            // Si no hay registros, usar valor actual como predicción
            fprintf(fp, "CO2: %.2f\n", zonas[i].actual.co2);
            fprintf(fp, "SO2: %.2f\n", zonas[i].actual.so2);
            fprintf(fp, "NO2: %.2f\n", zonas[i].actual.no2);
            fprintf(fp, "PM2.5: %.2f\n", zonas[i].actual.pm25);
        }

        fprintf(fp, "\n=========================================\n\n");
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
    printf("\n--- PREDICCION PARA LAS PROXIMAS 24 HORAS ---\n");
    printf("CO2: %.2f\n", zonas[pos].prediccion24h.co2);
    printf("SO2: %.2f\n", zonas[pos].prediccion24h.so2);
    printf("NO2: %.2f\n", zonas[pos].prediccion24h.no2);
    printf("PM2.5: %.2f\n", zonas[pos].prediccion24h.pm25);

    if (zonas[pos].prediccion24h.pm25 > limites.limitePM25)
    {
        printf("\nSuspender actividades al aire libre. (PM2.5)");
        printf("\nUso obligatorio de mascarillas. (PM2.5)");
        recomendacion = 1;
    }

    if (zonas[pos].prediccion24h.no2 > limites.limiteNO2)
    {
        printf("\nAplicar restricciones vehiculares. (NO2)");
        recomendacion = 1;
    }

    if (zonas[pos].prediccion24h.so2 > limites.limiteSO2)
    {
        printf("\nReducir temporalmente la actividad industrial. (SO2)");
        recomendacion = 1;
    }

    if (zonas[pos].prediccion24h.co2 > limites.limiteCO2)
    {
        printf("\nFomentar el uso de transporte publico. (CO2)");
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
    printf("\n================================\n");
    printf("#\t\tZONA\n");
    printf("================================\n");
    for (int i = 0; i < totalZonas; i++)
    {
        printf("%d\t\t%s\n", i + 1, zonas[i].nombreZona);
    }
    printf("================================\n");
}