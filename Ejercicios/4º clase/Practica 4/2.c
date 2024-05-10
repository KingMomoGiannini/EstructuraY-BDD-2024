/*2) Los siguientes ejercicios utilizarán el archivo peliculas.dat generado en el ejercicio anterior
a)	Mostrar la información completa de las últimas tres películas.
b)	Dada la posición de una película y un número N, mostrar las N películas siguientes a ella.
c)	Dado un año de estreno, informar cuántas películas se estrenaron en tal año o posteriormente.
d)	Dado un género, informar el promedio de calificación de las películas de tal género.
e)	Colocar el nombre de todas las películas en mayúsculas, dejando el archivo modificado.
f)	Generar un archivo top3Pelis.dat con solo nombre y calificación de las 3 mejores películas.
g)	Dado un género, generar un archivo pelisDeGenero.dat (donde Genero se reemplaza por el dado) que contenga 
    solo nombre y calificación de las películas que corresponda al género dado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

typedef struct{
    char nombre[50];
    int anio;
    char genero[20];
    float calificacion;
}Pelicula;

int CANT_PELICULAS = 5;

//prototipos
void mostrarPeliculas(Pelicula *peliculas, int cantidad);
void mostrarNPeliculasSiguientes(Pelicula *peliculas, int cantidad, int posicion, int n);
int cantidadPeliculasEstrenadas(Pelicula *peliculas, int cantidad, int anio);
float promedioCalificacionGenero(Pelicula *peliculas, int cantidad, char *genero);
void pasarAMayusculas(Pelicula *peliculas, int cantidad);
void generarTop3Pelis(Pelicula *peliculas, int cantidad);
void generarPelisDeGenero(Pelicula *peliculas, int cantidad, char *genero);
void leerArchivo(FILE *archivo);

int main(){
    FILE *archivo;
    Pelicula peliculas[10];

    archivo = fopen("peliculas.dat", "rb");
    if(archivo != NULL){
        for (int i = 0; i < CANT_PELICULAS; i++)
        {
            fread(&peliculas[i], sizeof(Pelicula), 1, archivo);
        }
        mostrarPeliculas(peliculas, CANT_PELICULAS);
        mostrarNPeliculasSiguientes(peliculas, CANT_PELICULAS, 2, 3);
        printf("Cantidad de peliculas estrenadas en 2010 o posterior: %d\n", cantidadPeliculasEstrenadas(peliculas, CANT_PELICULAS, 2010));
        printf("Promedio de calificacion de peliculas de genero comedia: %.2f\n", promedioCalificacionGenero(peliculas, CANT_PELICULAS, "comedia"));
        pasarAMayusculas(peliculas, CANT_PELICULAS);
        generarTop3Pelis(peliculas, CANT_PELICULAS);
        generarPelisDeGenero(peliculas, CANT_PELICULAS, "comedia");
        fclose(archivo);
    }
    else{
        printf("Error al abrir el archivo\n");
    }
    
    return 0;
}

void mostrarPeliculas(Pelicula *peliculas, int cantidad){
    for(int i = cantidad - 3; i < cantidad; i++){
        printf("Nombre: %s\n", peliculas[i].nombre);
        printf("Anio: %d\n", peliculas[i].anio);
        printf("Genero: %s\n", peliculas[i].genero);
        printf("Calificacion: %.2f\n", peliculas[i].calificacion);
        printf("\n");
    }
}

void mostrarNPeliculasSiguientes(Pelicula *peliculas, int cantidad, int posicion, int n){
    for(int i = posicion; i < posicion + n; i++){
        printf("Nombre: %s\n", peliculas[i].nombre);
        printf("Anio: %d\n", peliculas[i].anio);
        printf("Genero: %s\n", peliculas[i].genero);
        printf("Calificacion: %.2f\n", peliculas[i].calificacion);
        printf("\n");
    }
}

int cantidadPeliculasEstrenadas(Pelicula *peliculas, int cantidad, int anio){
    int cantidadPeliculas = 0;
    for(int i = 0; i < cantidad; i++){
        if(peliculas[i].anio >= anio){
            cantidadPeliculas++;
        }
    }
    return cantidadPeliculas;
}

float promedioCalificacionGenero(Pelicula *peliculas, int cantidad, char *genero){
    float sumaCalificaciones = 0;
    int cantidadPeliculas = 0;
    for(int i = 0; i < cantidad; i++){
        if(strcmp(peliculas[i].genero, genero) == 0){
            sumaCalificaciones += peliculas[i].calificacion;
            cantidadPeliculas++;
        }
    }
    return sumaCalificaciones / cantidadPeliculas;
}

void pasarAMayusculas(Pelicula *peliculas, int cantidad){
    FILE *archivo;
    archivo = fopen("peliculasMayusculas.dat", "wb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    for(int i = 0; i < cantidad; i++){
        for(int j = 0; j < strlen(peliculas[i].nombre); j++){
            peliculas[i].nombre[j] = toupper(peliculas[i].nombre[j]);
        }
    }

    fwrite(peliculas, sizeof(Pelicula), cantidad, archivo);

    fclose(archivo);
}

void generarTop3Pelis(Pelicula *peliculas, int cantidad){
    FILE *archivo;
    Pelicula top3[3];
    int posicion = 0;

    for(int i = 0; i < 3; i++){
        top3[i] = peliculas[0];
        for(int j = 0; j < cantidad; j++){
            if(peliculas[j].calificacion > top3[i].calificacion){
                top3[i] = peliculas[j];
                posicion = j;
            }
        }
        peliculas[posicion].calificacion = -1;
    }

    archivo = fopen("top3Pelis.dat", "wb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    fwrite(top3, sizeof(Pelicula), 3, archivo);

    fclose(archivo);
}

void generarPelisDeGenero(Pelicula *peliculas, int cantidad, char *genero){
    FILE *archivo;
    Pelicula pelisDeGenero[10];
    int cantidadPelisDeGenero = 0;

    for(int i = 0; i < cantidad; i++){
        if(strcmp(peliculas[i].genero, genero) == 0){
            pelisDeGenero[cantidadPelisDeGenero] = peliculas[i];
            cantidadPelisDeGenero++;
        }
    }

    archivo = fopen("pelisDeGenero.dat", "wb");
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    fwrite(pelisDeGenero, sizeof(Pelicula), cantidadPelisDeGenero, archivo);

    fclose(archivo);
}