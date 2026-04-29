#include <stdio.h>
#include <string.h>
#define N 10000

typedef struct { //Estructura principal del archivo, dividida en subestructuras.
    struct {
        int anio;
        int mes;
        int dia;
        char dia_semana [10];
    } fecha;


    struct {
        char hora_ini[6];
        char hora_fin[6];
    } horario;


    struct {
        char  actividad_base [50];
        char modalidad  [50];
        char centro [50];
        char tipo_uso  [50];
    } actividad;


    struct {
        int plazas;
        int ocupadas;
        int libres;
    } aforo;
} Registro;
//a partir de aquí y antes del main están los prototipos de funciones
void listado_opciones();

int main ()
{
//Vector de estructuras:
Registro vector_informacion [N];


FILE*ARCHIVO; //Creacion del puntero del archivo y lectura
ARCHIVO = fopen("deportes_ayuntamiento.txt" , "r");
fscanf(ARCHIVO, "%*[^\n]\n"); //Se salta la linea de los headers.


int i = 1;
while(fscanf(ARCHIVO, "%d %d %d %s %s %s %s %s %s %d %d %d %s" , &vector_informacion[i].fecha.anio , &vector_informacion[i].fecha.mes, &vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, &vector_informacion[i].aforo.plazas, &vector_informacion[i].aforo.ocupadas, &vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso) != EOF)
{
    if (ARCHIVO == NULL)
    {
        printf("ERROR: No se ha podido abrir el archivo. Comprueba el nombre y la carpeta.\n");
    }
fscanf(ARCHIVO, "%d %d %d %s %s %s %s %s %s %d %d %d %s" , &vector_informacion[i].fecha.anio , &vector_informacion[i].fecha.mes, &vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, &vector_informacion[i].aforo.plazas, &vector_informacion[i].aforo.ocupadas, &vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
i++;
} //Bucle de lectura del archivo

// COdigo para printear una linea del archivo: NO BORRAR. printf("%d %d %d %s %s %s %s %s %s %d %d %d %s" , vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);

printf("BIENVENIDO AL CENTRO DE GESTIÓN DE DATOS DEPORTIVOS\n");
printf("---------------------------------------------------\n");
printf("Presione cualquier tecla para ingresar:");
getchar();
printf("\nAccediendo...\n");
listado_opciones(); //llamamos a la funcion listado_opciones
int opcion_listado;
scanf("&d", &opcion_listado);
switch (opcion_listado){

    case 1: 
    case 2: 
    case 3: 
    case 4: 
    case 5:
    default:
}

return 0;
}

void listado_opciones(){
    printf("Listado de opciones\n");
    printf("-------------------\n");
    printf("1. Lista de actividades\n");
    printf("2. Estadísticas\n");
    printf("3. Resumen por centro\n");
    printf("4. Resumen por fecha\n");
    printf("5. Modificar el fichero\n"); 
}
