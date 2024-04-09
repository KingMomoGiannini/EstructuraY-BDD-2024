#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//definicion de tipos de datos
//cadena como tipo de dato o String

typedef char cadena[50];

typedef struct {
    int legajo;
    char nombre[20];
    char apellido[20];
    float nota[5];
}Alumno;

//prototipos de funciones
int cantidadElementos();
void cargar(Alumno alumnos[],int cantidad);
void mostrar(Alumno alumnos[], int cantidad);
void ordenarPorPromedio(Alumno alumnos[], int cantidad, int promedios[]);

int main(){
    
    int laCantidad = cantidadElementos();
    Alumno alumnos[laCantidad];
    cargar(alumnos,laCantidad);
    mostrar(alumnos, laCantidad);
    system("pause");
    system("cls");
    return 0;
}
//funcion que pida al usuario cantidad de elementos a almacenar en la lista
int cantidadElementos(){
    int cantidad;
    printf("Ingrese la cantidad de elementos a almacenar en la lista: ");
    scanf("%d", &cantidad);
    return cantidad;
}

//funcion void "cargar" que cargue los N alumnos con sus respectivas notas correspondientes a un curso de programacion.
void cargar(Alumno alumnos[], int cantidad) {

    // Solicitar al usuario que ingrese los datos de cada alumno
    for (int i = 0; i < cantidad; i++) {
        printf("Ingrese el nombre del alumno %d: ", i + 1);
        scanf("%s", alumnos[i].nombre);
    //ciclo que me permita cargar hasta 5 notas de alumnos
        for (int j = 0; j < 5; j++) {
            printf("Ingrese la nota %d del alumno %s: ", j + 1, alumnos[i].nombre);
            scanf("%2f", &alumnos[i].nota[j]);
        }
        system("cls");
    }
    
}

void mostrar(Alumno alumnos[], int cantidad) {
    float promedios[cantidad];
    for (int i = 0; i < cantidad; i++) {
        int sumaNotas=0;
        for (int j = 0; j < 5; j++) {
            if (j==0 || j==2)
            {
                sumaNotas+=alumnos[i].nota[j];
            }
        }
        promedios[i]=sumaNotas/2;
    }
    ordenarPorPromedio(alumnos, cantidad, promedios);
    for (int i = 0; i < cantidad; i++) {
        printf("Nombre: %s\n", alumnos[i].nombre);
        printf("Promedio: %.2f\n", promedios[i]);
    }
}

//funcion que ordene los alumnos por promedio
void ordenarPorPromedio(Alumno alumnos[], int cantidad, int promedios[]) {
    for (int i = 0; i < cantidad; i++) {
        for (int j = 0; j < cantidad - 1; j++) {
            if (promedios[j] < promedios[j + 1]) {
                int aux = promedios[j];
                promedios[j] = promedios[j + 1];
                promedios[j + 1] = aux;
                Alumno auxAlumno = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = auxAlumno;
            }
        }
    }
}



