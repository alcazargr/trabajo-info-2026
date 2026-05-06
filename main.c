#include <stdio.h>
#include <string.h>
//#include <stdlib.h> //Para usar la funcion atoi, que pasa un numero string a entero
#define N 5001

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
Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas);
int F_selector_centros (Lista_Centros Centros);
void Opcion_1 (Registro vector_informacion[], int total_lineas);
float Ocupacion_media(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_todos_centros(Registro vector_informacion[], int total_linea);
float Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_linea, char centro[]);
void Opcion_2();


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
while(fscanf(ARCHIVO, "%d %d %d %s %s %s %s %s %s %d %d %d %s", &vector_informacion[i].fecha.anio, &vector_informacion[i].fecha.mes, &vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base, vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, &vector_informacion[i].aforo.plazas, &vector_informacion[i].aforo.ocupadas, &vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso) == 13)  // Bucle de lectura del archivo. Cuando no de los 13 campos, es que habra terminado el archivo.
{
    i++;
}
int total_lineas = i;
// COdigo para printear una linea del archivo: NO BORRAR. printf("%d %d %d %s %s %s %s %s %s %d %d %d %s" , vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);

bienvenida(); //funcion bienvenida
int opcion_listado;
do{
opcion_listado = listado_opciones();  //llamamos a la funcion listado_opciones


switch (opcion_listado){
    case 1: 
        Opcion_1(vector_informacion, total_lineas);
        break;
    case 2: 
        Opcion_2();
        break;
    case 3: 
        break;
    case 4: 
        printf("Hasta pronto!\n");
        printf("-------------\n");
        break;
    default:
        break;
}
}while(opcion_listado != 4);
return 0;
}

//FUNCIONES (EN ORDEN DE APARICION:)

void bienvenida(){
    printf("BIENVENIDO AL CENTRO DE GESTIoN DE DATOS DEPORTIVOS\n");
    printf("---------------------------------------------------\n");
    printf("Presione cualquier tecla para ingresar:");
    getchar();
    printf("\nAccediendo");
    printf("\n");
}


int listado_opciones(){
    int opcion_listado;
    printf("Listado de opciones\n");
    printf("-------------------\n");
    printf("1. Lista de actividades\n");
    printf("2. Estadisticas\n");
    printf("3. Modificar el fichero\n"); 
    printf("4. Salir\n"); 
    scanf("%d", &opcion_listado);
    
    while(opcion_listado < 1 || opcion_listado >4){
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion_listado);
    }
    return opcion_listado;
}


void Opcion_2(){
    int opcion_estadisticas;
    printf("Estadisticas:\n");
    printf("1. Ocupacion media\n");
    printf("2. Horas pico segun actividad\n");
    printf("3. Actividad con mas demanda\n");
    printf("4. Actividad con menos demanda\n");
    printf("5. Centro con mayor oferta\n");
    printf("6. Eficiencia de los centros\n");
    scanf("%d", &opcion_estadisticas);
}

float Ocupacion_media(Registro vector_informacion[], int total_lineas) //por terminar
{
	Lista_Centros Centros = Listado_de_centros(vector_informacion, total_lineas);
	int centro_seleccionado = F_selector_centros (Centros); //Funcion que permite al usuario seleccionar un centro en concreto o todos. Se usara para filtrar los centros a la hora de calcular la ocupacion media.
	
	if(centro_seleccionado == -1) //Si el usuario ha seleccionado todos los centros, se calcula la ocupacion media de todos los centros.
    {
        return Ocupacion_media_todos_centros(vector_informacion, total_lineas);
    }
    else //Si el usuario ha seleccionado un centro en concreto, se calcula la ocupacion media de ese centro.
    {
        return Ocupacion_media_centro_especifico(vector_informacion, total_lineas, Centros.centros[centro_seleccionado].centro);
    }
}

float Ocupacion_media_todos_centros(Registro vector_informacion[], int total_linea){
    int i;
    float ocupacion_media_todos;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for(i = 0; i <total_linea; i++){
        total_plazas += vector_informacion[i].aforo.plazas;
        total_ocupadas += vector_informacion[i].aforo.ocupadas;
    }
    ocupacion_media_todos =((total_ocupadas*1.0) / (total_plazas))*100;
    return ocupacion_media_todos;
}
float Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_lineas, char centro[]) //por terminar
{
    int i;
    float ocupacion_media_centro;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for(i = 0; i< total_lineas; i++){
        if(strcmp(vector_informacion[i].actividad.centro, centro) == 0){
            total_plazas += vector_informacion[i].aforo.plazas;
            total_ocupadas += vector_informacion[i].aforo.ocupadas;
        }
    }
    ocupacion_media_centro = ((total_ocupadas*1.0)/(total_plazas))*100;
    return ocupacion_media_centro;
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
    if (pag < 7)
        printf("\n\n S: \t Pagina siguiente");
    if (pag > 1)
        printf("\n A: \t Pagina anterior");
    if (pag == 7)
        printf("\n 0: \t Todos los centros");

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
void Opcion_1(Registro vector_informacion[], int total_lineas) //Funcion de la opcion 1 (Listado de actividades):
{
    Lista_Centros Centros = Listado_de_centros(vector_informacion, total_lineas);
    int centro_seleccionado = F_selector_centros (Centros);
    
}
