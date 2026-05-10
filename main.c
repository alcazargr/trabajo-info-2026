#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Para usar la funcion atoi, que pasa un numero string a entero
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
} unidad_centro;

typedef struct {
    unidad_centro centros[70];   //Estructura que contiene las estructuras del tipo del struct anterior. Lo he hecho asi para evitar usar matrices, pues cada unidad es un string.
    int num_centros;     //Maximo de 70 centros
} Lista_Centros;

typedef struct{
    char actividad[50];
} unidad_actividad;

typedef struct {
    unidad_actividad actividades[200]; //Maximo de actividades
    int num_actividades;
} Lista_Actividades;

typedef struct {
    int anio;
    int mes;
    int dia;
    char hora_min[6];
    char hora_max[6];
} S_Fecha_Seleccionada;



//Prototipos de funciones:

int listado_opciones();

Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas);
Lista_Actividades Listado_de_actividades(Registro vector_informacion[], int total_lineas);
int F_selector_centros (Lista_Centros Centros);
int F_selector_actividades (Lista_Actividades Actividades);
S_Fecha_Seleccionada F_selector_horas();
void F_Imprimir_Filtrado(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades,  int centro_filtrado, int actividad_filtrada, S_Fecha_Seleccionada fecha_filtrada);
void F_Imprimir_Filtrado_Fichero(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades,  int centro_filtrado, int actividad_filtrada, S_Fecha_Seleccionada fecha_filtrada );


void Opcion_1 (Registro vector_informacion[], int total_lineas);
int Opcion_2_1();
int Opcion_2_2();
float Ocupacion_media_centros(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_todos_centros(Registro vector_informacion[], int total_linea);
float Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_linea, char centro[]);
float Ocupacion_media_actividades(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_todas_actividades(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_actividad_especifica(Registro vector_informacion[], int total_lineas, char actividad[]);

// Estadisticas
void Horas_pico_actividad(Registro v[], int n);
void Actividad_con_mas_demanda(Registro v[], int n);
void Actividad_con_menos_demanda(Registro v[], int n);
void Centro_con_mayor_oferta(Registro v[], int n);
void Eficiencia_centros(Registro v[], int n);

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
fclose(ARCHIVO);
// COdigo para printear una linea del archivo: NO BORRAR. printf("%d %d %d %s %s %s %s %s %s %d %d %d %s" , vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);

int opcion_listado;
int opcion_estadisticas_1, opcion_estadisticas_2;
float resultado_opcion_centro, resultado_opcion_actividad;

do{
opcion_listado = listado_opciones();  //llamamos a la funcion listado_opciones


switch (opcion_listado){
    case 1: 
        Opcion_1(vector_informacion, total_lineas);
        break;
    case 2: 
        opcion_estadisticas_1 = Opcion_2_1();
        switch(opcion_estadisticas_1){
            case 1:
                opcion_estadisticas_2 = Opcion_2_2();
                
                if(opcion_estadisticas_2 == 1){
                    resultado_opcion_centro = Ocupacion_media_centros(vector_informacion, total_lineas);
                    printf("\nLa ocupacion media es de: %.2f por ciento\n", resultado_opcion_centro);
                }
                else if(opcion_estadisticas_2 == 2){

                    printf("La ocupacion media es de: %.2f por ciento\n");
                }

                

                printf("La ocupacion media es de: %.2f por ciento\n"); 

                break;
            case 2:
            	Actividad_con_mas_demanda(vector_informacion, total_lineas);
                break;
            case 3:
				Actividad_con_menos_demanda(vector_informacion, total_lineas);
                printf("La actividad con menos demanda es: \n");
                break;
            case 4:
            	 Centro_con_mayor_oferta(vector_informacion, total_lineas);
                break;
            case 5:
            	Eficiencia_centros(vector_informacion, total_lineas);
                break;
            case 6:
            	Horas_pico_actividad(vector_informacion, total_lineas); //Esta por ver si se hace???
                break;
            default:
                break;
        }
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


int listado_opciones(){
    printf("\n\n\n");
    printf("BIENVENIDO AL CENTRO DE GESTION DE DATOS DEPORTIVOS DE MADRID\n");
    printf("---------------------------------------------------\n");
    printf("Presione cualquier tecla para ingresar:");
    getchar();
    printf("\n");

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


int Opcion_2_1(){
    int opcion_estadisticas_1;
    printf("Estadisticas:\n");
    printf("1. Ocupacion media\n");
    printf("2. Horas pico segun actividad\n");
    printf("3. Actividad con mas demanda\n");
    printf("4. Actividad con menos demanda\n");
    printf("5. Centro con mayor oferta\n");
    printf("6. Eficiencia de los centros\n");
    scanf("%d", &opcion_estadisticas_1);
    return opcion_estadisticas_1;
}
int Opcion_2_2(){
    int opcion_estadisticas_2;
    printf("Seleccione el tipo de filtro:\n");
    printf("1. Filtrar por centro\n");
    printf("2. Filtrar por actividad\n");
    scanf("%d", &opcion_estadisticas_2);
    return opcion_estadisticas_2;
}

float Ocupacion_media_centros(Registro vector_informacion[], int total_lineas) 
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
float Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_lineas, char centro[])
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

float Ocupacion_media_actividades(Registro vector_informacion[], int total_lineas)
{
    Lista_Actividades Actividades = Listado_de_actividades(vector_informacion, total_lineas);
    int actividad_seleccionada = F_selector_actividades (Actividades);

    if(actividad_seleccionada == -1){
        return Ocupacion_media_todas_actividades(vector_informacion, total_lineas);
    }
    else{
        return Ocupacion_media_actividad_especifica(vector_informacion, total_lineas, Actividades.actividades[actividad_seleccionada].actividad);
    }
}

float Ocupacion_media_todas_actividades(Registro vector_informacion[], int total_lineas){
    int i;
    float ocupacion_media_todas_actividades;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for(i = 0; i<total_lineas; i++){
        total_plazas += vector_informacion[i].aforo.plazas;
        total_ocupadas += vector_informacion[i].aforo.ocupadas;
    }
    ocupacion_media_todas_actividades = ((total_ocupadas*1.0)/(total_plazas))*100;
    return ocupacion_media_todas_actividades;

}

float Ocupacion_media_actividad_especifica(Registro vector_informacion[], int total_lineas, char actividad[]){
    int i = 0;
    float ocupacion_media_actividad_especifica;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for(i = 0; i<total_lineas;i++){
        if(strcmp(vector_informacion[i].actividad.actividad_base, actividad) == 0){
            total_plazas += vector_informacion[i].aforo.plazas;
            total_ocupadas += vector_informacion[i].aforo.ocupadas;
        }
    }
    ocupacion_media_actividad_especifica = ((total_ocupadas*1.0)/(total_plazas))*100;
    return ocupacion_media_actividad_especifica;
}

//NUEVO
//Estadisticas completas(falta acbarlo)


//Actividad_con_mas_demanda
void Actividad_con_mas_demanda(Registro v[], int n) {
    Lista_Actividades LA = Listado_de_actividades(v, n);

    float max_ocup = -1;
    char act_max[50];
	int i;
    for ( i = 0; i < LA.num_actividades; i++) {
        float ocup = Ocupacion_media_actividad_especifica(v, n, LA.actividades[i].actividad);
        if (ocup > max_ocup) {
            max_ocup = ocup;
            strcpy(act_max, LA.actividades[i].actividad);
        }
    }

    printf("\nActividad con mayor demanda: %s (%.2f%%)\n", act_max, max_ocup);
}

//Actividad_con_menos_demanda
void Actividad_con_menos_demanda(Registro v[], int n) {
    Lista_Actividades LA = Listado_de_actividades(v, n);

    float min_ocup = 999999;
    char act_min[50];
	int i;
    for ( i = 0; i < LA.num_actividades; i++) {
        float ocup = Ocupacion_media_actividad_especifica(v, n, LA.actividades[i].actividad);
        if (ocup < min_ocup) {
            min_ocup = ocup;
            strcpy(act_min, LA.actividades[i].actividad);
        }
    }

    printf("\nActividad con menor demanda: %s (%.2f%%)\n", act_min, min_ocup);
}

//Centro_con_mayor_oferta
void Centro_con_mayor_oferta(Registro v[], int n) {
    Lista_Centros LC = Listado_de_centros(v, n);

    int i, j, max_plazas = -1;
    char centro_max[50];
	
    for ( i = 0; i < LC.num_centros; i++) {
        int plazas = 0;

        for ( j = 0; j < n; j++) {
            if (strcmp(v[j].actividad.centro, LC.centros[i].centro) == 0)
                plazas += v[j].aforo.plazas;
        }

        if (plazas > max_plazas) {
            max_plazas = plazas;
            strcpy(centro_max, LC.centros[i].centro);
        }
    }

    printf("\nCentro con mayor oferta: %s (%d plazas totales)\n", centro_max, max_plazas);
}

//Eficiencia_centros
void Eficiencia_centros(Registro v[], int n) {
    Lista_Centros LC = Listado_de_centros(v, n);

    printf("\nEficiencia de los centros:\n");
	int i;
    for (i = 0; i < LC.num_centros; i++) {
        float ocup = Ocupacion_media_centro_especifico(v, n, LC.centros[i].centro);
        printf("- %s: %.2f%%\n", LC.centros[i].centro, ocup);
    }
}

//Horas_pico_actividad
void Horas_pico_actividad(Registro v[], int n) {
    Lista_Actividades LA = Listado_de_actividades(v, n);
    int act = F_selector_actividades(LA);

    if (act == -1) {
        printf("\nDebe seleccionar una actividad concreta.\n");
        return;
    }

    char actividad[50];
    strcpy(actividad, LA.actividades[act].actividad);

    int ocup_hora[24] = {0};
    int sesiones[24] = {0};
	int i,h;
    for (i = 0; i < n; i++) {
        if (strcmp(v[i].actividad.actividad_base, actividad) == 0) {
            h = atoi(v[i].horario.hora_ini);
             if (h >= 0 && h < 24) {  // protección extra
            ocup_hora[h] += v[i].aforo.ocupadas;
            sesiones[h]++;
        	}
        }
    }

    int mejor_hora = -1;
    float media, mejor_media = -1;

    for (h = 0; h < 24; h++) {
        if (sesiones[h] > 0) {
            media = (float)ocup_hora[h] / sesiones[h];
            if (media > mejor_media) {
                mejor_media = media;
                mejor_hora = h;
            }
        }
    }
	
	if (mejor_hora != -1) {
        printf("\nHora pico de %s: %02d:00 (media %.2f personas)\n",
               actividad, mejor_hora, mejor_media);
    } else {
        printf("\nNo hay datos para la actividad %s\n", actividad);
    }
}

Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas) //Subfuncion. Filtrara todos los centros y guardara los  centros diferentes (SON 66) en una estructura que se devolvera.
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

Lista_Actividades Listado_de_actividades(Registro vector_informacion[], int total_lineas)
{
    Lista_Actividades resultado;
    int i;
    int j;
    resultado.num_actividades = 0;
    int repetido;

    for(i = 0; i<total_lineas; i++){
        repetido = 0;
        for(j = 0; j<resultado.num_actividades; j++){

            if(strcmp(resultado.actividades[j].actividad, vector_informacion[i].actividad.actividad_base) == 0){
                repetido = 1;
                break;
            }
        }
        if(repetido == 0){
            strcpy(resultado.actividades[resultado.num_actividades].actividad, vector_informacion[i].actividad.actividad_base);
            resultado.num_actividades++;
        }
    }
    return resultado;
}

int F_selector_centros (Lista_Centros Centros) //Permite al usuario seleccionar un centro en concreto o todos.
{

    printf("Seleccione el centro de interes:\n");
    int i = 0;
    int pag_max = (Centros.num_centros+8)/9;
    int pag = 1;
    int I = 0;
    char opcion;
    int bandera = 0;
    int numero_seleccionado;
    int centro_seleccionado;

    while(pag>=1&&pag<=pag_max&&bandera ==0)
    {
        printf("\nPagina %d/%d\n\n" ,pag ,pag_max);
        for (i = 0; i<=8; i++)
        { 
            I = i+9*(pag-1); //El maximo de I son 62, el numero de elementos de ese vector. Esta hardcodeado  por simplicidad.
            if (I<=Centros.num_centros-1) //Nos aseguramos de no entrar en un centro no existente
            {
			    printf("\n%d: \t %s" ,i+1 ,Centros.centros[I].centro);
            }
        }
    if (pag == pag_max)
        printf("\n0: \t Todos los centros\n"); 
    if (pag < pag_max)
        printf("\n\n S: \t Pagina siguiente");
    if (pag > 1)
        printf("\n A: \t Pagina anterior");


        printf("\nSeleccione un centro:\t");
            
        fflush(stdout);
        scanf(" %c" ,&opcion);  

        switch(opcion)
        {
            case 's':
            case 'S':
            if (pag!= pag_max)
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
                if (centro_seleccionado>Centros.num_centros) 
                {
                    printf("Opcion no valida.");
                    break;
                }
                else
                {
                    bandera = 1;
                    break;
                }
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
    int centro_filtrado = F_selector_centros (Centros);
    S_Fecha_Seleccionada fecha_filtrada = F_selector_horas();
    Lista_Actividades Actividades = Listado_de_actividades(vector_informacion, total_lineas);
    int actividad_filtrada = F_selector_actividades(Actividades);
    F_Imprimir_Filtrado(total_lineas, vector_informacion, Centros, Actividades, centro_filtrado, actividad_filtrada, fecha_filtrada);
    F_Imprimir_Filtrado_Fichero(total_lineas, vector_informacion, Centros, Actividades, centro_filtrado, actividad_filtrada, fecha_filtrada);
}

int F_selector_actividades (Lista_Actividades Actividades) 
{

    printf("Seleccione la actividad de interes:\n");
    int i = 0;
    int pag_max = (Actividades.num_actividades+8)/9; //Se redondea hacia arriba
    int pag = 1;
    int I = 0;
    char opcion;
    int bandera = 0;
    int numero_seleccionado;
    int actividad_seleccionada;

    while(pag>=1&&pag<=pag_max&&bandera == 0) //While para pasar de pagina
    {
        printf("\nPagina %d/%d\n\n" ,pag ,pag_max);

        for (i = 0; i<=8; i++) //For para cada elemento de la pagina
        { 
            I = i+9*(pag-1);
            if (I<=Actividades.num_actividades-1) //Nos aseguramos de no entrar en una actividad no existente
            {
                printf("\n%d: \t %s" ,i+1 ,Actividades.actividades[I].actividad);
            }

        }
        if (pag == pag_max)
            printf("\n0: \t Todas las actividades\n");
        if (pag < pag_max)
            printf("\n\n S: \t Pagina siguiente");
        if (pag > 1)
            printf("\n A: \t Pagina anterior");


        printf("\nSeleccione una actividad:\t");
            
        fflush(stdout);
        scanf(" %c" ,&opcion);  
        

        switch(opcion)
        {
            case 's':
            case 'S':
            if (pag!= pag_max)
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
                actividad_seleccionada = numero_seleccionado+9*(pag-1);
                if (actividad_seleccionada>Actividades.num_actividades)
                {
                    printf("Opcion no valida.");
                    break;
                }
                else
                {
                    bandera = 1;
                    break;
                }
            case '0':
                actividad_seleccionada = -1;
                bandera = 1;
                break;
            default:
                printf("La opcion seleccionada no es valida");
                break;
        }
    }
return actividad_seleccionada;
}

S_Fecha_Seleccionada F_selector_horas()
{
    char opcion;
    S_Fecha_Seleccionada resultado;

    printf("Quiere especificar una fecha para el filtro? (Y/N):\t");
    scanf(" %c" ,&opcion);

    switch (opcion) 
    {
        case 'y':
        case 'Y':
            printf("\nIntroduzca el annio de interes:\t");
            scanf("%d" ,&resultado.anio);
            printf("\nIntroduzca el mes  de interes: \n(Eje: 8 para agosto)\t");
            scanf("%d" ,&resultado.mes); 
            printf("\nIntroduzca el dia  de interes: \t");
            scanf("%d" ,&resultado.dia); 
            printf("\nIntroduzca la hora minima sobre la que le gustaria buscar. \n Formato: HH:MM \t");
            scanf("%s" ,resultado.hora_min);                        
            printf("\nIntroduzca la hora maxima sobre la que le gustaria buscar. \n Formato: HH:MM \t");
            scanf("%s" ,resultado.hora_max); 
        break;

        case 'n':
        case 'N': 
            resultado.anio = -1;
            resultado.mes = -1;
            resultado.dia = -1;
        break;
        
        default:
        break;
    }
return resultado;
}

void F_Imprimir_Filtrado(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades,  int centro_filtrado, int actividad_filtrada, S_Fecha_Seleccionada fecha_filtrada )
{
    int i;
    char pedir_tecla; //No se hace nada con esta variable.
    printf("Pulse cualquier tecla para imprimir todas las actividades con los filtros seleccionados.\t");
    scanf(" %c" ,&pedir_tecla); 

    printf("\n");
    printf("anio || mes || dia || dia_semana || hora_inicio || hora_fin || actividad_base || modalidad || centro || plazas || ocupadas || libres\n");
    for (i=0; i<=total_lineas-1; i++)
    {
        if (centro_filtrado==-1)
        {
            if (actividad_filtrada==-1)
            {
                if(fecha_filtrada.anio==-1)
                {
                    //Se printean todos:
                    printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                }
                else
                {
                    if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                    {
                        if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                        //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                        printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                    }
                }
            }
            else
            {
                if(fecha_filtrada.anio==-1)
                {
                    //Se printean todos los de esa actividad:
                    if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                    {
                        printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                    }
                }
                else
                {
                    //Comprobacion de actividad:
                     if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                    {
                        //Comprobacion de fecha:
                        if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                        {
                            if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                            //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                            {                                
                                printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                            }
                        }
                    }
                }
            }

        }
        else
        {
            if (actividad_filtrada==-1)
            {
                if(fecha_filtrada.anio==-1)
                {
                    //Comprobacion de centro:
                    if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                    {
                        //Se printean todos los de ese centro:
                        printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                    }
                }
                else
                {
                    //Comprobacion de centro:
                    if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                    {
                        //Comrpobacion de fecha:
                        if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                        {
                            if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                            //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                            {                                
                                printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                            }
                        }
                    }
                }
            }
            else
            {
                if(fecha_filtrada.anio==-1)
                {
                    //Comprobacion de centro:
                    if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                    {
                        //Comprobacion de actividad:
                        if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                        {
                            printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                        }
                    }                
                }
                else
                {
                    //Comprobacion de centro:
                    if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                    {
                        //Comprobacion de actividad:
                        if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                        {
                            //Comrpobacion de fecha:
                            if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                            {
                                if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                                //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                                {                                
                                    printf("%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                                }                
                            }
                        }
                    }
                }
            }            
        }
    }
}

void F_Imprimir_Filtrado_Fichero(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades,  int centro_filtrado, int actividad_filtrada, S_Fecha_Seleccionada fecha_filtrada )
{
    char opcion;
    int i;
    FILE *ARCHIVO_ESCRITURA_FILTRADO;
    printf("Desea guardar el resultado en un nuevo fichero? (Y/N):\t");
    scanf(" %c" ,&opcion);

    switch (opcion)
    {
        case 'n':
        case 'N':
        default:
            break;

        case 'y': 
        case 'Y':
            printf("Creando fichero...\n");
            //Codigo completamente copiado y ligeramente modificado de la funcion anterior:
            ARCHIVO_ESCRITURA_FILTRADO = fopen("deportes_ayuntamiento_filtros.txt" , "w"); 
            fprintf(ARCHIVO_ESCRITURA_FILTRADO, "anio mes dia dia_semana hora_inicio hora_fin actividad_base modalidad centro plazas ocupadas libres\n");
            for (i=0; i<=total_lineas-1; i++)
            {
                if (centro_filtrado==-1)
                {
                    if (actividad_filtrada==-1)
                    {
                        if(fecha_filtrada.anio==-1)
                        {
                            //Se printean todos:
                              fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                        }
                        else
                        {
                            if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                            {
                                if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                                //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                                fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                            }
                        }
                    }
                    else
                    {
                        if(fecha_filtrada.anio==-1)
                        {
                            //Se printean todos los de esa actividad:
                            if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                            {
                                fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                            }
                        }
                        else
                        {
                            //Comprobacion de actividad:
                            if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                            {
                                //Comprobacion de fecha:
                                if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                                {
                                    if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                                    //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                                    {                                
                                        fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                                    }
                                }
                            }
                        }
                    }

                }
                else
                {
                    if (actividad_filtrada==-1)
                    {
                        if(fecha_filtrada.anio==-1)
                        {
                            //Comprobacion de centro:
                            if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                            {
                                //Se printean todos los de ese centro:
                                fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                            }
                        }
                        else
                        {
                            //Comprobacion de centro:
                            if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                            {
                                //Comrpobacion de fecha:
                                if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                                {
                                    if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                                    //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                                    {                                
                                        fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if(fecha_filtrada.anio==-1)
                        {
                            //Comprobacion de centro:
                            if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                            {
                                //Comprobacion de actividad:
                                if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                                {
                                    fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                                }
                            }                
                        }
                        else
                        {
                            //Comprobacion de centro:
                            if(stricmp(vector_informacion[i].actividad.centro, Centros.centros[centro_filtrado-1].centro)==0)
                            {
                                //Comprobacion de actividad:
                                if(stricmp(vector_informacion[i].actividad.actividad_base, Actividades.actividades[actividad_filtrada-1].actividad)==0)
                                {
                                    //Comrpobacion de fecha:
                                    if(vector_informacion[i].fecha.anio == fecha_filtrada.anio && vector_informacion[i].fecha.mes == fecha_filtrada.mes && vector_informacion[i].fecha.dia == fecha_filtrada.dia) //Si el annio, mes y dia coinciden, se comprobara la hora.
                                    {
                                        if(strcmp(fecha_filtrada.hora_min, vector_informacion[i].horario.hora_ini)<=0 && strcmp(fecha_filtrada.hora_max, vector_informacion[i].horario.hora_fin)>=0)
                                        //Si la hora del filtro es menor que la hora a la que empieza ase evento y la hora del final del filtro es mayor a la que termina, se imprime, se printea.
                                        {                                
                                            fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n" ,vector_informacion[i].fecha.anio , vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base , vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                                        }                
                                    }
                                }
                            }
                        }
                    }            
                }
            }
        fclose(ARCHIVO_ESCRITURA_FILTRADO);
        break;
    }
}