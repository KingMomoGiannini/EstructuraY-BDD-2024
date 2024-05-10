/*1) Realiza un programa que permita generar un archivo binario llamado peliculas.dat, el cual cuente con al menos 5 registros de tus películas 
favoritas. De cada una se espera la siguiente info: 
▪ Nombre
▪ Género
▪ Año de estreno
▪ Calificación en el sitio IMBD
Luego de generado, abrirlo y mostrarlo por consola, chequeando que esté todo correcto.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nombre[50];
    char genero[50];
    int anio;
    float calificacion;
}Pelicula;

void cargarPeliculas(Pelicula *peliculas, int cantidad);
void mostrarPeliculas(FILE *archivoPeliculas, Pelicula *peliculas, int cantidad);
void guardarPeliculas(FILE *archivoPeliculas, Pelicula *peliculas, int cantidad);

int main(){
    int opcion;
    Pelicula peliculas[5];
    FILE *archivoPeliculas;
    while(opcion != 3){
        printf("\t1- Cargar peliculas\n");
        printf("\t2- Mostrar peliculas\n");
        printf("\t3- Salir\n");
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            archivoPeliculas = fopen("peliculas.dat", "wb");
            if (archivoPeliculas != NULL){
                cargarPeliculas(peliculas, 5);
                guardarPeliculas(archivoPeliculas,peliculas, 5);
                fclose(archivoPeliculas);
            }
            else{
                printf("Error al abrir el archivo\n");
            }
            break;
        case 2: 
            archivoPeliculas = fopen("peliculas.dat", "rb");
            if(archivoPeliculas != NULL){
                mostrarPeliculas(archivoPeliculas, peliculas, 5);
                fclose(archivoPeliculas);
            }
            else{
                printf("Error al abrir el archivo para lectura\n");
            }
            break;
        case 3:
            break;
        default:
            printf("Opcion incorrecta\n");
            break;
        }
    }
    return 0;
}

void cargarPeliculas(Pelicula *peliculas, int cantidad){
    for(int i = 0; i < cantidad; i++){
        printf("Ingrese el nombre de la pelicula %d: ", i+1);
        fflush(stdin);
        gets(peliculas[i].nombre);
        printf("Ingrese el genero de la pelicula %d: ", i+1);
        fflush(stdin);
        gets(peliculas[i].genero);
        printf("Ingrese el anio de estreno de la pelicula %d: ", i+1);
        scanf("%d", &peliculas[i].anio);
        printf("Ingrese la calificacion de la pelicula %d: ", i+1);
        scanf("%f", &peliculas[i].calificacion);
    }
}

void mostrarPeliculas(FILE *archivoPeliculas, Pelicula *peliculas, int cantidad){
    if(archivoPeliculas != NULL){
        for(int i = 0; i < cantidad; i++){
            fread(&peliculas[i], sizeof(Pelicula), 1, archivoPeliculas);
            printf("Pelicula %d\n", i+1);
            printf("Nombre: %s\n", peliculas[i].nombre);
            printf("Genero: %s\n", peliculas[i].genero);
            printf("Anio de estreno: %d\n", peliculas[i].anio);
            printf("Calificacion: %.2f\n", peliculas[i].calificacion);
            printf("------------------------\n");
        }
    }
    else{
        printf("Error al abrir el archivo\n");
    }
}

void guardarPeliculas(FILE *archivoPeliculas, Pelicula *peliculas, int cantidad){
    if(archivoPeliculas != NULL){
        for(int i = 0; i < cantidad; i++){
            fwrite(&peliculas[i], sizeof(Pelicula), 1, archivoPeliculas);
        }
    }
    else{
        printf("Error al abrir el archivo\n");
    }
}

