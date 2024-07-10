
/*Transformar un vector real en un vector dinamico con funciones. 
int *crearVector(int *, int );
void cargaVector(int[], int, int);
void mostrarVector(int[], int, char *);
Luego generar un vector dinamico con los numeros primos que posea el vector dinamico antes creado a traves
de la funcion, utilizar realloc para expandir memoria:
int *vectorPrimos(int *, int, int *) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *crearVector(int *, int );
void cargaVector(int[], int, int);
void mostrarVector(int[], int, char *);
int *realocarVector(int *, int);

int main() {
    int *vec = NULL;
    int n = 15; // este va a ser el tamaño inicial del vector, despues le asigno otro
    int max = 100; // creo un valor máximo para los elementos del vector

    vec = crearVector(vec, n);
    if (vec == NULL) {
        return 1;
    }

    cargaVector(vec, n, max);
    mostrarVector(vec, n, "Vector inicializado:");
    n=30; //le asigno 10 a n para poder realocar a mayor espacio de memoria
    realocarVector(vec, n);
    cargaVector(vec, n, max);
    mostrarVector(vec, n, "Vector con memoria expandida:");
    free(vec); //liberamos la memoria como dijo el profe
    return 0;
}
/*
    n = 10; // Nuevo tamaño del vector
    vec = (int *)realloc(vec, n * sizeof(int));
    if (vec == NULL) {
        printf("Error: No se pudo asignar más memoria.\n");
        return 1;
    }
*/

int *crearVector(int *vec, int n) { //asignamos memoria para que utilizar a vec como el vector.
    vec = (int *)malloc(n * sizeof(int));
    if (vec == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return NULL;
    }
    return vec;
}

void cargaVector(int *vec, int n, int max) { //aca generamos los valores aleatorios para agregar al vector
    int i;
    //numeros aleatorios entre 1 y 100
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        vec[i] = rand() % (max + 1);
    }

}

void mostrarVector(int vec[], int n, char *mensaje) { //aca solo le pasasmos el vector, la cantidad de elementos que tiene, y el mensaje que queremos mostrar
    int i;
    printf("%s\n", mensaje);
    for (i = 0; i < n; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int *realocarVector(int *vec, int n) { //aca realocamos la memoria para que utilice el vector, y se puedan agregar o quitar elementos al mismo.
    vec = (int *)realloc(vec, n * sizeof(int));
    if (vec == NULL) {
        printf("Error: No se pudo asignar más memoria.\n");
        return NULL;
    }
    return vec;
}