#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para usar atoi, que pasa un numero string a entero

#define N 5001
#define MAX_CENTROS 70
#define MAX_ACTIVIDADES 200

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
} unidad_centro;

typedef struct {
    unidad_centro centros[MAX_CENTROS];
    int num_centros;
} Lista_Centros;

typedef struct {
    char actividad[50];
} unidad_actividad;

typedef struct {
    unidad_actividad actividades[MAX_ACTIVIDADES];
    int num_actividades;
} Lista_Actividades;

typedef struct {
    int anio;
    int mes;
    int dia;
    char hora_min[6];
    char hora_max[6];
} S_Fecha_Seleccionada;


// Prototipos de funciones

int listado_opciones();

Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas);
Lista_Actividades Listado_de_actividades(Registro vector_informacion[], int total_lineas);

int F_selector_centros(Lista_Centros Centros);
int F_selector_actividades(Lista_Actividades Actividades);
S_Fecha_Seleccionada F_selector_horas();

void Opcion_1(Registro vector_informacion[], int total_lineas);

void Imprimir_registro_pantalla(Registro r);
void Imprimir_registro_fichero(FILE *fichero, Registro r);

int Cumple_filtros(
    Registro r,
    Lista_Centros Centros,
    Lista_Actividades Actividades,
    int centro_filtrado,
    int actividad_filtrada,
    S_Fecha_Seleccionada fecha_filtrada
);

void F_Imprimir_Filtrado(
    int total_lineas,
    Registro vector_informacion[],
    Lista_Centros Centros,
    Lista_Actividades Actividades,
    int centro_filtrado,
    int actividad_filtrada,
    S_Fecha_Seleccionada fecha_filtrada
);

void F_Imprimir_Filtrado_Fichero(
    int total_lineas,
    Registro vector_informacion[],
    Lista_Centros Centros,
    Lista_Actividades Actividades,
    int centro_filtrado,
    int actividad_filtrada,
    S_Fecha_Seleccionada fecha_filtrada
);

int Opcion_2_1();
int Opcion_2_2();

float Ocupacion_media_centros(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_todos_centros(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_lineas, char centro[]);

float Ocupacion_media_actividades(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_todas_actividades(Registro vector_informacion[], int total_lineas);
float Ocupacion_media_actividad_especifica(Registro vector_informacion[], int total_lineas, char actividad[]);

// Estadisticas

void Horas_pico_actividad(Registro v[], int n);
void Actividad_con_mas_demanda(Registro v[], int n);
void Actividad_con_menos_demanda(Registro v[], int n);
void Centro_con_mayor_oferta(Registro v[], int n);
void Eficiencia_centros(Registro v[], int n);


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

    while (
        i < N &&
        fscanf(
            ARCHIVO,
            "%d %d %d %s %s %s %s %s %s %d %d %d %s",
            &vector_informacion[i].fecha.anio,
            &vector_informacion[i].fecha.mes,
            &vector_informacion[i].fecha.dia,
            vector_informacion[i].fecha.dia_semana,
            vector_informacion[i].horario.hora_ini,
            vector_informacion[i].horario.hora_fin,
            vector_informacion[i].actividad.actividad_base,
            vector_informacion[i].actividad.modalidad,
            vector_informacion[i].actividad.centro,
            &vector_informacion[i].aforo.plazas,
            &vector_informacion[i].aforo.ocupadas,
            &vector_informacion[i].aforo.libres,
            vector_informacion[i].actividad.tipo_uso
        ) == 13
    )
    {
        i++;
    }

    int total_lineas = i;
    fclose(ARCHIVO);

    int opcion_listado;
    int opcion_estadisticas_1;
    int opcion_estadisticas_2;
    float resultado_opcion_centro;
    float resultado_opcion_actividad;

    do
    {
        opcion_listado = listado_opciones();

        switch (opcion_listado)
        {
            case 1:
                Opcion_1(vector_informacion, total_lineas);
                break;

            case 2:
                opcion_estadisticas_1 = Opcion_2_1();

                switch (opcion_estadisticas_1)
                {
                    case 1:
                        opcion_estadisticas_2 = Opcion_2_2();

                        if (opcion_estadisticas_2 == 1)
                        {
                            resultado_opcion_centro = Ocupacion_media_centros(vector_informacion, total_lineas);
                            printf("\nLa ocupacion media del centro es de: %.2f por ciento\n", resultado_opcion_centro);
                        }
                        else if (opcion_estadisticas_2 == 2)
                        {
                            resultado_opcion_actividad = Ocupacion_media_actividades(vector_informacion, total_lineas);
                            printf("\nLa ocupacion media de la actividad es de: %.2f por ciento\n", resultado_opcion_actividad);
                        }
                        else
                        {
                            printf("\nOpcion no valida.\n");
                        }

                        break;

                    case 2:
                        Horas_pico_actividad(vector_informacion, total_lineas);
                        break;

                    case 3:
                        Actividad_con_mas_demanda(vector_informacion, total_lineas);
                        break;

                    case 4:
                        Actividad_con_menos_demanda(vector_informacion, total_lineas);
                        break;

                    case 5:
                        Centro_con_mayor_oferta(vector_informacion, total_lineas);
                        break;

                    case 6:
                        Eficiencia_centros(vector_informacion, total_lineas);
                        break;

                    default:
                        printf("\nOpcion no valida.\n");
                        break;
                }

                break;

            case 3:
                printf("\nLa opcion de modificar fichero todavia no esta implementada.\n");
                break;

            case 4:
                printf("Hasta pronto!\n");
                printf("-------------\n");
                break;

            default:
                printf("\nOpcion no valida.\n");
                break;
        }

    } while (opcion_listado != 4);

    return 0;
}


// FUNCIONES


int listado_opciones()
{
    int opcion_listado;

    printf("\n\n\n");
    printf("BIENVENIDO AL CENTRO DE GESTION DE DATOS DEPORTIVOS DE MADRID\n");
    printf("-------------------------------------------------------------\n");
    printf("Listado de opciones\n");
    printf("-------------------\n");
    printf("1. Lista de actividades\n");
    printf("2. Estadisticas\n");
    printf("3. Modificar el fichero\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");

    scanf("%d", &opcion_listado);

    while (opcion_listado < 1 || opcion_listado > 4)
    {
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion_listado);
    }

    return opcion_listado;
}


int Opcion_2_1()
{
    int opcion_estadisticas_1;

    printf("\nEstadisticas:\n");
    printf("1. Ocupacion media\n");
    printf("2. Horas pico segun actividad\n");
    printf("3. Actividad con mas demanda\n");
    printf("4. Actividad con menos demanda\n");
    printf("5. Centro con mayor oferta\n");
    printf("6. Eficiencia de los centros\n");
    printf("Seleccione una opcion: ");

    scanf("%d", &opcion_estadisticas_1);

    return opcion_estadisticas_1;
}


int Opcion_2_2()
{
    int opcion_estadisticas_2;

    printf("\nSeleccione el tipo de filtro:\n");
    printf("1. Filtrar por centro\n");
    printf("2. Filtrar por actividad\n");
    printf("Seleccione una opcion: ");

    scanf("%d", &opcion_estadisticas_2);

    return opcion_estadisticas_2;
}


Lista_Centros Listado_de_centros(Registro vector_informacion[], int total_lineas)
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


Lista_Actividades Listado_de_actividades(Registro vector_informacion[], int total_lineas)
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

        for (i = 0; i < 9; i++)
        {
            indice_real = i + 9 * (pag - 1);

            if (indice_real < Centros.num_centros)
            {
                printf("%d: %s\n", i + 1, Centros.centros[indice_real].centro);
            }
        }

        if (pag == pag_max)
        {
            printf("0: Todos los centros\n");
        }

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
                break;

            case 'a':
            case 'A':
                if (pag > 1)
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

                // Se resta 1 porque los vectores empiezan en 0.
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

            case '0':
                if (pag == pag_max)
                {
                    centro_seleccionado = -1;
                    bandera = 1;
                }
                else
                {
                    printf("La opcion 0 solo aparece en la ultima pagina.\n");
                }
                break;

            default:
                printf("La opcion seleccionada no es valida.\n");
                break;
        }
    }

    return centro_seleccionado;
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

        for (i = 0; i < 9; i++)
        {
            indice_real = i + 9 * (pag - 1);

            if (indice_real < Actividades.num_actividades)
            {
                printf("%d: %s\n", i + 1, Actividades.actividades[indice_real].actividad);
            }
        }

        if (pag == pag_max)
        {
            printf("0: Todas las actividades\n");
        }

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
                break;

            case 'a':
            case 'A':
                if (pag > 1)
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

                // Se resta 1 porque los vectores empiezan en 0.
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

            case '0':
                if (pag == pag_max)
                {
                    actividad_seleccionada = -1;
                    bandera = 1;
                }
                else
                {
                    printf("La opcion 0 solo aparece en la ultima pagina.\n");
                }
                break;

            default:
                printf("La opcion seleccionada no es valida.\n");
                break;
        }
    }

    return actividad_seleccionada;
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
            printf("Introduzca el annio de interes: ");
            scanf("%d", &resultado.anio);

            printf("Introduzca el mes de interes: ");
            scanf("%d", &resultado.mes);

            printf("Introduzca el dia de interes: ");
            scanf("%d", &resultado.dia);

            printf("Introduzca la hora minima. Formato HH:MM: ");
            scanf("%s", resultado.hora_min);

            printf("Introduzca la hora maxima. Formato HH:MM: ");
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


void Opcion_1(Registro vector_informacion[], int total_lineas)
{
    Lista_Centros Centros = Listado_de_centros(vector_informacion, total_lineas);
    int centro_filtrado = F_selector_centros(Centros);

    S_Fecha_Seleccionada fecha_filtrada = F_selector_horas();

    Lista_Actividades Actividades = Listado_de_actividades(vector_informacion, total_lineas);
    int actividad_filtrada = F_selector_actividades(Actividades);

    F_Imprimir_Filtrado(
        total_lineas,
        vector_informacion,
        Centros,
        Actividades,
        centro_filtrado,
        actividad_filtrada,
        fecha_filtrada
    );

    F_Imprimir_Filtrado_Fichero(
        total_lineas,
        vector_informacion,
        Centros,
        Actividades,
        centro_filtrado,
        actividad_filtrada,
        fecha_filtrada
    );
}


void Imprimir_registro_pantalla(Registro r)
{
    printf(
        "%d || %d || %d || %s || %s || %s || %s || %s || %s || %d || %d || %d || %s\n",
        r.fecha.anio,
        r.fecha.mes,
        r.fecha.dia,
        r.fecha.dia_semana,
        r.horario.hora_ini,
        r.horario.hora_fin,
        r.actividad.actividad_base,
        r.actividad.modalidad,
        r.actividad.centro,
        r.aforo.plazas,
        r.aforo.ocupadas,
        r.aforo.libres,
        r.actividad.tipo_uso
    );
}


void Imprimir_registro_fichero(FILE *fichero, Registro r)
{
    fprintf(
        fichero,
        "%d %d %d %s %s %s %s %s %s %d %d %d %s\n",
        r.fecha.anio,
        r.fecha.mes,
        r.fecha.dia,
        r.fecha.dia_semana,
        r.horario.hora_ini,
        r.horario.hora_fin,
        r.actividad.actividad_base,
        r.actividad.modalidad,
        r.actividad.centro,
        r.aforo.plazas,
        r.aforo.ocupadas,
        r.aforo.libres,
        r.actividad.tipo_uso
    );
}


int Cumple_filtros(
    Registro r,
    Lista_Centros Centros,
    Lista_Actividades Actividades,
    int centro_filtrado,
    int actividad_filtrada,
    S_Fecha_Seleccionada fecha_filtrada
)
{
    int cumple = 1;

    // Comprobacion del centro
    if (centro_filtrado != -1)
    {
        if (strcmp(r.actividad.centro, Centros.centros[centro_filtrado].centro) != 0)
        {
            cumple = 0;
        }
    }

    // Comprobacion de la actividad
    if (actividad_filtrada != -1)
    {
        if (strcmp(r.actividad.actividad_base, Actividades.actividades[actividad_filtrada].actividad) != 0)
        {
            cumple = 0;
        }
    }

    // Comprobacion de la fecha y de las horas
    if (fecha_filtrada.anio != -1)
    {
        if (
            r.fecha.anio != fecha_filtrada.anio ||
            r.fecha.mes != fecha_filtrada.mes ||
            r.fecha.dia != fecha_filtrada.dia
        )
        {
            cumple = 0;
        }
        else
        {
            if (
                strcmp(fecha_filtrada.hora_min, r.horario.hora_ini) > 0 ||
                strcmp(fecha_filtrada.hora_max, r.horario.hora_fin) < 0
            )
            {
                cumple = 0;
            }
        }
    }

    return cumple;
}


void F_Imprimir_Filtrado(
    int total_lineas,
    Registro vector_informacion[],
    Lista_Centros Centros,
    Lista_Actividades Actividades,
    int centro_filtrado,
    int actividad_filtrada,
    S_Fecha_Seleccionada fecha_filtrada
)
{
    int i;
    int contador = 0;
    char pedir_tecla;

    printf("\nPulse cualquier tecla para imprimir las actividades filtradas: ");
    scanf(" %c", &pedir_tecla);

    printf("\n");
    printf("anio || mes || dia || dia_semana || hora_inicio || hora_fin || actividad_base || modalidad || centro || plazas || ocupadas || libres || tipo_uso\n");

    for (i = 0; i < total_lineas; i++)
    {
        if (Cumple_filtros(vector_informacion[i], Centros, Actividades, centro_filtrado, actividad_filtrada, fecha_filtrada))
        {
            Imprimir_registro_pantalla(vector_informacion[i]);
            contador++;
        }
    }

    printf("\nTotal de registros encontrados: %d\n", contador);
}


void F_Imprimir_Filtrado_Fichero(
    int total_lineas,
    Registro vector_informacion[],
    Lista_Centros Centros,
    Lista_Actividades Actividades,
    int centro_filtrado,
    int actividad_filtrada,
    S_Fecha_Seleccionada fecha_filtrada
)
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

            fprintf(
                ARCHIVO_ESCRITURA_FILTRADO,
                "anio mes dia dia_semana hora_inicio hora_fin actividad_base modalidad centro plazas ocupadas libres tipo_uso\n"
            );

            for (i = 0; i < total_lineas; i++)
            {
                if (Cumple_filtros(vector_informacion[i], Centros, Actividades, centro_filtrado, actividad_filtrada, fecha_filtrada))
                {
                    Imprimir_registro_fichero(ARCHIVO_ESCRITURA_FILTRADO, vector_informacion[i]);
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


float Ocupacion_media_centros(Registro vector_informacion[], int total_lineas)
{
    Lista_Centros Centros = Listado_de_centros(vector_informacion, total_lineas);
    int centro_seleccionado = F_selector_centros(Centros);

    if (centro_seleccionado == -1)
    {
        return Ocupacion_media_todos_centros(vector_informacion, total_lineas);
    }
    else
    {
        return Ocupacion_media_centro_especifico(
            vector_informacion,
            total_lineas,
            Centros.centros[centro_seleccionado].centro
        );
    }
}


float Ocupacion_media_todos_centros(Registro vector_informacion[], int total_lineas)
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


float Ocupacion_media_centro_especifico(Registro vector_informacion[], int total_lineas, char centro[])
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


float Ocupacion_media_actividades(Registro vector_informacion[], int total_lineas)
{
    Lista_Actividades Actividades = Listado_de_actividades(vector_informacion, total_lineas);
    int actividad_seleccionada = F_selector_actividades(Actividades);

    if (actividad_seleccionada == -1)
    {
        return Ocupacion_media_todas_actividades(vector_informacion, total_lineas);
    }
    else
    {
        return Ocupacion_media_actividad_especifica(
            vector_informacion,
            total_lineas,
            Actividades.actividades[actividad_seleccionada].actividad
        );
    }
}


float Ocupacion_media_todas_actividades(Registro vector_informacion[], int total_lineas)
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


float Ocupacion_media_actividad_especifica(Registro vector_informacion[], int total_lineas, char actividad[])
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


void Actividad_con_mas_demanda(Registro v[], int n)
{
    Lista_Actividades LA = Listado_de_actividades(v, n);

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
        ocupacion_porcentual = Ocupacion_media_actividad_especifica(v, n, LA.actividades[i].actividad);

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

    printf("\nActividad con mayor demanda porcentual: %s (%.2f%%)\n",
           actividad_max_porcentual,
           max_ocupacion_porcentual);

    printf("Actividad con mayor demanda absoluta: %s (%d plazas ocupadas)\n",
           actividad_max_absoluta,
           max_ocupacion_absoluta);
}


void Actividad_con_menos_demanda(Registro v[], int n)
{
    Lista_Actividades LA = Listado_de_actividades(v, n);

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
        ocupacion_porcentual = Ocupacion_media_actividad_especifica(v, n, LA.actividades[i].actividad);

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

    printf("\nActividad con menor demanda porcentual: %s (%.2f%%)\n",
           actividad_min_porcentual,
           min_ocupacion_porcentual);

    printf("Actividad con menor demanda absoluta: %s (%d plazas ocupadas)\n",
           actividad_min_absoluta,
           min_ocupacion_absoluta);
}


void Centro_con_mayor_oferta(Registro v[], int n)
{
    Lista_Centros LC = Listado_de_centros(v, n);

    int i, j;
    int max_plazas = -1;
    char centro_max[50] = "";

    for (i = 0; i < LC.num_centros; i++)
    {
        int plazas = 0;

        for (j = 0; j < n; j++)
        {
            if (strcmp(v[j].actividad.centro, LC.centros[i].centro) == 0)
            {
                plazas += v[j].aforo.plazas;
            }
        }

        if (plazas > max_plazas)
        {
            max_plazas = plazas;
            strcpy(centro_max, LC.centros[i].centro);
        }
    }

    printf("\nCentro con mayor oferta: %s (%d plazas totales)\n", centro_max, max_plazas);
}


void Eficiencia_centros(Registro v[], int n)
{
    Lista_Centros LC = Listado_de_centros(v, n);
    int i;

    printf("\nEficiencia de los centros:\n");

    for (i = 0; i < LC.num_centros; i++)
    {
        float ocupacion = Ocupacion_media_centro_especifico(v, n, LC.centros[i].centro);
        printf("- %s: %.2f%%\n", LC.centros[i].centro, ocupacion);
    }
}


void Horas_pico_actividad(Registro v[], int n)
{
    Lista_Actividades LA = Listado_de_actividades(v, n);
    int act = F_selector_actividades(LA);

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
        printf("\nHora pico de %s: %02d:00 (media %.2f personas)\n",
               actividad,
               mejor_hora,
               mejor_media);
    }
    else
    {
        printf("\nNo hay datos para la actividad %s\n", actividad);
    }
}
