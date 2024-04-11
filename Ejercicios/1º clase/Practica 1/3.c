#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* Realizar un programa que permita realizar lo siguiente  
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
    int j;
    int existe;
    do{
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

void mostrarEmpleados(Empleado *empleados, int cantEmpleados){
    int i;
    for(i = 0; i < cantEmpleados; i++){
        if (strcmp(empleados[i].sector,"a"))
        {
            printf("-----------Sector A-----------\n", empleados[i].sector);
            printf("DNI: %d\n", empleados[i].dni);
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Apellido: %s\n", empleados[i].apellido);
        }
        else if (strcmp(empleados[i].sector,"b"))
        {
            printf("-----------Sector B-----------\n", empleados[i].sector);
            printf("DNI: %d\n", empleados[i].dni);
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Apellido: %s\n", empleados[i].apellido);
        }
        else if (strcmp(empleados[i].sector,"c"))
        {
            printf("-----------Sector C-----------\n", empleados[i].sector);
            printf("DNI: %d\n", empleados[i].dni);
            printf("Nombre: %s\n", empleados[i].nombre);
            printf("Apellido: %s\n", empleados[i].apellido);
        }
        
    }
}
