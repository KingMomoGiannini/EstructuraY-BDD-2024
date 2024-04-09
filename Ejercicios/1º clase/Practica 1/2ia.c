#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUMNOS 100
#define MAX_NOTAS 5

// Definición de la estructura Alumno
typedef struct {
    char nombre[50];
    float notas[MAX_NOTAS];
    float promedio;
} Alumno;

// Prototipos de funciones
int pedirCantidadElementos();
void cargarAlumnos(Alumno alumnos[], int cantidad);
void calcularPromedio(Alumno alumnos[], int cantidad);
void ordenarAlumnosPorPromedio(Alumno alumnos[], int cantidad);
void mostrarAlumnos(Alumno alumnos[], int cantidad);

int main() {
    int cantidad = pedirCantidadElementos();
    Alumno alumnos[MAX_ALUMNOS];

    cargarAlumnos(alumnos, cantidad);
    calcularPromedio(alumnos, cantidad);
    ordenarAlumnosPorPromedio(alumnos, cantidad);
    mostrarAlumnos(alumnos, cantidad);

    return 0;
}

// Función para pedir al usuario la cantidad de elementos a almacenar
int pedirCantidadElementos() {
    int cantidad;
    printf("Ingrese la cantidad de alumnos: ");
    scanf("%d", &cantidad);
    return cantidad;
}

// Función para cargar los datos de los alumnos
void cargarAlumnos(Alumno alumnos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("\nIngrese el nombre del alumno %d: ", i + 1);
        scanf("%s", alumnos[i].nombre);
        printf("Ingrese las notas del alumno %d (máximo 5 notas): ", i + 1);
        for (int j = 0; j < MAX_NOTAS; j++) {
            scanf("%f", &alumnos[i].notas[j]);
        }
    }
}

// Función para calcular el promedio de cada alumno
void calcularPromedio(Alumno alumnos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        float suma = 0;
        for (int j = 0; j < MAX_NOTAS; j++) {
            suma += alumnos[i].notas[j];
        }
        alumnos[i].promedio = suma / MAX_NOTAS;
    }
}

// Función para ordenar los alumnos por promedio de mayor a menor
void ordenarAlumnosPorPromedio(Alumno alumnos[], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (alumnos[j].promedio < alumnos[j + 1].promedio) {
                Alumno temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }
}

// Función para mostrar los datos de los alumnos
void mostrarAlumnos(Alumno alumnos[], int cantidad) {
    printf("\nAlumnos ordenados por promedio de mayor a menor:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Nombre: %s, Promedio: %.2f\n", alumnos[i].nombre, alumnos[i].promedio);
    }
}
