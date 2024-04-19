/*escribir un programa, que tenga dos opciones:
opcion 1 - escribir un archivo de texto que guarde el numero de legajo, el nombvre y apellido y el salario de ese empleado ingresado desde teclado.
opcion 2 - leer el archivo de texto generado y mostrarlo por pantalla.
la apretura y cierre del archivo se debe realizar en la funcion main.
separar acciones en funciones. como leer archivo y escribir archivo.
crear empleado como estructura*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct{
    int legajo;
    char nombre[MAX];
    char apellido[MAX];
    float salario;
}Empleado;

void escribirArchivo(FILE *archivo);
void leerArchivo(FILE *archivo);

int main(){
    int opcion;
    FILE *archivo; 
    archivo = fopen("empleados2.txt","a+");//Abrimos el archivo en modo lectura y escritura
    if (archivo != NULL)    //Si el archivo se abrio correctamente
    {
        do{ //Menu de opciones
            printf("\t1. Escribir archivo\n\t2. Leer archivo\n\t3. Salir\n");
            scanf("%d", &opcion);
            switch(opcion){
                case 1:
                    escribirArchivo(archivo);
                    break;
                case 2:
                    leerArchivo(archivo);
                    break;
                case 3:
                    break;
                default:
                    printf("Opcion incorrecta\n");
            }
        }while(opcion!=3);
        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo\n");
    }
    return 0;
}

void escribirArchivo(FILE *archivo){
    Empleado emp;
    printf("Ingrese legajo: ");
    scanf("%d", &emp.legajo);
    printf("Ingrese nombre: ");
    fflush(stdin);
    gets(emp.nombre);
    printf("Ingrese apellido: ");
    gets(emp.apellido);
    printf("Ingrese salario: ");
    scanf("%f", &emp.salario);
    fprintf(archivo, "%d %s %s %.2f\n", emp.legajo, emp.nombre, emp.apellido, emp.salario);
}

void leerArchivo(FILE *archivo){
    Empleado emp;
    rewind(archivo);
    while (!feof(archivo))
    {
        fscanf(archivo, "%d %s %s %f\n", &emp.legajo, emp.nombre, emp.apellido, &emp.salario);
        printf("%d\t%s\t%s\t$%.2f\n", emp.legajo, emp.nombre, emp.apellido, emp.salario);    
    }    
}

