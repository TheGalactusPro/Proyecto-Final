typedef struct
{
    float temperatura;
    float velocidadViento;
    float humedad;
} Clima;

typedef struct
{
    float co2;
    float so2;
    float no2;
    float pm25;
} Contaminacion;

typedef struct
{
    int dia;
    int mes;
    int ano;
    Contaminacion niveles;
} Registro;

typedef struct
{
    int idZona;
    char nombreZona[50];
    int numRegistros;
    Contaminacion actual;
    Contaminacion prediccion24h;
    Clima climaActual;
    Registro historial[30];
} Zona;

typedef struct
{
    float limiteCO2;
    float limiteSO2;
    float limiteNO2;
    float limitePM25;
} LimitesOMS;

typedef struct
{
    int idZona;
    char mensaje[200];
    int nivelAlerta;
} Alerta;

typedef struct
{
    int idZona;
    char recomendacion[300];
} Recomendacion;

typedef struct
{
    Zona zonas[100];
    LimitesOMS limites;
} SistemaContaminacion;

int menu();
void leerCadena(char *cadena, int n);
int validarEntero(int a, int b);
float validarFloatRango(float a, float b);

void registrarZona(Zona *z);
void mostrarZonasRegistradas(Zona zonas[], int totalZonas);

void monitoreoActual(Zona zonas[], int totalZonas, LimitesOMS limites);
void predecir24h(Zona zonas[], int totalZonas);
void mostrarPromediosHistoricos(Zona zonas[], int totalZonas);
void generarAlertas(Zona zonas[], int totalZonas, LimitesOMS limites);
void generarRecomendaciones(Zona zonas[], int totalZonas, LimitesOMS limites);
void generarReporte(Zona zonas[], int totalZonas);