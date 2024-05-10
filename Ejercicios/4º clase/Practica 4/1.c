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
void mostrarPeliculas(Pelicula *peliculas, int cantidad);
void guardarPeliculas(Pelicula *peliculas, int cantidad);

int main(){
    Pelicula peliculas[5];
    cargarPeliculas(peliculas, 5);
    guardarPeliculas(peliculas, 5);
    mostrarPeliculas(peliculas, 5);
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

void mostrarPeliculas(Pelicula *peliculas, int cantidad){
    FILE *archivo = fopen("peliculas.dat", "rb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    for(int i = 0; i < cantidad; i++){
        fread(&peliculas[i], sizeof(Pelicula), 1, archivo);
        printf("Pelicula %d\n", i+1);
        printf("Nombre: %s\n", peliculas[i].nombre);
        printf("Genero: %s\n", peliculas[i].genero);
        printf("Anio de estreno: %d\n", peliculas[i].anio);
        printf("Calificacion: %.2f\n", peliculas[i].calificacion);
    }
    fclose(archivo);
}

void guardarPeliculas(Pelicula *peliculas, int cantidad){
    FILE *archivo = fopen("peliculas.dat", "wb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    for(int i = 0; i < cantidad; i++){
        fwrite(&peliculas[i], sizeof(Pelicula), 1, archivo);
    }
    fclose(archivo);
}

