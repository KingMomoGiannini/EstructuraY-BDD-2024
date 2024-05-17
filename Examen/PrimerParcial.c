#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VUELTAS_MAX 500
#define CORREDORES_MAX 20

typedef struct{
    int numeroCorredor;
    char nombre[15];
    char apellido[15];
    char escuderia[15];
}Corredor;

typedef struct{
    int numeroVuelta;
    int numeroCorredor;
    float tiempo;
}Tiempo;

typedef struct
{
    Corredor elCorredor;
    Tiempo tiempo[VUELTAS_MAX];
    float tiempoTotal;
} GrillaFinal;

void mostrarCorredores(FILE *archivoCorredores);
void listarCorredores(FILE *archivoCorredores, Corredor corredores[], int *cantCorredores);
void mostrarTiempos(FILE *archivoTiempos);
void listarTiempos(FILE *archivoTiempos, Tiempo tiempos[], int *cantTiempos);
void mostrarConfiguracion(FILE *archivoConfig);
void ordenarTiemposPorNumeroCorredor(Tiempo tiempos[], int cantTiempos, GrillaFinal estadisticasCorredor[]);
void ordenarCorredoresPorNumeroCorredor(Corredor corredores[], int cantCorredores, GrillaFinal estadisticasCorredor[]);
void sumarTiemposCorredor(Tiempo tiempos[], int cantTiempos, GrillaFinal estadisticasCorredor[]);
void generarArchivoPodio(GrillaFinal estadisticasCorredor[]);
void ordenarCorredoresPorTiempo(int cantCorredores, GrillaFinal estadisticasCorredor[]);

int main(){
    FILE *archivoCorredores;
    FILE *archivoConfig;
    FILE *archivoTiempos;
    int cantidadCorredores = 0;
    int cantTiempos = 0;
    Corredor corredores[CORREDORES_MAX];
    Tiempo tiempos[VUELTAS_MAX];
    GrillaFinal resultadosCorredor[CORREDORES_MAX];
    int opcion;
    archivoCorredores = fopen("../corredores.dat", "rb");
    archivoTiempos = fopen("../tiempos2.dat", "rb");

    if (archivoCorredores != NULL && archivoTiempos != NULL)
    {
        listarCorredores(archivoCorredores,corredores,&cantidadCorredores);
        listarTiempos(archivoTiempos,tiempos,&cantTiempos);
        ordenarCorredoresPorNumeroCorredor(corredores, cantidadCorredores, resultadosCorredor);
        ordenarTiemposPorNumeroCorredor(tiempos, cantTiempos, resultadosCorredor);
        fclose(archivoCorredores);
        fclose(archivoTiempos);
        printf("OK\n");
    }
    else{
        printf("\nNo se pudo abrir el archivo de corredores o de tiempos.");
    }

    do{
        mostrarConfiguracion(archivoConfig);
        printf("\t1- Mostrar los corredores\n");
        printf("\t2- Mostrar los tiempos de carrera\n");
        printf("\t3- Final de carrera\n");
        printf("\t4- Imprimir podio\n");
        printf("\t5- Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                archivoCorredores = fopen("../corredores.dat", "rb");
                if (archivoCorredores != NULL){
                    mostrarCorredores(archivoCorredores);                    
                    printf ("\nCantidad de corredores: %d\n",cantidadCorredores);
                    fclose(archivoCorredores);
                }
                else{
                    printf("Error al abrir el archivo de corredores\n");
                }
                break;
            case 2:
                archivoTiempos = fopen("../tiempos2.dat", "rb");
                if (archivoTiempos != NULL){
                    mostrarTiempos(archivoTiempos);
                    fclose(archivoTiempos);
                }
                else{
                    printf("Error al abrir el archivo de tiempos\n");
                }
                break;
            case 3:
                for (int i = 0; i < cantidadCorredores; i++){
                    printf("Numero de corredor: %d,\t", resultadosCorredor[i].elCorredor.numeroCorredor);
                    printf("Nombre: %s,\t", resultadosCorredor[i].elCorredor.nombre);
                    printf("Apellido: %s,\t", resultadosCorredor[i].elCorredor.apellido);
                    printf("Tiempo total: %.3f\n", resultadosCorredor[i].tiempoTotal);
                }
                break;
            case 4:
                ordenarCorredoresPorTiempo(cantidadCorredores, resultadosCorredor);
                generarArchivoPodio(resultadosCorredor);
                break;
            case 5:
                break;
            default:
                printf("Opcion invalida\n");
        }
    }while(opcion != 5);
    
    return 0;
}

void mostrarCorredores(FILE *archivoCorredores){
    Corredor corredor;
    if(archivoCorredores != NULL){
        while(fread(&corredor, sizeof(Corredor), 1, archivoCorredores)){
            printf("Numero de corredor:%d\t", corredor.numeroCorredor);
            printf("Nombre: %s\t", corredor.nombre);
            printf("Apellido: %s\t", corredor.apellido);
            printf("Escuderia: %s\t", corredor.escuderia);
            printf("\n");
        }
    }
    else{
        printf("Error al abrir el archivo de corredores\n");
    }
}

void mostrarTiempos(FILE *archivoTiempos){
    Tiempo tiempo;
    if(archivoTiempos != NULL){
        while(fread(&tiempo, sizeof(Tiempo), 1, archivoTiempos)){
            printf("Numero de vuelta: %d,\t", tiempo.numeroVuelta);
            printf("Numero de corredor: %d,\t", tiempo.numeroCorredor);
            printf("Tiempo: %.3f\n", tiempo.tiempo);
        }
    }
    else{
        printf("Error al abrir el archivo de tiempos\n");
    }
}

void mostrarConfiguracion(FILE *archivoConfig){
    archivoConfig = fopen("../config.txt", "r");
    if(archivoConfig != NULL){
        char config[15];
        printf("------------------\n");
        while(fgets(config, 15, archivoConfig)){
            printf("%s", config);
        }
        printf("------------------\n");
        fclose(archivoConfig);
    }
    else{
        printf("Error al abrir el archivo de configuracion\n");
    }
}

void listarCorredores(FILE *archivoCorredores, Corredor corredores[], int *cantCorredores){
    Corredor elCorredorf;
    int i = 0;
    while(fread(&elCorredorf, sizeof(Corredor),1,archivoCorredores)){
        corredores[i] = elCorredorf;
        i++;
    }
    (*cantCorredores) = i;
}

void listarTiempos(FILE *archivoTiempos, Tiempo tiempos[], int *cantTiempos){
    Tiempo elTiempof;
    int i = 0;
    while(fread(&elTiempof, sizeof(Tiempo),1,archivoTiempos)){
        tiempos[i] = elTiempof;
        i++;
    }
    (*cantTiempos) = i;
}

void ordenarCorredoresPorNumeroCorredor(Corredor corredores[], int cantCorredores, GrillaFinal resultadosCorredor[]){
    for (int i = 0; i < cantCorredores; i++){
        for (int j = 0; j < cantCorredores - 1; j++){
            if (corredores[j].numeroCorredor > corredores[j + 1].numeroCorredor){
                Corredor corredorAuxiliar;
                corredorAuxiliar = corredores[j];
                corredores[j] = corredores[j + 1];
                corredores[j + 1] = corredorAuxiliar;
            }
        }
    }
    for (int i = 0; i < cantCorredores; i++){
        resultadosCorredor[i].elCorredor = corredores[i];
    }
}

void ordenarTiemposPorNumeroCorredor(Tiempo tiempos[], int cantTiempos, GrillaFinal resultadosCorredor[]){
    for (int i = 0; i < cantTiempos; i++){
        for (int j = 0; j < cantTiempos - 1; j++){
            if (tiempos[j].numeroCorredor > tiempos[j + 1].numeroCorredor){
                Tiempo tiempoAuxiliar;
                tiempoAuxiliar = tiempos[j];
                tiempos[j] = tiempos[j + 1];
                tiempos[j + 1] = tiempoAuxiliar;
            }
        }
    }
    sumarTiemposCorredor(tiempos, cantTiempos, resultadosCorredor);
}

void sumarTiemposCorredor(Tiempo tiempos[], int cantTiempos, GrillaFinal resultadosCorredor[]){
    int i = 0;
    int j = 0;
    float tiempoTotal = 0;
    for (i = 0; i < cantTiempos; i++){
        if ((tiempos[i].numeroCorredor == resultadosCorredor[j].elCorredor.numeroCorredor)){
            tiempoTotal += tiempos[i].tiempo;
        }
        else{
            resultadosCorredor[j].tiempoTotal = tiempoTotal;
            tiempoTotal = 0;
            j++;
        }
    }
    resultadosCorredor[j].tiempoTotal = tiempoTotal;
}

void generarArchivoPodio(GrillaFinal resultadosCorredor[]){
    FILE *archivoPodio;
    archivoPodio = fopen("../podio.txt", "w");
    if (archivoPodio != NULL){
        fprintf(archivoPodio, "Podio de %s\n", "nombre de circuito");
        fprintf(archivoPodio, "1ro %s %s (%d - %.3f)\n", resultadosCorredor[0].elCorredor.apellido, resultadosCorredor[0].elCorredor.nombre, resultadosCorredor[0].elCorredor.numeroCorredor, resultadosCorredor[0].tiempoTotal);
        fprintf(archivoPodio, "2do %s %s (%d - %.3f)\n", resultadosCorredor[1].elCorredor.apellido, resultadosCorredor[1].elCorredor.nombre, resultadosCorredor[1].elCorredor.numeroCorredor, resultadosCorredor[1].tiempoTotal);
        fprintf(archivoPodio, "3ro %s %s (%d - %.3f)\n", resultadosCorredor[2].elCorredor.apellido, resultadosCorredor[2].elCorredor.nombre, resultadosCorredor[2].elCorredor.numeroCorredor, resultadosCorredor[2].tiempoTotal);
        fclose(archivoPodio);
    }
    else{
        printf("Error al abrir el archivo de podio\n");
    }
    archivoPodio = fopen("../podio.txt", "r");
    if (archivoPodio != NULL){
        char podio[50];
        while(fgets(podio, 50, archivoPodio)){
            printf("%s", podio);
        }
        fclose(archivoPodio);
    }
    else{
        printf("Error al abrir el archivo de podio\n");
    }
}

void ordenarCorredoresPorTiempo(int cantCorredores, GrillaFinal resultadosCorredor[]){
    for (int i = 0; i < cantCorredores; i++){
        for (int j = 0; j < cantCorredores - 1; j++){
            if (resultadosCorredor[j].tiempoTotal > resultadosCorredor[j + 1].tiempoTotal){
                GrillaFinal corredorAuxiliar;
                corredorAuxiliar = resultadosCorredor[j];
                resultadosCorredor[j] = resultadosCorredor[j + 1];
                resultadosCorredor[j + 1] = corredorAuxiliar;
            }
        }
    }
}