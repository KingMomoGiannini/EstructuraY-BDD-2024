#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* 
Ejercicio 3 - Practica 1
Realizar un programa que permita realizar lo siguiente  
a) Una función que permita cargar los empleados de una empresa hasta que decida 
terminar el ingreso de datos con DNI igual a -1. Deberá validarse si el empleado si 
ya fue ingresado o no 
b) Realizar el ordenamiento de los empleados por orden alfabético  
c) Mostrar los empleados por sector*/


typedef struct{
    int dni;
    char nombre[50];
    char apellido[50];
    char sector[50];
}Empleado;

void cargarEmpleados(Empleado *empleados, int *cantEmpleados);
void ordenarEmpleados(Empleado *empleados, int cantEmpleados);
void mostrarEmpleados(Empleado *empleados, int cantEmpleados);
void ordenarEmpleadosPorSector(Empleado *empleados, int cantEmpleados);

int main(){
    Empleado empleados[100];
    int cantEmpleados = 0;
    cargarEmpleados(empleados, &cantEmpleados);
    ordenarEmpleados(empleados, cantEmpleados);
    mostrarEmpleados(empleados, cantEmpleados);
    return 0;
}

void cargarEmpleados(Empleado *empleados, int *cantEmpleados){
    int dni;
    int i;
    int existe;
    do{
        existe=0;
        printf("Ingrese el DNI del empleado: ");
        scanf("%d", &dni);
        if(dni != -1){
            existe = 0;
            for(i = 0; i < *cantEmpleados; i++){
                if(empleados[i].dni == dni){
                    existe = 1;
                }
            }
            if(existe == 0){
                empleados[*cantEmpleados].dni = dni;
                printf("Ingrese el nombre del empleado: ");
                scanf("%s", empleados[*cantEmpleados].nombre);
                printf("Ingrese el apellido del empleado: ");
                scanf("%s", empleados[*cantEmpleados].apellido);
                printf("Ingrese el sector del empleado: ");
                scanf("%s", empleados[*cantEmpleados].sector);
                (*cantEmpleados)++;
            }else{
                printf("El empleado ya fue ingresado\n");
            }
        }
    }while(dni != -1);
}

void ordenarEmpleados(Empleado *empleados, int cantEmpleados){
    int i;
    int j;
    Empleado aux;
    for(i = 0; i < cantEmpleados - 1; i++){
        for(j = 0; j < cantEmpleados - i - 1; j++){
            if(strcmp(empleados[j].apellido, empleados[j + 1].apellido) > 0){
                aux = empleados[j];
                empleados[j] = empleados[j + 1];
                empleados[j + 1] = aux;
            }
        }
    }
}

void ordenarEmpleadosPorSector(Empleado *empleados, int cantEmpleados){
    int i;
    int j;
    Empleado aux;
    for(i = 0; i < cantEmpleados - 1; i++){
        for(j = 0; j < cantEmpleados - i - 1; j++){
            if(strcmp(empleados[j].sector, empleados[j + 1].sector) > 0){
                aux = empleados[j];
                empleados[j] = empleados[j + 1];
                empleados[j + 1] = aux;
            }
        }
    }
}

void mostrarEmpleados(Empleado *empleados, int cantEmpleados){
    int i;
    char elSector[50]="";
    //ordenar empleados por sector
    ordenarEmpleadosPorSector(empleados, cantEmpleados);
    for(i = 0; i < cantEmpleados; i++){
        if (strcmp(elSector, empleados[i].sector)==0){
            printf("-------------------------------------------------\n");
            printf("DNI: %d\n", empleados[i].dni);
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Apellido: %s\n", empleados[i].apellido);
            printf("-------------------------------------------------\n");
        }
        else{
            strcpy(elSector, empleados[i].sector);
            printf("\n-----------Sector %s-----------\n", elSector);  
            printf("DNI: %d\n", empleados[i].dni);
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Apellido: %s\n", empleados[i].apellido);      
        }
    }
}
