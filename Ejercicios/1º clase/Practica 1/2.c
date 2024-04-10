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
void mostrarAlumnosAprobados(Alumno alumnos[], int cantidad);
void mostrarAlumnosPorInicial(Alumno alumnos[], int cantidad, char inicial);

int main(){
    
    int laCantidad = cantidadElementos();
    char inicial;
    Alumno alumnos[laCantidad];
    cargar(alumnos,laCantidad);
    mostrar(alumnos, laCantidad);
    system("pause");
    system("cls");
    mostrarAlumnosAprobados(alumnos, laCantidad);
    system("pause");
    system("cls");
    printf("Ingrese la inicial del nombre de los alumnos a mostrar: ");
    fflush(stdin);
    scanf("%c", &inicial);
    mostrarAlumnosPorInicial(alumnos, laCantidad, inicial);

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
        printf("\nIngrese el apellido del alumno %s: ", alumnos[i].nombre);
        scanf("%s", alumnos[i].apellido);
        printf("\nIngrese el legajo del alumno %s: ", alumnos[i].nombre);
        scanf("%d", &alumnos[i].legajo);
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


void mostrarAlumnosAprobados(Alumno alumnos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        int sumaNotas=0;
        for (int j = 0; j < 5; j++) {
            if (j==0 || j==2)
            {
                sumaNotas+=alumnos[i].nota[j];
            }
        }
        float promedio=sumaNotas/2;
        if (promedio>=6)
        {
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("Legajo: %d\n", alumnos[i].legajo);
            printf("Promedio: %.2f\n", promedio);
        }
    }
}

//funcion que muestre los alumnos cuyo nombre comience con una letra ingresada por el usuario
void mostrarAlumnosPorInicial(Alumno alumnos[], int cantidad, char inicial) {
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].nombre[0] == inicial) {
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("Legajo: %d\n", alumnos[i].legajo);
            printf("Notas: ");
            for (int j = 0; j < 5; j++) {
                printf("\n%.2f ", alumnos[i].nota[j]);
            }
        }
    }
}


