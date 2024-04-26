/*escribir un programa, que tenga dos opciones:
opcion 1 - escribir un archivo de texto que guarde el numero de legajo, el nombvre y apellido y el salario de ese empleado ingresado desde teclado.
opcion 2 - leer el archivo de texto generado y mostrarlo por pantalla.
la apretura y cierre del archivo se debe realizar en la funcion main.
separar acciones en funciones. como leer archivo y escribir archivo.
crear empleado como estructura*/

/*Clase 4 - agregar:
opcion 3 - Calcular promedio de salarios
opcion 4 - generar archivo de texto con los empleados ordenados alfabeticamente por apellido llamado "ordenado.txt"
opcion 5 - Leer archivo generado.*/

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
void calcularPromedio(FILE *archivo);
void ordenarArchivo(FILE *archivo,FILE *archivoOrdenado);
void mostrarArchivoOrdenado(FILE *archivo);

int main(){
    int opcion;
    FILE *archivo; 
    FILE *archivoOrdenado;
    archivo = fopen("empleados2.txt","a+");//Abrimos el archivo en modo lectura y escritura
    if (archivo != NULL)    //Si el archivo se abrio correctamente
    {
        do{ //Menu de opciones
            printf("\t1. Escribir archivo\n\t2. Leer archivo\n\t3. Calcular promedio de salarios\n \t4. Ordenar archivo\n \t5. Mostrar archivo ordenado\n \t6. Salir\n");
            scanf("%d", &opcion);
            switch(opcion){
                case 1:
                    escribirArchivo(archivo);
                    break;
                case 2:
                    leerArchivo(archivo);
                    break;
                
                case 3:
                    calcularPromedio(archivo);
                    break;
                case 4:
                    ordenarArchivo(archivo,archivoOrdenado);
                    break;
                case 5:
                    mostrarArchivoOrdenado(archivoOrdenado);
                    break;
                case 6:
                    break;    
                default:
                    printf("Opcion incorrecta\n");
            }
        }while(opcion!=6);
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

void calcularPromedio(FILE *archivo){
    Empleado emp;
    float salario, promedio;
    int cantidad = 0;
    rewind(archivo);
    while (!feof(archivo))
    {
        fscanf(archivo, "%d %s %s %f\n", &emp.legajo, emp.nombre, emp.apellido, &emp.salario);
        salario += emp.salario;
        cantidad++;
    }
    promedio = salario / cantidad;
    printf("El promedio de salarios es: $%.2f\n", promedio);
}

void ordenarArchivo(FILE *archivo,FILE *archivoOrdenado){
    Empleado emp[MAX], aux;
    int i = 0, j = 0, cantidad = 0;
    rewind(archivo);
    while (!feof(archivo))
    {
        fscanf(archivo, "%d %s %s %f\n", &emp[i].legajo, emp[i].nombre, emp[i].apellido, &emp[i].salario);
        i++;
        cantidad++;
    }
    for (i = 0; i < cantidad; i++)
    {
        for (j = 0; j < cantidad - 1; j++)
        {
            if (strcmp(emp[j].apellido, emp[j+1].apellido) > 0)
            {
                aux = emp[j];
                emp[j] = emp[j+1];
                emp[j+1] = aux;
            }
        }
    }
    fclose(archivo);
    archivoOrdenado = fopen("ordenado.txt", "w");
    if (archivo != NULL)
    {
        for (i = 0; i < cantidad; i++)
        {
            fprintf(archivoOrdenado, "%d %s %s %.2f\n", emp[i].legajo, emp[i].nombre, emp[i].apellido, emp[i].salario);
        }
        fclose(archivoOrdenado);    
    }
    else{
        printf("Error al abrir el archivo\n");
    }
    
}

void mostrarArchivoOrdenado(FILE *archivoOrdenado){
    Empleado emp;
    archivoOrdenado = fopen("ordenado.txt", "r");
    if (archivoOrdenado != NULL){ //Si el archivo se abrio correctamente
        rewind(archivoOrdenado);
        while (!feof(archivoOrdenado))
        {
            fscanf(archivoOrdenado, "%d %s %s %f\n", &emp.legajo, emp.nombre, emp.apellido, &emp.salario);
            printf("%d\t%s\t%s\t$%.2f\n", emp.legajo, emp.nombre, emp.apellido, emp.salario);    
        }    
        fclose(archivoOrdenado);
        system("pause");
        system("cls");
    } 
    else
    {
        printf("Error al abrir el archivo\n");
    }
}
