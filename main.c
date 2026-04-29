#include <stdio.h>
#include <string.h>
#include <unistd.h> //para usar la función sleep para el delay (accediendo...) al acceder al programa
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
        char actividad_base [50];
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
printf("\nAccediendo");
fflush(stdout);
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
sleep(1);
printf("\n");

int salida = 0; //variable bandera (justificación en el comentario justo debajo)
do{ // bucle para que cuando el usuario cancele la salida del programa este vuelva al inicio
listado_opciones(); //llamamos a la funcion listado_opciones
int opcion_listado;
scanf("%d", &opcion_listado);

while(opcion_listado < 1 || opcion_listado >6){
    printf("Ingrese una opcion valida: ");
    scanf("%d", &opcion_listado);
}

switch (opcion_listado){
    case 1: 
        printf("1. Por centro");
        printf("2. Por horas");
        printf("3. Por tipo de actividad");
    case 2: 
    case 3: 
    case 4: 
    case 5:
    case 6: 
        
        char opcion_salida;

        printf("Desea salir? (Y/N):\n");
        scanf(" %c", &opcion_salida);

        while((opcion_salida != 'y') && (opcion_salida != 'Y') && (opcion_salida != 'n') && (opcion_salida != 'N')){
            printf("Elija una opcion valida:\n");
            scanf(" %c", &opcion_salida);
        }
        
        if(opcion_salida == 'y' || opcion_salida == 'Y'){
            salida = 1;
        }
        else if (opcion_salida == 'n' || opcion_salida == 'N' ){
            printf("Cancelando salida. Regresando al menu");
            
            fflush(stdout);
            for (int i = 0; i < 3; i++) {
                sleep(1);
                printf(".");
                fflush(stdout);
            }
            sleep(1);
            printf("\n");
        }

    default:
        break;
}

}while(salida == 0);

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
    printf("6. Salir\n"); 
}
