/*Introducción
Con el fin de poder reproducir el desarrollo de una carrera de Fórmula 1, la FIA lo
contrata para desarrollar una aplicación que sea capaz de procesar información de los
corredores durante la carrera y poder calcular estadísticas on-demand del operador.
Lo que se pide es una aplicación en C que sea capaz de leer información de archivos y
calcular lo que el operador de estadísticas requiera según los datos leídos.

La aplicación cuenta con los siguientes archivos:
- config.txt: este archivo contiene la configuración del programa, el cual contiene:
o Nombre de la aplicación: cadena de 15 caracteres.
o Nombre del circuito: cadena de 15 caracteres.
o Número de versión: una cadena de 5 caracteres (ej., 1.0).
- corredores.dat: este archivo contiene datos de los corredores de F1 en formato binario,
cuya estructura es la siguiente:
o Número de corredor: dato entero.
o Nombre: cadena de 15 caracteres.
o Apellido: cadena de 15 caracteres.
o escudería: cadena de 15 caracteres.
- tiempos.dat: este archivo contiene los tiempos de vuelta de cada corredor en formato
binario, cuya estructura es la siguiente:
o Número de vuelta: dato entero.
o Número de corredor: dato entero.
o Tiempo: formato decimal de 3 dígitos de precisión.
Funcionalidades
La aplicación debe poder mostrar un menú de opciones. El menú de opciones debe
mostrar siempre el nombre de la aplicación, el circuito y la versión. Las opciones por
implementar son las siguientes opciones:
1- Mostrar los corredores
2- Mostrar los tiempos de carrera*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct{
    char nombreAplicacion[15];
    char nombreCircuito[15];
    char numeroVersion[5];
}Configuracion;

void mostrarCorredores(FILE *archivoCorredores);
void mostrarTiempos(FILE *archivoTiempos);

int main(){
    Configuracion configuracion;
    FILE *archivoCorredores;
    FILE *archivoConfig;
    FILE *archivoTiempos;
    archivoConfig = fopen("../config.txt", "r");
    if(archivoConfig != NULL){
        fgets(configuracion.nombreAplicacion, 15, archivoConfig);
        fgets(configuracion.nombreCircuito, 15, archivoConfig);
        fgets(configuracion.numeroVersion, 5, archivoConfig);
        fclose(archivoConfig);
    }
    else{
        printf("Error al abrir el archivo de configuracion\n");    
    }

    int opcion;
    do{
        printf("Nombre de la aplicacion: %s", configuracion.nombreAplicacion);
        printf("Nombre del circuito: %s", configuracion.nombreCircuito);
        printf("Numero de version: %s\n", configuracion.numeroVersion);
        printf("\t1- Mostrar los corredores\n");
        printf("\t2- Mostrar los tiempos de carrera\n");
        printf("\t3- Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                archivoCorredores = fopen("../corredores.dat", "rb");
                if (archivoCorredores != NULL){
                    mostrarCorredores(archivoCorredores);
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
                break;
            default:
                printf("Opcion invalida\n");
        }
    }while(opcion != 3);
    
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
