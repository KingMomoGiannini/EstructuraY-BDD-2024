/*3.	Teniendo en cuenta el ejercicio 2 de la practica 1 generar un archivo 
de texto que guarde los datos ingresados de los alumnos y luego se muestre desde el archivo
a.	Mostrar los alumnos por apellido en orden alfabético y guardar la información 
obtenida en otro archivo de texto*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char cadena[50];

typedef struct {
    int legajo;
    char nombre[20];
    char apellido[20];
    float nota[5];
}Alumno;

int cantidadElementos();
void cargar(Alumno alumnos[],int cantidad);
void mostrar(Alumno alumnos[], int cantidad);
void ordenarPorApellido(Alumno alumnos[], int cantidad);
void guardarEnArchivo(Alumno alumnos[], int cantidad, FILE *elArchivo);


int main(){
    
    int laCantidad = cantidadElementos();
    Alumno alumnos[laCantidad];
    cargar(alumnos,laCantidad);
    mostrar(alumnos, laCantidad);
    FILE *elArchivo;
    FILE *elArchivoNuevo;
    elArchivo = fopen("alumnos.txt", "a+");
    elArchivoNuevo = fopen("alumnosOrdenados.txt", "a+");
    if (elArchivo != NULL){
        guardarEnArchivo(alumnos, laCantidad, elArchivo);
        ordenarPorApellido(alumnos, laCantidad);
        mostrar(alumnos, laCantidad);
        guardarEnArchivo(alumnos, laCantidad, elArchivoNuevo);
        fclose(elArchivo);
        fclose(elArchivoNuevo);
    }
    else{
        printf("No se pudo abrir el archivo");
    }

    return 0;
}

int cantidadElementos(){
    int cantidad;
    printf("Ingrese la cantidad de elementos a almacenar en la lista: ");
    scanf("%d", &cantidad);
    return cantidad;
}

void cargar(Alumno alumnos[], int cantidad) {
    system("cls");
    for (int i = 0; i < cantidad; i++) {

        printf("Ingrese el nombre del alumno %d: ", i + 1);
        scanf("%s", alumnos[i].nombre);
        printf("\nIngrese el apellido del alumno %s: ", alumnos[i].nombre);
        scanf("%s", alumnos[i].apellido);
        printf("\nIngrese el legajo del alumno %s: ", alumnos[i].nombre);
        scanf("%d", &alumnos[i].legajo);
        for (int j = 0; j < 5; j++){
            printf("\nIngrese la nota %d del alumno %s: ", j + 1, alumnos[i].nombre);
            scanf("%f", &alumnos[i].nota[j]);
        }
    }
}

void mostrar(Alumno alumnos[], int cantidad){
    for (int i = 0; i < cantidad; i++){
        printf("\nNombre: %s\nApellido: %s\nLegajo: %d\n", alumnos[i].nombre, alumnos[i].apellido, alumnos[i].legajo);
        for (int j = 0; j < 5; j++){
            printf("Nota %d: %.2f\n", j + 1, alumnos[i].nota[j]);
        }
    }
}

void ordenarPorApellido(Alumno alumnos[], int cantidad){
    Alumno aux;
    for (int i = 0; i < cantidad - 1; i++){
        for (int j = 0; j < cantidad - i - 1; j++){
            if (strcmp(alumnos[j].apellido, alumnos[j + 1].apellido) > 0){
                aux = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = aux;
            }
        }
    }
}

void guardarEnArchivo(Alumno alumnos[], int cantidad, FILE *elArchivo){
    for (int i = 0; i < cantidad; i++){
        fprintf(elArchivo, "Nombre: %s\nApellido: %s\nLegajo: %d\n", alumnos[i].nombre, alumnos[i].apellido, alumnos[i].legajo);
        for (int j = 0; j < 5; j++){
            fprintf(elArchivo, "Nota %d: %.2f\n", j + 1, alumnos[i].nota[j]);
        }
        fprintf(elArchivo, "\n");
    }
}

