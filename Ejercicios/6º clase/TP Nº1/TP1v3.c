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
2- Mostrar los tiempos de carrera

<Agregar - Opcion 3: Salir y opcion 4: cambiar el nombre de una escudería dentro del archivo de corredores.dat> 
Agregar- Opcion 6: Mostrar el tiempo final(tiempos sumados de cada vuelta) de cada corredor (sin contar la vuelta 0) de menor a mayor por consola.
Agregar- Opcion 7: En un archivo podio.txt mostrar el podio: nombre, apellido, y el tiempo de cada uno.
*/

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

void mostrarCorredores(FILE *archivoCorredores);
void mostrarCorredoresEnEstructura(Corredor corredores[], int cantidadCorredores);
void mostrarTiempos(FILE *archivoTiempos);
void cambiarNombreEscuderia(FILE *archivoCorredores, char escuderia[], char nuevaEscuderia[]);
void cambiarEscuderiaCorredor(FILE *archivoCorredores, int numeroCorredor, char nuevaEscuderia[]);
void mostrarConfiguracion(FILE *archivoConfig);
//funcion para listar corredores
void listarCorredores(FILE *archivoCorredores, Corredor corredores[], int cantidadCorredores);
//funcion para mostrar el tiempo final de cada corredor
void mostrarTiempoFinal(FILE *archivoTiempos, Corredor corredores[], int cantidadCorredores);
//funcion para mostrar el podio
void mostrarPodio(FILE *archivoTiempos, Corredor corredores[], int cantidadCorredores);

int main(){
    FILE *archivoCorredores;
    FILE *archivoConfig;
    FILE *archivoTiempos;
    Corredor corredores[100];
    int cantidadCorredores = 0;
    int opcion;
    archivoCorredores = fopen("../corredores.dat", "rb");
    if (archivoCorredores != NULL)
    {
        listarCorredores(archivoCorredores, corredores, cantidadCorredores);
        mostrarCorredoresEnEstructura(corredores, cantidadCorredores);
        fclose(archivoCorredores);
    }
    else
    {
        printf("Error al abrir el archivo de corredores\n");
    }
    do{
        mostrarConfiguracion(archivoConfig);
        printf("\t1- Mostrar los corredores\n");
        printf("\t2- Mostrar los tiempos de carrera\n");
        printf("\t3- Salir\n");
        printf("\t4- Cambiar el nombre de la escuderia\n");
        printf("\t5- Cambiar el nombre de la escuderia de un conductor\n");
        printf("\t6- Mostrar el tiempo final de cada corredor\n");
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
            case 4:
                archivoCorredores = fopen("../corredores.dat", "rb+");
                if(archivoCorredores != NULL){
                    char laEscuderia[15];
                    char nuevaEscuderia[15];
                    printf("Ingrese la escuderia: ");
                    fflush(stdin);
                    scanf("%s", laEscuderia);
                    strcat(laEscuderia, "\n");
                    printf("Ingrese la nueva escuderia: ");
                    fflush(stdin);
                    scanf("%s", nuevaEscuderia);
                    strcat(nuevaEscuderia, "\n");
                    cambiarNombreEscuderia(archivoCorredores, laEscuderia, nuevaEscuderia);
                    fclose(archivoCorredores);
                }
                else{
                    printf("Error al abrir el archivo de corredores\n");
                }
                break;
            case 5:
                archivoCorredores = fopen("../corredores.dat", "rb+");
                if(archivoCorredores != NULL){
                    Corredor corredor;
                    char nuevaEscuderia[15];
                    printf("Ingrese el numero de corredor: ");
                    scanf("%d", &corredor.numeroCorredor);
                    printf("Ingrese la nueva escuderia: ");
                    fflush(stdin);
                    scanf("%s", nuevaEscuderia);
                    //gets(nuevaEscuderia);
                    cambiarEscuderiaCorredor(archivoCorredores, corredor.numeroCorredor, nuevaEscuderia);
                    fclose(archivoCorredores);
                }
                else{
                    printf("Error al abrir el archivo de corredores\n");
                }
                break;
            case 6:
                archivoTiempos = fopen("../tiempos2.dat", "rb");
                if (archivoTiempos != NULL){
                    mostrarTiempoFinal(archivoTiempos, corredores, cantidadCorredores);
                    fclose(archivoTiempos);
                }
                else{
                    printf("Error al abrir el archivo de tiempos\n");
                }
                break;
            
            default:
                printf("Opcion invalida\n");
        }
    }while(opcion != 3);
    
    return 0;
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

void cambiarNombreEscuderia(FILE *archivoCorredores, char escuderia[], char nuevaEscuderia[]){
    Corredor corredor;
    if(archivoCorredores != NULL){
        while(fread(&corredor, sizeof(Corredor), 1, archivoCorredores)){
            
            if(strcmp(corredor.escuderia, escuderia) == 0){
                fseek(archivoCorredores, -sizeof(Corredor), SEEK_CUR);
                strcpy(corredor.escuderia, nuevaEscuderia);
                printf("Escuderia a cambiar %s\n", corredor.escuderia);
                fwrite(&corredor, sizeof(Corredor), 1, archivoCorredores);
                fseek(archivoCorredores, 0, SEEK_CUR);
            }
        }
    }
    else{
        printf("Error al abrir el archivo de corredores\n");
    }
}

void cambiarEscuderiaCorredor(FILE *archivoCorredores, int numeroCorredor, char nuevaEscuderia[]){//funciona!!
    Corredor corredor;
    if(archivoCorredores != NULL){
        while(fread(&corredor, sizeof(Corredor), 1, archivoCorredores)){
            
            if(corredor.numeroCorredor == numeroCorredor){
                fseek(archivoCorredores, -sizeof(Corredor), SEEK_CUR);
                strcpy(corredor.escuderia, nuevaEscuderia);
                fwrite(&corredor, sizeof(Corredor), 1, archivoCorredores);
                fseek(archivoCorredores, 0, SEEK_CUR);
            }
        }
    }
    else{
        printf("Error al abrir el archivo de corredores\n");
    }
}

void listarCorredores(FILE *archivoCorredores, Corredor corredores[], int cantidadCorredores){
    Corredor corredor;
    if(archivoCorredores != NULL){
        while(fread(&corredor, sizeof(Corredor), 1, archivoCorredores)){
            corredores[cantidadCorredores] = corredor;
            cantidadCorredores++;
        }
    }
    else{
        printf("Error al abrir el archivo de corredores\n");
    }
}

void mostrarTiempoFinal(FILE *archivoTiempos, Corredor corredores[], int cantidadCorredores){
    Tiempo tiempo;
    float tiempoFinal = 0;
    float tiemposFinales[100];
    int i = 0;
    if(archivoTiempos != NULL){
        while(fread(&tiempo, sizeof(Tiempo), 1, archivoTiempos)){
            if(tiempo.numeroVuelta != 0){
                tiempoFinal += tiempo.tiempo;
            }
            else{
                tiemposFinales[i] = tiempoFinal;
                tiempoFinal = 0;
                i++;
            }
        }
        for(int j = 0; j < cantidadCorredores; j++){
            printf("Corredor: %s %s, tiempo final: %.3f\n", corredores[j].nombre, corredores[j].apellido, tiemposFinales[j]);
        }
    }
    else{
        printf("Error al abrir el archivo de tiempos\n");
    }
}

void mostrarPodio(FILE *archivoTiempos, Corredor corredores[], int cantidadCorredores){
    Tiempo tiempo;
    float tiempoFinal = 0;
    float tiemposFinales[100];
    int i = 0;
    if(archivoTiempos != NULL){
        while(fread(&tiempo, sizeof(Tiempo), 1, archivoTiempos)){
            if(tiempo.numeroVuelta != 0){
                tiempoFinal += tiempo.tiempo;
            }
            else{
                tiemposFinales[i] = tiempoFinal;
                tiempoFinal = 0;
                i++;
            }
        }
        for(int j = 0; j < cantidadCorredores; j++){
            printf("Corredor: %s %s, tiempo final: %.3f\n", corredores[j].nombre, corredores[j].apellido, tiemposFinales[j]);
        }
    }
    else{
        printf("Error al abrir el archivo de tiempos\n");
    }
}