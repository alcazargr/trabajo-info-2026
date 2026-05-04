#include <stdio.h>
#include <string.h>
#include <unistd.h> //para usar la función sleep para el delay (accediendo...) al acceder al programa
//#include <stdlib.h> //Para usar la funcion atoi, que pasa un numero string a entero
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

typedef struct { //Estructura para guardar un centro centros .
        char centro [50];
} unidad;

typedef struct {
    unidad centros[63];   //Estructura que contiene las 63 estructuras del tipo del struct anterior. Lo he hecho asi para evitar usar matrices, pues cada unidad es un string.
    int num_centros;     
} Lista_Centros;



//Prototipos de funciones:


void bienvenida();
int listado_opciones();
void listado_actividades();
Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas);
int F_selector_centros (Lista_Centros Centros);
int Opcion_1 (Registro vector_informacion[], int total_lineas);

void estadisticas();


//Funcion main:



int main ()
{
//Vector de estructuras:
Registro vector_informacion [N];


FILE*ARCHIVO; //Creacion del puntero del archivo y lectura
ARCHIVO = fopen("deportes_ayuntamiento.txt" , "r");
if (ARCHIVO == NULL)
{
    printf("ERROR: No se ha podido abrir el archivo. Comprueba el nombre y la carpeta.\n");
    return 0;
}
fscanf(ARCHIVO, "%*[^\n]\n"); //Se salta la linea de los headers.


int i = 0;
while(fscanf(ARCHIVO, "%d %d %d %s %s %s %s %s %s %d %d %d %s" , &vector_informacion[i].fecha.anio , &vector_informacion[i].fecha.mes, &vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, &vector_informacion[i].aforo.plazas, &vector_informacion[i].aforo.ocupadas, &vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso) != EOF)
{
   
fscanf(ARCHIVO, "%d %d %d %s %s %s %s %s %s %d %d %d %s" , &vector_informacion[i].fecha.anio , &vector_informacion[i].fecha.mes, &vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, &vector_informacion[i].aforo.plazas, &vector_informacion[i].aforo.ocupadas, &vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
i++;

} //Bucle de lectura del archivo
int total_lineas= i;
// COdigo para printear una linea del archivo: NO BORRAR. printf("%d %d %d %s %s %s %s %s %s %d %d %d %s" , vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);

bienvenida(); //funcion bienvenida
do{
int opcion_listado = listado_opciones();  //llamamos a la funcion listado_opciones
int opcion_case1; // variables provisionales para los subcasos dentro de cada case del switch
int opcion_case2;
int opcion_case3;
int opcion_case4;
int opcion_case5;


switch (opcion_listado){
    case 1: 
        listado_actividades();
        scanf("%d", &opcion_case1);
        fflush(stdin);

        if(opcion_case1 == 1){
            printf("Aquí tiene el listado de actividades por centro:\n");
            Opcion_1(vector_informacion, total_lineas);
        }
        if(opcion_case1 == 2){
            printf("Aquí tiene el listado de actividades por día:\n");
        }
        if(opcion_case1 == 3){
            printf("Aquí tiene el listado de actividades por horas:\n");
        }
        if(opcion_case1 == 4){
            printf("Aquí tiene el listado de actividades por tipo de actividad:\n");
        }
        break;
    case 2: 
        estadisticas();
        break;
    case 3: 
        break;
    case 4: 
        break;
    case 5:
        break;
    case 6: 
        printf("Hasta pronto!\n");
        printf("-------------\n");
        break;
    default:
        break;
}
}while(opcion_listado != 6);
return 0;
}

//FUNCIONES (EN ORDEN DE APARICION:)

void bienvenida(){
    printf("BIENVENIDO AL CENTRO DE GESTIÓN DE DATOS DEPORTIVOS\n");
    printf("---------------------------------------------------\n");
    printf("Presione cualquier tecla para ingresar:");
    getchar();
    fflush(stdin);
    printf("\nAccediendo");
    fflush(stdout);
        for (int i = 0; i < 3; i++) {
            sleep(1);
            printf(".");
            fflush(stdout);
        }
    sleep(1);
    printf("\n"); 
}


int listado_opciones(){
    int opcion_listado;
    printf("Listado de opciones\n");
    printf("-------------------\n");
    printf("1. Lista de actividades\n");
    printf("2. Estadísticas\n");
    printf("3. Resumen por centro\n");
    printf("4. Resumen por fecha\n");
    printf("5. Modificar el fichero\n"); 
    printf("6. Salir\n"); 
    scanf("%d", &opcion_listado);
    fflush(stdin);
    
    while(opcion_listado < 1 || opcion_listado >6){
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion_listado);
        fflush(stdin);
    }
    return opcion_listado;
}

void listado_actividades(){
    printf("Lista de actividades por:\n");
    printf("1. Centro\n");
    printf("2. Días\n");
    printf("3. Horas\n");
    printf("4. Tipo de actividad\n");
}

void estadisticas(){
    int opcion_estadisticas;
    printf("Estadisticas:");
    printf("1. Ocupación media");
    printf("2. Horas pico según actividad");
    printf("3. Actividad con más demanda");
    printf("4. Actividad con menos demanda");
    printf("5. Centro con mayor oferta");
    printf("6. Eficiencia de los centros");
    scanf("%d", &opcion_estadisticas);
    fflush(stdin);
}

 
    


Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas) //Subfuncion. Filtrara todos los centros y guardara los 63 centros diferentes en una estructura que se devolvera.
{    
    Lista_Centros resultado;
    int i;
    int j;
    resultado.num_centros = 0;
    int repetido; //V. Bandera


    for (i=0; i<=total_lineas-1; i++ )
    {
        repetido = 0;
        for(j = 0; j <resultado.num_centros; j++) //Comprueba que ese centro (el del elemento i) no este ya en ningun elemento del vector "resultado."
        {
            if(strcmp(resultado.centros[j].centro, vector_informacion[i].actividad.centro) == 0) //Ambos strings son iguales (el centro ya esta repetido)
            {
                repetido = 1;
                break;
            }
        }

        if(repetido == 0) //Si el centro no esta en ningun elemento del vector resultado, se copia en el actual, pues es nuevo.
        {
            strcpy(resultado.centros[resultado.num_centros].centro, vector_informacion[i].actividad.centro);
            resultado.num_centros++;
        }
    }
    return resultado;

    }

int F_selector_centros (Lista_Centros Centros) //Permite al usuario seleccionar un centro en concreto o todos.
{

    printf("Seleccione el centro cuyas actividades quiera ver:\n");
    int i = 0;
    int pag = 1;
    int I = 0;
    char opcion;
    int bandera = 0;
    int numero_seleccionado;
    int centro_seleccionado;

    while(pag>=1&&pag<=7&&bandera ==0) //El maximo de paginas son 7, pues hay 63 centros.Esta hardcodeado  por simplicidad.
    {
        for (i = 0; i<=8; i++)
        { 
            I = i+9*(pag-1); //El maximo de I son 62, el numero de elementos de ese vector. Esta hardcodeado  por simplicidad.
            printf("\n%d: \t %s" ,i+1 ,Centros.centros[I].centro);
        }
        if (pag ==1)
        {
            printf("\n\n S: \t Pagina siguiente");

        }
        else if (pag == 7)
        {   
            printf("\n 0: \t todos");
            printf("\n\n A: \tPagina anterior");
        }

        printf("\nSeleccione un centro:\t");
            
        fflush(stdout);
        scanf(" %c" ,&opcion);  
        fflush(stdin);

        switch(opcion)
        {
            case 's':
            case 'S':
            if (pag!= 7)
                {
                    pag++;
                }
                break;
            case 'a':
            case 'A':
            if (pag!= 1)
                {
                    pag--;
                }                
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                numero_seleccionado = opcion - '0';
                centro_seleccionado = numero_seleccionado+9*(pag-1);
                bandera = 1;
                break;
            case '0':
                centro_seleccionado = -1;
                bandera = 1;
                break;
            default:
                printf("La opcion seleccionada no es valida");
                break;
        }
    }
return centro_seleccionado;
}
int Opcion_1(Registro vector_informacion[], int total_lineas) //Funcion de la opcion 1 (Listado de actividades):
{
    Lista_Centros Centros = Listado_de_centros(vector_informacion, total_lineas);
    int centro_seleccionado = F_selector_centros (Centros);


}
