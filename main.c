#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para usar atoi, que pasa un numero string a entero

#define N 5100
#define MAX_CENTROS 70
#define MAX_ACTIVIDADES 200
#define MAX_TIPOS 50

typedef struct { // Estructura principal del archivo, dividida en subestructuras.
    struct {
        int anio;
        int mes;
        int dia;
        char dia_semana[10];
    } fecha;

    struct {
        char hora_ini[6];
        char hora_fin[6];
    } horario;

    struct {
        char actividad_base[50];
        char modalidad[50];
        char centro[50];
        char tipo_uso[50];
    } actividad;

    struct {
        int plazas;
        int ocupadas;
        int libres;
    } aforo;
} Registro;

typedef struct {
    char centro[50];
    float ocupacion_media;
} unidad_centro;

typedef struct {
    unidad_centro centros[MAX_CENTROS];
    int num_centros;
} Lista_Centros;

typedef struct {
    char actividad[50];
    float ocupacion_media;
} unidad_actividad;

typedef struct {
    unidad_actividad actividades[MAX_ACTIVIDADES];
    int num_actividades;
} Lista_Actividades;

typedef struct {
    char tipo[50];
} unidad_tipo;

typedef struct {
    unidad_tipo tipos[MAX_TIPOS];
    int num_tipos;
} Lista_Tipos;

typedef struct {
    int anio;
    int mes;
    int dia;
    char hora_min[6];
    char hora_max[6];
} S_Fecha_Seleccionada;

typedef struct {
    char centro[50];
    int actividades_distintas;
    int sesiones_totales;
    int plazas_totales;
} Oferta_Centro;

// Prototipos de funciones ordenados segun el flujo principal del programa:


// Funcion que muestra el menu principal:
int F_listado_opciones();

// Funcion principal de la opcion 1:
void F_Opcion_1(Registro vector_informacion[], int total_lineas);

// Subfunciones de la opcion 1:
Lista_Centros F_Listado_de_centros(Registro vector_informacion[], int total_lineas);
int F_selector_centros(Lista_Centros Centros);
Lista_Actividades F_Listado_de_actividades(Registro vector_informacion[], int total_lineas);
int F_selector_actividades(Lista_Actividades Actividades);
Lista_Tipos F_Listado_de_tipos(Registro vector_informacion[], int total_lineas);
int F_selector_tipos(Lista_Tipos Tipos);
S_Fecha_Seleccionada F_selector_horas();
void F_Imprimir_Filtrado(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades, Lista_Tipos Tipos, int centro_filtrado, int actividad_filtrada, int tipo_filtrado, S_Fecha_Seleccionada fecha_filtrada);
int F_Cumple_filtros(Registro r, Lista_Centros Centros, Lista_Actividades Actividades, Lista_Tipos Tipos, int centro_filtrado, int actividad_filtrada, int tipo_filtrado, S_Fecha_Seleccionada fecha_filtrada);
void F_Imprimir_Filtrado_Fichero(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades, Lista_Tipos Tipos, int centro_filtrado, int actividad_filtrada, int tipo_filtrado, S_Fecha_Seleccionada fecha_filtrada);

// Funcion principal de la opcion 2:
void F_Opcion_2(Registro vector_informacion[], int total_lineas);

// Subfunciones de la opcion 2:
int F_Opcion_2_1();
int F_Opcion_2_2();
float F_Ocupacion_media_centros(Registro vector_informacion[], int total_lineas);
float F_Ocupacion_media_todos_centros(Registro vector_informacion[], int total_lineas);
float F_Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_lineas, char centro[]);
float F_Ocupacion_media_actividades(Registro vector_informacion[], int total_lineas);
float F_Ocupacion_media_todas_actividades(Registro vector_informacion[], int total_lineas);
float F_Ocupacion_media_actividad_especifica(Registro vector_informacion[], int total_lineas, char actividad[]);
void F_Eficiencia_centros(Registro v[], int n);

// Funcion principal de la opcion 3:
void F_Opcion_3(Registro vector_informacion[], int total_lineas);

// Subfunciones de la opcion 3:
int F_Opcion_3_1();
void F_Horas_pico_actividad(Registro v[], int n);
void F_Actividad_con_mas_demanda(Registro v[], int n);
void F_Actividad_con_menos_demanda(Registro v[], int n);
void F_Centro_con_mayor_oferta(Registro v[], int n);
void F_Grafico_Centros(Registro vector_informacion[], int total_lineas);
void F_Grafico_Actividades(Registro vector_informacion[], int total_lineas);

// Funcion principal de la opcion 4:
void F_Opcion_4(Registro vector_informacion[], int total_lineas);

// Subfunciones de la opcion 4:
void F_Modificar_Actividad(Registro v[], int n);
void F_Eliminar_Salto_Linea(char cadena[]);
void F_Guardar_Fichero(Registro vector_informacion[], int n);
void F_Anadir_Actividad(Registro v[], int *n);


// Funcion main


int main()
{
    Registro vector_informacion[N];

    FILE *ARCHIVO;
    ARCHIVO = fopen("deportes_ayuntamiento.txt", "r");

    if (ARCHIVO == NULL)
    {
        printf("ERROR: No se ha podido abrir el archivo. Comprueba el nombre y la carpeta.\n");
        return 0;
    }

    // Se salta la linea de los headers.
    fscanf(ARCHIVO, "%*[^\n]\n");

    int i = 0;

    while (i < N &&fscanf(ARCHIVO, "%d %d %d %s %s %s %s %s %s %d %d %d %s", &vector_informacion[i].fecha.anio, &vector_informacion[i].fecha.mes, &vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base, vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, &vector_informacion[i].aforo.plazas, &vector_informacion[i].aforo.ocupadas, &vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso ) == 13)
    {
        i++;
    }

    int total_lineas = i;
    fclose(ARCHIVO);

    int opcion_listado;


    do
    {
        opcion_listado = F_listado_opciones();

        switch (opcion_listado)
        {
            case 1:
                F_Opcion_1(vector_informacion, total_lineas);
                break;

            case 2:
                F_Opcion_2(vector_informacion, total_lineas);
                break;

            case 3:
                F_Opcion_3(vector_informacion, total_lineas);
                break;

            case 4:
                F_Opcion_4(vector_informacion, total_lineas);
    			break;

            case 5:
                printf("Hasta pronto!\n");
                printf("-------------\n");
                break;

            default:
                printf("\nOpcion no valida.\n");
                break;
        }

    } while (opcion_listado != 5);

    return 0;
}



// FUNCIONES:


// Funcion que muestra el menu principal:

int F_listado_opciones()
{
    int opcion_listado;

    printf("\n\n\n");
    printf("BIENVENIDO AL CENTRO DE GESTION DE DATOS DEPORTIVOS DE MADRID\n");
    printf("-------------------------------------------------------------\n\n\n");
    printf("Listado de opciones del programa:\n");
    printf("--------------------------------\n\n");
    printf("1. Lista de actividades\n");
    printf("Esta opcion permite filtrar y mostrar las actividades que cumplan con los parametros especificados.\n\n");
    printf("2. Estadisticas.\n");
    printf("Esta opcion permite calcular diferentes estadisticas sobre la informacion del fichero, como la ocupacion media.\n\n");
    printf("3. Analisis de datos.\n");
    printf("Esta opcion permite analizar algunas caracteristicas sobre los datos del fichero, como el centro con mayor demanda.\n\n");
    printf("4. Modificar el fichero\n");
    printf("Esta opcion permite realizar diversas modificaciones al fichero.\n\n");

    printf("5. Salir\n\n");
    printf("Seleccione una opcion:\t ");

    scanf("%d", &opcion_listado);

    while (opcion_listado < 1 || opcion_listado > 5)
    {
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion_listado);
    }

    return opcion_listado;
}


// Funcion principal de la opcion 1:

void F_Opcion_1(Registro vector_informacion[], int total_lineas)
{
    Lista_Centros Centros;
    Lista_Actividades Actividades;
    Lista_Tipos Tipos;

    int centro_filtrado;
    int actividad_filtrada;
    int tipo_filtrado;

    S_Fecha_Seleccionada fecha_filtrada;

    Centros = F_Listado_de_centros(vector_informacion, total_lineas);
    centro_filtrado = F_selector_centros(Centros);

    if (centro_filtrado == -2)
    {
        printf("\nVolviendo al menu principal...\n");
        return;
    }

    Actividades = F_Listado_de_actividades(vector_informacion, total_lineas);
    actividad_filtrada = F_selector_actividades(Actividades);

    if (actividad_filtrada == -2)
    {
        printf("\nVolviendo al menu principal...\n");
        return;
    }

    Tipos = F_Listado_de_tipos(vector_informacion, total_lineas);
    tipo_filtrado = F_selector_tipos(Tipos);

    if (tipo_filtrado == -2)
    {
        printf("\nVolviendo al menu principal...\n");
        return;
    }

    fecha_filtrada = F_selector_horas();

    F_Imprimir_Filtrado(total_lineas, vector_informacion, Centros, Actividades, Tipos, centro_filtrado, actividad_filtrada, tipo_filtrado, fecha_filtrada);
    F_Imprimir_Filtrado_Fichero(total_lineas, vector_informacion, Centros, Actividades, Tipos, centro_filtrado, actividad_filtrada, tipo_filtrado, fecha_filtrada);
}


// Subfunciones de la opcion 1:

Lista_Centros F_Listado_de_centros(Registro vector_informacion[], int total_lineas)
{
    Lista_Centros resultado;
    int i, j;
    int repetido;

    resultado.num_centros = 0;

    for (i = 0; i < total_lineas; i++)
    {
        repetido = 0;

        for (j = 0; j < resultado.num_centros; j++)
        {
            if (strcmp(resultado.centros[j].centro, vector_informacion[i].actividad.centro) == 0)
            {
                repetido = 1;
                break;
            }
        }

        if (repetido == 0 && resultado.num_centros < MAX_CENTROS)
        {
            strcpy(resultado.centros[resultado.num_centros].centro, vector_informacion[i].actividad.centro);
            resultado.num_centros++;
        }
    }

    return resultado;
}

int F_selector_centros(Lista_Centros Centros)
{
    int i;
    int indice_real;
    int pag_max = (Centros.num_centros + 8) / 9;
    int pag = 1;
    char opcion;
    int bandera = 0;
    int numero_seleccionado;
    int centro_seleccionado = -1;

    printf("\nSeleccione el centro de interes:\n");

    while (pag >= 1 && pag <= pag_max && bandera == 0)
    {
        printf("\nPagina %d/%d\n", pag, pag_max);

        printf("x: Volver al menu principal\n");
        printf("0: Todos los centros\n\n");

        for (i = 0; i < 9; i++)
        {
            indice_real = i + 9 * (pag - 1);

            if (indice_real < Centros.num_centros)
            {
                printf("%d: %s\n", i + 1, Centros.centros[indice_real].centro);
            }
        }
        printf("\n");

        if (pag < pag_max)
        {
            printf("S: Pagina siguiente\n");
        }

        if (pag > 1)
        {
            printf("A: Pagina anterior\n");
        }

        printf("Seleccione un centro: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case 's':
            case 'S':
                if (pag < pag_max)
                {
                    pag++;
                }
                else
                {
                    printf("Ya esta en la ultima pagina.\n");
                }
                break;

            case 'a':
            case 'A':
                if (pag > 1)
                {
                    pag--;
                }
                else
                {
                    printf("Ya esta en la primera pagina.\n");
                }
                break;
            
            case 'X':
            case 'x':
                centro_seleccionado = -2;
                bandera = 1;
                break;

            case '0':
                centro_seleccionado = -1;
                bandera = 1;
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
                centro_seleccionado = (numero_seleccionado - 1) + 9 * (pag - 1);

                if (centro_seleccionado >= Centros.num_centros)
                {
                    printf("Opcion no valida.\n");
                }
                else
                {
                    bandera = 1;
                }
                break;

            default:
                printf("La opcion seleccionada no es valida.\n");
                break;
        }
    }

    return centro_seleccionado;
}

Lista_Actividades F_Listado_de_actividades(Registro vector_informacion[], int total_lineas)
{
    Lista_Actividades resultado;
    int i, j;
    int repetido;

    resultado.num_actividades = 0;

    for (i = 0; i < total_lineas; i++)
    {
        repetido = 0;

        for (j = 0; j < resultado.num_actividades; j++)
        {
            if (strcmp(resultado.actividades[j].actividad, vector_informacion[i].actividad.actividad_base) == 0)
            {
                repetido = 1;
                break;
            }
        }

        if (repetido == 0 && resultado.num_actividades < MAX_ACTIVIDADES)
        {
            strcpy(resultado.actividades[resultado.num_actividades].actividad, vector_informacion[i].actividad.actividad_base);
            resultado.num_actividades++;
        }
    }

    return resultado;
}

int F_selector_actividades(Lista_Actividades Actividades)
{
    int i;
    int indice_real;
    int pag_max = (Actividades.num_actividades + 8) / 9;
    int pag = 1;
    char opcion;
    int bandera = 0;
    int numero_seleccionado;
    int actividad_seleccionada = -1;

    printf("\nSeleccione la actividad de interes:\n");

    while (pag >= 1 && pag <= pag_max && bandera == 0)
    {
        printf("\nPagina %d/%d\n", pag, pag_max);
        
        printf("x: Volver al menu principal\n");
        printf("0: Todas las actividades\n\n");

        for (i = 0; i < 9; i++)
        {
            indice_real = i + 9 * (pag - 1);

            if (indice_real < Actividades.num_actividades)
            {
                printf("%d: %s\n", i + 1, Actividades.actividades[indice_real].actividad);
            }
        }
        printf("\n");

        if (pag < pag_max)
        {
            printf("S: Pagina siguiente\n");
        }

        if (pag > 1)
        {
            printf("A: Pagina anterior\n");
        }

        printf("Seleccione una actividad: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case 's':
            case 'S':
                if (pag < pag_max)
                {
                    pag++;
                }
                else
                {
                    printf("Ya esta en la ultima pagina.\n");
                }
                break;

            case 'a':
            case 'A':
                if (pag > 1)
                {
                    pag--;
                }
                else
                {
                    printf("Ya esta en la primera pagina.\n");
                }
                break;
            
            case 'X':
            case 'x':
                actividad_seleccionada = -2;
                bandera = 1;
                break;

            case '0':
                actividad_seleccionada = -1;
                bandera = 1;
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
                actividad_seleccionada = (numero_seleccionado - 1) + 9 * (pag - 1);

                if (actividad_seleccionada >= Actividades.num_actividades)
                {
                    printf("Opcion no valida.\n");
                }
                else
                {
                    bandera = 1;
                }
                break;

            default:
                printf("La opcion seleccionada no es valida.\n");
                break;
        }
    }

    return actividad_seleccionada;
}

Lista_Tipos F_Listado_de_tipos(Registro vector_informacion[], int total_lineas)
{
    Lista_Tipos resultado;
    int i, j;
    int repetido;

    resultado.num_tipos = 0;

    for (i = 0; i < total_lineas; i++)
    {
        repetido = 0;

        for (j = 0; j < resultado.num_tipos; j++)
        {
            if (strcmp(resultado.tipos[j].tipo, vector_informacion[i].actividad.tipo_uso) == 0)
            {
                repetido = 1;
                break;
            }
        }

        if (repetido == 0 && resultado.num_tipos < MAX_TIPOS)
        {
            strcpy(resultado.tipos[resultado.num_tipos].tipo, vector_informacion[i].actividad.tipo_uso);
            resultado.num_tipos++;
        }
    }
    return resultado;
}

int F_selector_tipos(Lista_Tipos Tipos)
{
    int i;
    int indice_real;
    int pag_max = (Tipos.num_tipos + 8) / 9;
    int pag = 1;
    char opcion;
    int bandera = 0;
    int numero_seleccionado;
    int tipo_seleccionado = -1;

    printf("\nSeleccione el tipo de actividad:\n");

    while (pag >= 1 && pag <= pag_max && bandera == 0)
    {
        printf("\nPagina %d/%d\n", pag, pag_max);

        printf("x: Volver al menu principal\n");
        printf("0: Todos los tipos\n\n");

        for (i = 0; i < 9; i++)
        {
            indice_real = i + 9 * (pag - 1);

            if (indice_real < Tipos.num_tipos)
            {
                printf("%d: %s\n", i + 1, Tipos.tipos[indice_real].tipo);
            }
        }
        printf("\n");

        if (pag < pag_max)
        {
            printf("S: Pagina siguiente\n");
        }

        if (pag > 1)
        {
            printf("A: Pagina anterior\n");
        }

        printf("Seleccione un tipo de actividad:\t");
        scanf(" %c", &opcion);

        switch (opcion)
        {
            case 's':
            case 'S':
                if (pag < pag_max)
                {
                    pag++;
                }
                else
                {
                    printf("Ya esta en la ultima pagina.\n");
                }
                break;

            case 'a':
            case 'A':
                if (pag > 1)
                {
                    pag--;
                }
                else
                {
                    printf("Ya esta en la primera pagina.\n");
                }
                break;
            
            case 'X':
            case 'x':
                tipo_seleccionado = -2;
                bandera = 1;
                break;

            case '0':
                tipo_seleccionado = -1;
                bandera = 1;
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
                tipo_seleccionado = (numero_seleccionado - 1) + 9 * (pag - 1);

                if (tipo_seleccionado >= Tipos.num_tipos)
                {
                    printf("Opcion no valida.\n");
                }
                else
                {
                    bandera = 1;
                }
                break;

            default:
                printf("La opcion seleccionada no es valida.\n");
                break;
        }
    }

    return tipo_seleccionado;
}

S_Fecha_Seleccionada F_selector_horas()
{
    char opcion;
    S_Fecha_Seleccionada resultado;

    printf("\nQuiere especificar una fecha para el filtro? (Y/N): ");
    scanf(" %c", &opcion);

    switch (opcion)
    {
        case 'y':
        case 'Y':
            printf("Introduzca el annio de interes:\t");
            scanf("%d", &resultado.anio);

            printf("Introduzca el mes de interes:\t");
            scanf("%d", &resultado.mes);

            printf("Introduzca el dia de interes:\t");
            scanf("%d", &resultado.dia);

            printf("Introduzca la hora minima. Formato HH:MM:\t");
            scanf("%s", resultado.hora_min);

            printf("Introduzca la hora maxima. Formato HH:MM:\t");
            scanf("%s", resultado.hora_max);
            break;

        case 'n':
        case 'N':
            resultado.anio = -1;
            resultado.mes = -1;
            resultado.dia = -1;
            strcpy(resultado.hora_min, "00:00");
            strcpy(resultado.hora_max, "23:59");
            break;

        default:
            printf("Opcion no valida. No se aplicara filtro de fecha.\n");
            resultado.anio = -1;
            resultado.mes = -1;
            resultado.dia = -1;
            strcpy(resultado.hora_min, "00:00");
            strcpy(resultado.hora_max, "23:59");
            break;
    }

    return resultado;
}

void F_Imprimir_Filtrado(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades, Lista_Tipos Tipos, int centro_filtrado, int actividad_filtrada, int tipo_filtrado, S_Fecha_Seleccionada fecha_filtrada)
{
    int i;
    int contador = 0;
    char pedir_tecla;

    printf("\nPulse cualquier tecla para imprimir las actividades filtradas: ");
    scanf(" %c", &pedir_tecla);

    printf("\n");
    printf("anio || mes || dia || dia_semana || hora_inicio || hora_fin || actividad_base || modalidad || centro || plazas || ocupadas || libres || tipo_actividad\n");

    for (i = 0; i < total_lineas; i++)
    {
        if (F_Cumple_filtros(vector_informacion[i], Centros, Actividades, Tipos, centro_filtrado, actividad_filtrada, tipo_filtrado, fecha_filtrada))
        {
            printf("%d %d %d %s %s %s %s %s %s %d %d %d %s\n", vector_informacion[i].fecha.anio, vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base, vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
            contador++;
        }
    }

    printf("\nTotal de registros encontrados: %d\n", contador);
}

int F_Cumple_filtros(Registro r, Lista_Centros Centros, Lista_Actividades Actividades, Lista_Tipos Tipos, int centro_filtrado, int actividad_filtrada, int tipo_filtrado, S_Fecha_Seleccionada fecha_filtrada)
{
    int cumple = 1;

    // Comprobacion del centro.
    if (centro_filtrado != -1)
    {
        if (strcmp(r.actividad.centro, Centros.centros[centro_filtrado].centro) != 0)
        {
            cumple = 0;
        }
    }

    // Comprobacion de la actividad.
    if (actividad_filtrada != -1)
    {
        if (strcmp(r.actividad.actividad_base, Actividades.actividades[actividad_filtrada].actividad) != 0)
        {
            cumple = 0;
        }
    }

    // Comprobacion del tipo de actividad.
    if (tipo_filtrado != -1)
    {
        if (strcmp(r.actividad.tipo_uso, Tipos.tipos[tipo_filtrado].tipo) != 0)
        {
            cumple = 0;
        }
    }

    // Comprobacion de la fecha y de las horas.
    if (fecha_filtrada.anio != -1)
    {
        if (r.fecha.anio != fecha_filtrada.anio || r.fecha.mes != fecha_filtrada.mes || r.fecha.dia != fecha_filtrada.dia)
        {
            cumple = 0;
        }
        else
        {
            /*
                Se comparan las horas como cadenas porque estan en formato HH:MM.
                En este formato, strcmp funciona correctamente para ordenar horas.
            */
            if (strcmp(r.horario.hora_ini, fecha_filtrada.hora_min) < 0 || strcmp(r.horario.hora_fin, fecha_filtrada.hora_max) > 0)
            {
                cumple = 0;
            }
        }
    }
    return cumple;
}

void F_Imprimir_Filtrado_Fichero(int total_lineas, Registro vector_informacion[], Lista_Centros Centros, Lista_Actividades Actividades, Lista_Tipos Tipos, int centro_filtrado, int actividad_filtrada, int tipo_filtrado, S_Fecha_Seleccionada fecha_filtrada)
{
    char opcion;
    int i;
    int contador = 0;

    FILE *ARCHIVO_ESCRITURA_FILTRADO;

    printf("\nDesea guardar el resultado en un nuevo fichero? (Y/N): ");
    scanf(" %c", &opcion);

    switch (opcion)
    {
        case 'y':
        case 'Y':
            ARCHIVO_ESCRITURA_FILTRADO = fopen("deportes_ayuntamiento_filtros.txt", "w");

            if (ARCHIVO_ESCRITURA_FILTRADO == NULL)
            {
                printf("ERROR: No se ha podido crear el fichero.\n");
                return;
            }

            fprintf(ARCHIVO_ESCRITURA_FILTRADO, "anio mes dia dia_semana hora_inicio hora_fin actividad_base modalidad centro plazas ocupadas libres tipo_actividad\n");

            for (i = 0; i < total_lineas; i++)
            {
                if (F_Cumple_filtros(vector_informacion[i], Centros, Actividades, Tipos, centro_filtrado, actividad_filtrada, tipo_filtrado, fecha_filtrada))
                {
                    fprintf(ARCHIVO_ESCRITURA_FILTRADO, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n", vector_informacion[i].fecha.anio, vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base, vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
                    contador++;
                }
            }

            fclose(ARCHIVO_ESCRITURA_FILTRADO);

            printf("Fichero creado correctamente: deportes_ayuntamiento_filtros.txt\n");
            printf("Registros guardados: %d\n", contador);
            break;

        case 'n':
        case 'N':
            printf("No se ha guardado ningun fichero.\n");
            break;

        default:
            printf("Opcion no valida. No se ha guardado ningun fichero.\n");
            break;
    }
}


// Funcion principal de la opcion 2:

void F_Opcion_2(Registro vector_informacion[], int total_lineas)
{
    int opcion_estadisticas;
    int opcion_estadisticas_media;
    float resultado_opcion_centro;
    float resultado_opcion_actividad;

    do
    {
        opcion_estadisticas = F_Opcion_2_1();

        switch (opcion_estadisticas)
        {
            case 1:
                do
                {
                    opcion_estadisticas_media = F_Opcion_2_2();

                    switch (opcion_estadisticas_media)
                    {
                        case 1:
                            resultado_opcion_centro = F_Ocupacion_media_centros(vector_informacion, total_lineas);

                            if (resultado_opcion_centro >= 0)
                            {
                                printf("\nLa ocupacion media del centro es de: %.2f %%\n", resultado_opcion_centro);
                            }
                            break;

                        case 2:
                            resultado_opcion_actividad = F_Ocupacion_media_actividades(vector_informacion, total_lineas);

                            if (resultado_opcion_actividad >= 0)
                            {
                                printf("\nLa ocupacion media de la actividad es de: %.2f %% \n", resultado_opcion_actividad);
                            }
                            break;

                        case 3:
                            printf("\nVolviendo al menu principal...\n");
                            break;

                        default:
                            printf("\nOpcion no valida. Intente de nuevo.\n");
                            break;
                    }

                } while (opcion_estadisticas_media < 1 || opcion_estadisticas_media > 3);
                break;

            case 2:
                F_Eficiencia_centros(vector_informacion, total_lineas);
                break;

            case 3:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }

    } while (opcion_estadisticas < 1 || opcion_estadisticas > 3);
}


// Subfunciones de la opcion 2:

int F_Opcion_2_1()
{
    int opcion_estadisticas_1;
    int entrada_correcta;

    printf("\nEstadisticas:\n");
    printf("1. Ocupacion media\n");
    printf("2. Eficiencia de los centros\n");
    printf("3. Volver al menu principal\n");
    printf("Seleccione una opcion: ");

    entrada_correcta = scanf("%d", &opcion_estadisticas_1);

    if (entrada_correcta != 1)
    {
        while (getchar() != '\n');
        opcion_estadisticas_1 = -1;
    }

    return opcion_estadisticas_1;
}

int F_Opcion_2_2()
{
    int opcion_estadisticas_2;
    int entrada_correcta;

    printf("\nOcupacion media:\n");
    printf("1. Por centro\n");
    printf("2. Por actividad\n");
    printf("3. Volver al menu principal\n");
    printf("Seleccione una opcion: ");

    entrada_correcta = scanf("%d", &opcion_estadisticas_2);

    if (entrada_correcta != 1)
    {
        while (getchar() != '\n');
        opcion_estadisticas_2 = -1;
    }

    return opcion_estadisticas_2;
}

float F_Ocupacion_media_centros(Registro vector_informacion[], int total_lineas)
{
    Lista_Centros Centros = F_Listado_de_centros(vector_informacion, total_lineas);
    int centro_seleccionado = F_selector_centros(Centros);

    if (centro_seleccionado == -2)
    {
        printf("\nVolviendo al menu principal...\n");
        return -1;
    }

    if (centro_seleccionado == -1)
    {
        return F_Ocupacion_media_todos_centros(vector_informacion, total_lineas);
    }
    else
    {
        return F_Ocupacion_media_centro_especifico(vector_informacion, total_lineas, Centros.centros[centro_seleccionado].centro);
    }
}

float F_Ocupacion_media_todos_centros(Registro vector_informacion[], int total_lineas)
{
    int i;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for (i = 0; i < total_lineas; i++)
    {
        total_plazas += vector_informacion[i].aforo.plazas;
        total_ocupadas += vector_informacion[i].aforo.ocupadas;
    }

    if (total_plazas == 0)
    {
        return 0;
    }

    return ((float)total_ocupadas / total_plazas) * 100;
}

float F_Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_lineas, char centro[])
{
    int i;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for (i = 0; i < total_lineas; i++)
    {
        if (strcmp(vector_informacion[i].actividad.centro, centro) == 0)
        {
            total_plazas += vector_informacion[i].aforo.plazas;
            total_ocupadas += vector_informacion[i].aforo.ocupadas;
        }
    }

    if (total_plazas == 0)
    {
        return 0;
    }

    return ((float)total_ocupadas / total_plazas) * 100;
}

float F_Ocupacion_media_actividades(Registro vector_informacion[], int total_lineas)
{
    Lista_Actividades Actividades = F_Listado_de_actividades(vector_informacion, total_lineas);
    int actividad_seleccionada = F_selector_actividades(Actividades);

    if (actividad_seleccionada == -2)
    {
        printf("\nVolviendo al menu principal...\n");
        return -1;
    }

    if (actividad_seleccionada == -1)
    {
        return F_Ocupacion_media_todas_actividades(vector_informacion, total_lineas);
    }
    else
    {
        return F_Ocupacion_media_actividad_especifica(vector_informacion, total_lineas, Actividades.actividades[actividad_seleccionada].actividad);
    }
}

float F_Ocupacion_media_todas_actividades(Registro vector_informacion[], int total_lineas)
{
    int i;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for (i = 0; i < total_lineas; i++)
    {
        total_plazas += vector_informacion[i].aforo.plazas;
        total_ocupadas += vector_informacion[i].aforo.ocupadas;
    }

    if (total_plazas == 0)
    {
        return 0;
    }

    return ((float)total_ocupadas / total_plazas) * 100;
}

float F_Ocupacion_media_actividad_especifica(Registro vector_informacion[], int total_lineas, char actividad[])
{
    int i;
    int total_plazas = 0;
    int total_ocupadas = 0;

    for (i = 0; i < total_lineas; i++)
    {
        if (strcmp(vector_informacion[i].actividad.actividad_base, actividad) == 0)
        {
            total_plazas += vector_informacion[i].aforo.plazas;
            total_ocupadas += vector_informacion[i].aforo.ocupadas;
        }
    }

    if (total_plazas == 0)
    {
        return 0;
    }

    return ((float)total_ocupadas / total_plazas) * 100;
}

void F_Eficiencia_centros(Registro v[], int n)
{
    Lista_Centros LC = F_Listado_de_centros(v, n);
    Oferta_Centro ofertas[MAX_CENTROS];

    int i, j, k;
    int repetida;
    int max_actividades = 0;
    int max_plazas = 0;

    float ocupacion;
    float variedad;
    float volumen_oferta;
    float eficiencia;

    /*
        La eficiencia de cada centro se calcula como un valor compuesto.
        Asi no se repite exactamente el mismo calculo que la ocupacion media.

        Factores usados:
        - Ocupacion: porcentaje de plazas ocupadas respecto a las plazas totales del centro.
        - Variedad: actividades distintas del centro comparadas con el centro con mas variedad.
        - Volumen de oferta: plazas totales del centro comparadas con el centro que mas plazas ofrece.

        Formula final:
        eficiencia = ocupacion * 0.60 + variedad * 0.25 + volumen_oferta * 0.15
    */

    // Primero se recopilan los datos necesarios de cada centro.
    for (i = 0; i < LC.num_centros; i++)
    {
        char actividades_distintas[MAX_ACTIVIDADES][50];

        strcpy(ofertas[i].centro, LC.centros[i].centro);
        ofertas[i].actividades_distintas = 0;
        ofertas[i].sesiones_totales = 0;
        ofertas[i].plazas_totales = 0;

        for (j = 0; j < n; j++)
        {
            if (strcmp(v[j].actividad.centro, LC.centros[i].centro) == 0)
            {
                ofertas[i].sesiones_totales++;
                ofertas[i].plazas_totales += v[j].aforo.plazas;

                // Se comprueba si la actividad ya ha sido contada en este centro.
                repetida = 0;

                for (k = 0; k < ofertas[i].actividades_distintas; k++)
                {
                    if (strcmp(actividades_distintas[k], v[j].actividad.actividad_base) == 0)
                    {
                        repetida = 1;
                        break;
                    }
                }

                // Si la actividad no estaba repetida, se guarda como nueva actividad distinta.
                if (repetida == 0 && ofertas[i].actividades_distintas < MAX_ACTIVIDADES)
                {
                    strcpy(actividades_distintas[ofertas[i].actividades_distintas], v[j].actividad.actividad_base);
                    ofertas[i].actividades_distintas++;
                }
            }
        }

        // Se guardan los maximos para poder normalizar los datos en porcentaje.
        if (ofertas[i].actividades_distintas > max_actividades)
        {
            max_actividades = ofertas[i].actividades_distintas;
        }

        if (ofertas[i].plazas_totales > max_plazas)
        {
            max_plazas = ofertas[i].plazas_totales;
        }
    }

    printf("\nEficiencia de los centros:\n");
    printf("--------------------------\n\n");

    // Finalmente se calcula e imprime la eficiencia de cada centro.
    for (i = 0; i < LC.num_centros; i++)
    {
        ocupacion = F_Ocupacion_media_centro_especifico(v, n, ofertas[i].centro);

        if (max_actividades == 0)
        {
            variedad = 0;
        }
        else
        {
            variedad = ((float)ofertas[i].actividades_distintas / max_actividades) * 100;
        }

        if (max_plazas == 0)
        {
            volumen_oferta = 0;
        }
        else
        {
            volumen_oferta = ((float)ofertas[i].plazas_totales / max_plazas) * 100;
        }

        eficiencia = ocupacion * 0.60 + variedad * 0.25 + volumen_oferta * 0.15;

        printf("Centro: %s\n", ofertas[i].centro);
        printf("  Ocupacion: %.2f%%\n", ocupacion);
        printf("  Variedad de actividades: %.2f%% (%d actividades distintas)\n", variedad, ofertas[i].actividades_distintas);
        printf("  Volumen de oferta: %.2f%% (%d plazas ofertadas)\n", volumen_oferta, ofertas[i].plazas_totales);
        printf("  Eficiencia final: %.2f%%\n\n", eficiencia);
    }

    printf("Formula utilizada:\n");
    printf("------------------\n");
    printf("Eficiencia = ocupacion * 0.60 + variedad * 0.25 + volumen de oferta * 0.15\n\n");
    printf("Donde:\n");
    printf("- Ocupacion: porcentaje de plazas ocupadas respecto a las plazas totales del centro.\n");
    printf("- Variedad: actividades distintas del centro comparadas con el centro que mas actividades distintas tiene.\n");
    printf("- Volumen de oferta: plazas totales del centro comparadas con el centro que mas plazas ofrece.\n\n");
}


// Funcion principal de la opcion 3:

void F_Opcion_3(Registro vector_informacion[], int total_lineas)
{
    int opcion_analisis;

    do
    {
        opcion_analisis = F_Opcion_3_1();

        switch (opcion_analisis)
        {
            case 1:
                F_Horas_pico_actividad(vector_informacion, total_lineas);
                break;

            case 2:
                F_Actividad_con_mas_demanda(vector_informacion, total_lineas);
                break;

            case 3:
                F_Actividad_con_menos_demanda(vector_informacion, total_lineas);
                break;

            case 4:
                F_Centro_con_mayor_oferta(vector_informacion, total_lineas);
                break;

            case 5:
                F_Grafico_Centros(vector_informacion, total_lineas);
                break;

            case 6:
                F_Grafico_Actividades(vector_informacion, total_lineas);
                break;

            case 7:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }

    } while (opcion_analisis < 1 || opcion_analisis > 7);
}


// Subfunciones de la opcion 3:

int F_Opcion_3_1()
{
    int opcion_analisis;
    int entrada_correcta;

    printf("\nQue desea saber?\n");
    printf("1. Horas pico de una actividad.\n");
    printf("2. Actividad con mas demanda.\n");
    printf("3. Actividad con menos demanda.\n");
    printf("4. Centro con mayor oferta de actividades.\n");
    printf("5. Descargar hoja de calculo con la ocupacion media de cada centro deportivo.\n");
    printf("6. Descargar hoja de calculo con la ocupacion media de cada actividad.\n");
    printf("7. Volver al menu principal.\n");
    printf("Seleccione una opcion:\t");

    entrada_correcta = scanf("%d", &opcion_analisis);

    if (entrada_correcta != 1)
    {
        while (getchar() != '\n');
        opcion_analisis = -1;
    }

    return opcion_analisis;
}

void F_Horas_pico_actividad(Registro v[], int n)
{
    Lista_Actividades LA = F_Listado_de_actividades(v, n);
    int act = F_selector_actividades(LA);

    if (act == -2)
    {
        printf("\nVolviendo al menu principal...\n");
        return;
    }

    if (act == -1)
    {
        printf("\nDebe seleccionar una actividad concreta.\n");
        return;
    }

    char actividad[50];
    strcpy(actividad, LA.actividades[act].actividad);

    int ocup_hora[24] = {0};
    int sesiones[24] = {0};

    int i, h;

    for (i = 0; i < n; i++)
    {
        if (strcmp(v[i].actividad.actividad_base, actividad) == 0)
        {
            h = atoi(v[i].horario.hora_ini);

            if (h >= 0 && h < 24)
            {
                ocup_hora[h] += v[i].aforo.ocupadas;
                sesiones[h]++;
            }
        }
    }

    int mejor_hora = -1;
    float media;
    float mejor_media = -1;

    for (h = 0; h < 24; h++)
    {
        if (sesiones[h] > 0)
        {
            media = (float)ocup_hora[h] / sesiones[h];

            if (media > mejor_media)
            {
                mejor_media = media;
                mejor_hora = h;
            }
        }
    }

    if (mejor_hora != -1)
    {
        printf("\nHora pico de %s: %02d:00 (media %.2f personas)\n", actividad, mejor_hora, mejor_media);
    }
    else
    {
        printf("\nNo hay datos para la actividad %s\n", actividad);
    }
}

void F_Actividad_con_mas_demanda(Registro v[], int n)
{
    Lista_Actividades LA = F_Listado_de_actividades(v, n);

    float max_ocupacion_porcentual = -1;
    char actividad_max_porcentual[50] = "";

    int max_ocupacion_absoluta = -1;
    char actividad_max_absoluta[50] = "";

    int i, j;

    for (i = 0; i < LA.num_actividades; i++)
    {
        float ocupacion_porcentual;
        int ocupacion_absoluta = 0;

        // Calculamos la ocupacion porcentual de la actividad actual.
        ocupacion_porcentual = F_Ocupacion_media_actividad_especifica(v, n, LA.actividades[i].actividad);

        // Calculamos la ocupacion absoluta de la actividad actual.
        for (j = 0; j < n; j++)
        {
            if (strcmp(v[j].actividad.actividad_base, LA.actividades[i].actividad) == 0)
            {
                ocupacion_absoluta += v[j].aforo.ocupadas;
            }
        }

        if (ocupacion_porcentual > max_ocupacion_porcentual)
        {
            max_ocupacion_porcentual = ocupacion_porcentual;
            strcpy(actividad_max_porcentual, LA.actividades[i].actividad);
        }

        if (ocupacion_absoluta > max_ocupacion_absoluta)
        {
            max_ocupacion_absoluta = ocupacion_absoluta;
            strcpy(actividad_max_absoluta, LA.actividades[i].actividad);
        }
    }

    printf(
        "\nActividad con mayor demanda porcentual: %s (%.2f%%)\n",
        actividad_max_porcentual,
        max_ocupacion_porcentual
    );

    printf(
        "Actividad con mayor demanda absoluta: %s (%d plazas ocupadas)\n",
        actividad_max_absoluta,
        max_ocupacion_absoluta
    );
}

void F_Actividad_con_menos_demanda(Registro v[], int n)
{
    Lista_Actividades LA = F_Listado_de_actividades(v, n);

    float min_ocupacion_porcentual = 999999;
    char actividad_min_porcentual[50] = "";

    int min_ocupacion_absoluta = 999999;
    char actividad_min_absoluta[50] = "";

    int i, j;

    for (i = 0; i < LA.num_actividades; i++)
    {
        float ocupacion_porcentual;
        int ocupacion_absoluta = 0;

        // Calculamos la ocupacion porcentual de la actividad actual.
        ocupacion_porcentual = F_Ocupacion_media_actividad_especifica(v, n, LA.actividades[i].actividad);

        // Calculamos la ocupacion absoluta de la actividad actual.
        for (j = 0; j < n; j++)
        {
            if (strcmp(v[j].actividad.actividad_base, LA.actividades[i].actividad) == 0)
            {
                ocupacion_absoluta += v[j].aforo.ocupadas;
            }
        }

        // Comprobamos si esta actividad tiene la menor ocupacion porcentual.
        if (ocupacion_porcentual < min_ocupacion_porcentual)
        {
            min_ocupacion_porcentual = ocupacion_porcentual;
            strcpy(actividad_min_porcentual, LA.actividades[i].actividad);
        }

        // Comprobamos si esta actividad tiene la menor ocupacion absoluta.
        if (ocupacion_absoluta < min_ocupacion_absoluta)
        {
            min_ocupacion_absoluta = ocupacion_absoluta;
            strcpy(actividad_min_absoluta, LA.actividades[i].actividad);
        }
    }

    printf(
        "\nActividad con menor demanda porcentual: %s (%.2f%%)\n",
        actividad_min_porcentual,
        min_ocupacion_porcentual
    );

    printf(
        "Actividad con menor demanda absoluta: %s (%d plazas ocupadas)\n",
        actividad_min_absoluta,
        min_ocupacion_absoluta
    );
}

void F_Centro_con_mayor_oferta(Registro v[], int n)
{
    Lista_Centros LC = F_Listado_de_centros(v, n);

    Oferta_Centro oferta_actual;
    Oferta_Centro oferta_max;

    int i, j, k;
    int repetida;

    /*
        Inicializamos la oferta maxima con valores bajos.
        Asi, el primer centro analizado sustituira estos datos.
    */
    strcpy(oferta_max.centro, "");
    oferta_max.actividades_distintas = -1;
    oferta_max.sesiones_totales = 0;
    oferta_max.plazas_totales = 0;

    /*
        Recorremos todos los centros.
        Para cada centro contamos:
        - cuantas actividades distintas tiene
        - cuantas sesiones aparecen en el fichero
        - cuantas plazas totales ofrece
    */
    for (i = 0; i < LC.num_centros; i++)
    {
        strcpy(oferta_actual.centro, LC.centros[i].centro);
        oferta_actual.actividades_distintas = 0;
        oferta_actual.sesiones_totales = 0;
        oferta_actual.plazas_totales = 0;

        for (j = 0; j < n; j++)
        {
            if (strcmp(v[j].actividad.centro, oferta_actual.centro) == 0)
            {
                oferta_actual.sesiones_totales++;
                oferta_actual.plazas_totales += v[j].aforo.plazas;

                /*
                    Comprobamos si esta actividad ya habia aparecido antes
                    en el mismo centro. Si no habia aparecido, se cuenta como
                    una nueva actividad distinta.
                */
                repetida = 0;

                for (k = 0; k < j; k++)
                {
                    if (
                        strcmp(v[k].actividad.centro, oferta_actual.centro) == 0 &&
                        strcmp(v[k].actividad.actividad_base, v[j].actividad.actividad_base) == 0
                    )
                    {
                        repetida = 1;
                        break;
                    }
                }

                if (repetida == 0)
                {
                    oferta_actual.actividades_distintas++;
                }
            }
        }

        /*
            El centro con mayor oferta sera el que tenga mas actividades distintas.
            Si hay empate, se elige el que tenga mas plazas totales.
        */
        if (
            oferta_actual.actividades_distintas > oferta_max.actividades_distintas ||
            (
                oferta_actual.actividades_distintas == oferta_max.actividades_distintas &&
                oferta_actual.plazas_totales > oferta_max.plazas_totales
            )
        )
        {
            oferta_max = oferta_actual;
        }
    }

    if (oferta_max.actividades_distintas == -1)
    {
        printf("\nNo hay datos suficientes para calcular el centro con mayor oferta.\n");
    }
    else
    {
        printf("\nCentro con mayor oferta de actividades:\n");
        printf("--------------------------------------\n");
        printf("Centro: %s\n", oferta_max.centro);
        printf("Actividades distintas ofertadas: %d\n", oferta_max.actividades_distintas);
        printf("Sesiones totales registradas: %d\n", oferta_max.sesiones_totales);
        printf("Plazas totales ofertadas: %d\n", oferta_max.plazas_totales);
    }
}

void F_Grafico_Centros(Registro vector_informacion[], int total_lineas)
{
    Lista_Centros Centros = F_Listado_de_centros(vector_informacion, total_lineas);
    FILE* GRAFICA;
    int i;

    GRAFICA = fopen("Ocupacion_Media_Centros.csv", "w");

    if (GRAFICA == NULL)
    {
        printf("ERROR: No se ha podido crear el fichero Ocupacion_Media_Centros.csv\n");
        printf("Comprueba que el archivo no este abierto y que el programa tenga permisos para escribir en la carpeta.\n");
        return;
    }

    fprintf(GRAFICA, "Centro;Ocupacion_media\n");

    for (i = 0; i < Centros.num_centros; i++)
    {
        Centros.centros[i].ocupacion_media = F_Ocupacion_media_centro_especifico(vector_informacion, total_lineas, Centros.centros[i].centro);

        fprintf(GRAFICA, "%s;%.2f\n", Centros.centros[i].centro, Centros.centros[i].ocupacion_media);
    }

    fclose(GRAFICA);

    printf("La hoja de calculo Ocupacion_Media_Centros.csv se ha descargado correctamente\n");
}

void F_Grafico_Actividades(Registro vector_informacion[], int total_lineas)
{
    Lista_Actividades Actividades = F_Listado_de_actividades(vector_informacion, total_lineas);
    FILE* GRAFICA;
    int i;

    GRAFICA = fopen("Ocupacion_Media_Actividades.csv", "w");

    if (GRAFICA == NULL)
    {
        printf("ERROR: No se ha podido crear el fichero Ocupacion_Media_Actividades.csv\n");
        printf("Comprueba que el archivo no este abierto y que el programa tenga permisos para escribir en la carpeta.\n");
        return;
    }

    fprintf(GRAFICA, "Actividad;Ocupacion_media\n");

    for (i = 0; i < Actividades.num_actividades; i++)
    {
        Actividades.actividades[i].ocupacion_media = F_Ocupacion_media_actividad_especifica(vector_informacion, total_lineas, Actividades.actividades[i].actividad);

        fprintf(GRAFICA, "%s;%.2f\n", Actividades.actividades[i].actividad, Actividades.actividades[i].ocupacion_media);
    }

    fclose(GRAFICA);

    printf("La hoja de calculo Ocupacion_Media_Actividades.csv se ha descargado correctamente\n");
}


// Funcion principal de la opcion 4:

void F_Opcion_4(Registro vector_informacion[], int total_lineas)
{
    int opcion_modificar;
    int entrada_correcta;

    do
    {
        printf("\nModificar fichero:\n");
        printf("-----------------\n\n");
        printf("1. Sobreescribir una actividad existente.\n");
        printf("2. Anadir una actividad nueva.\n");
        printf("3. Volver al menu principal.\n");
        printf("Seleccione una opcion: ");

        entrada_correcta = scanf("%d", &opcion_modificar);

        if (entrada_correcta != 1)
        {
            while (getchar() != '\n');
            opcion_modificar = -1;
        }

        switch (opcion_modificar)
        {
            case 1:
                F_Modificar_Actividad(vector_informacion, total_lineas);
                F_Guardar_Fichero(vector_informacion, total_lineas);
                break;

            case 2:
                F_Anadir_Actividad(vector_informacion, &total_lineas);
                F_Guardar_Fichero(vector_informacion, total_lineas);
                break;

            case 3:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }

    } while (opcion_modificar < 1 || opcion_modificar > 3);
}


// Subfunciones de la opcion 4:

void F_Modificar_Actividad(Registro v[], int n)
{
    int i;
    int opcion;

    printf("\nListado de actividades\n");
    printf("----------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d -> %s | %s | %s\n", i, v[i].actividad.actividad_base, v[i].actividad.centro, v[i].horario.hora_ini);
    }

    printf("\nSeleccione el indice de la actividad: ");
    scanf("%d", &opcion);

    if (opcion < 0 || opcion >= n)
    {
        printf("Indice no valido.\n");
        return;
    }

    getchar();

    printf("\nIntroduzca el nuevo nombre actividad:\t");
    fgets(v[opcion].actividad.actividad_base, 50, stdin);
    F_Eliminar_Salto_Linea(v[opcion].actividad.actividad_base);

    printf("Introduzca la nueva modalidad de la actividad:\t");
    fgets(v[opcion].actividad.modalidad, 50, stdin);
    F_Eliminar_Salto_Linea(v[opcion].actividad.modalidad);

    printf("Introduzca el nuevo centro donde se realiza la actividad:\t");
    fgets(v[opcion].actividad.centro, 50, stdin);
    F_Eliminar_Salto_Linea(v[opcion].actividad.centro);

    printf("Introduzca el nuevo numero de plazas de la actividad:\t");
    scanf("%d", &v[opcion].aforo.plazas);

    printf("Introduzca el nuevo numero de plazas ocupadas de la actividad:\t");
    scanf("%d", &v[opcion].aforo.ocupadas);

    v[opcion].aforo.libres = v[opcion].aforo.plazas - v[opcion].aforo.ocupadas;

    getchar();

    printf("Introduzca el nuevo tipo de uso de la actividad:\t");
    fgets(v[opcion].actividad.tipo_uso, 50, stdin);
    F_Eliminar_Salto_Linea(v[opcion].actividad.tipo_uso);

    printf("\nActividad modificada correctamente.\n");
}

void F_Eliminar_Salto_Linea(char cadena[])
{
    cadena[strcspn(cadena, "\n")] = '\0';
}

void F_Guardar_Fichero(Registro vector_informacion[], int n)
{
    FILE *f;
    int i;
    f = fopen("deportes_ayuntamiento.txt", "w");

    if (f == NULL)
    {
        printf("Error al guardar el fichero.\n");
        return;
    }

    fprintf(f,"anio mes dia dia_semana hora_inicio hora_fin actividad_base modalidad centro plazas ocupadas libres tipo_actividad\n");

    for (i = 0; i < n; i++)
    {
        fprintf(f, "%d %d %d %s %s %s %s %s %s %d %d %d %s\n", vector_informacion[i].fecha.anio, vector_informacion[i].fecha.mes, vector_informacion[i].fecha.dia, vector_informacion[i].fecha.dia_semana, vector_informacion[i].horario.hora_ini, vector_informacion[i].horario.hora_fin, vector_informacion[i].actividad.actividad_base, vector_informacion[i].actividad.modalidad, vector_informacion[i].actividad.centro, vector_informacion[i].aforo.plazas, vector_informacion[i].aforo.ocupadas, vector_informacion[i].aforo.libres, vector_informacion[i].actividad.tipo_uso);
    }

    fclose(f);
    printf("\nFichero actualizado correctamente.\n");
}

void F_Anadir_Actividad(Registro v[], int *n)
{
    Registro nuevo;
    if (*n >= N)
    {
        printf("No hay espacio para mas actividades.\n");
        return;
    }

    printf("\nNueva actividad\n");
    printf("----------------\n");

    printf("Introduzca el anio de la actividad:\t");
    scanf("%d", &nuevo.fecha.anio);

    printf("Introduzca el mes de la actividad:\t");
    scanf("%d", &nuevo.fecha.mes);

    printf("Introduzca el dia de la actividad:\t");
    scanf("%d", &nuevo.fecha.dia);

    getchar();

    printf("Introduzca el dia de la semana de la actividad:\t ");
    fgets(nuevo.fecha.dia_semana, 10, stdin);
    F_Eliminar_Salto_Linea(nuevo.fecha.dia_semana);

    printf("Introduzca la hora de inicio de la actividad. (Formato: HH:MM):\t ");
    fgets(  nuevo.horario.hora_ini, 6, stdin);
    F_Eliminar_Salto_Linea(nuevo.horario.hora_ini);

    printf("Introduzca la hora de fin de la actividad. (Formato: HH:MM):\t ");
    fgets(  nuevo.horario.hora_fin, 6, stdin);
    F_Eliminar_Salto_Linea(nuevo.horario.hora_fin);

    printf("Introduzca la actividad:\t");
    fgets(nuevo.actividad.actividad_base, 50, stdin);
    F_Eliminar_Salto_Linea(nuevo.actividad.actividad_base);

    printf("Introduzca la modalidad de la actividad:\t");
    fgets(nuevo.actividad.modalidad, 50, stdin);
    F_Eliminar_Salto_Linea(nuevo.actividad.modalidad);

    printf("Introduzca el centro de la actividad:\t");
    fgets(nuevo.actividad.centro, 50, stdin);
    F_Eliminar_Salto_Linea(nuevo.actividad.centro);

    printf("Introduzca el numero de plazas totales de la actividad:\t");
    scanf("%d", &nuevo.aforo.plazas);

    printf("Introduzca el numero de plazas ocupadas de la actividad:\t");
    scanf("%d", &nuevo.aforo.ocupadas);

    nuevo.aforo.libres = nuevo.aforo.plazas - nuevo.aforo.ocupadas;

    getchar();

    printf("Introduzca el tipo de uso de la actividad:\t");
    fgets(nuevo.actividad.tipo_uso, 50, stdin);
    F_Eliminar_Salto_Linea(nuevo.actividad.tipo_uso);

    v[*n] = nuevo;

    (*n)++;

    printf("\nActividad anadida correctamente.\n");
}
