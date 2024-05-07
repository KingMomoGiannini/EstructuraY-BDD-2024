/*Desarrollar un programa que reciba el archivo  empleado.csv que se encuentra en 
la seccion ARCHIVOS y se realize un menu con las siguientes opciones

opcion 1 leer el archivo de texto (separados por punto y coma).

opcion 2 generar un archivo binario que contenga los empleados del sector VENTAS.

opcion 3 generar un archivo de texto con los empleados cuyo oficio sea EMPLEADO 
(Empleados.txt) y un archivo de texto con los demas empleados (oficios.txt)*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int legajo;
    char apellido[50];
    char oficio[50];
    char sector[50];
    float salario;
}Empleado;

void leerArchivo(FILE *elArchivo,Empleado empleados[], int *cantEmpleados);
void generarArchivoBinario(Empleado empleados[], int *cantEmpleados);
void leerArchivoBinario(FILE *elArchivoBinario);
void generarArchivoEmpleados(Empleado empleados[], int *cantEmpleados);
void generarArchivoOficios(Empleado empleados[], int *cantEmpleados);

int main(){
    int opcion;
    Empleado empleados[100];
    FILE *elArchivo;
    FILE *elArchivoBinario;
    int cantEmpleados;
    elArchivo = fopen("empleados.csv", "r");
    if (elArchivo != NULL){
        do
        {
            printf("1. Leer archivo de texto\n2. Generar archivo binario con empleados del sector VENTAS\n3. Generar archivo de texto con empleados cuyo oficio sea EMPLEADO y un archivo de texto con los demas empleados\n4. Leer archivo Binario de sector VENTAS.\n5. Salir \n");
            scanf("%d", &opcion);
            switch (opcion)
            {
                case 1:
                    leerArchivo(elArchivo,empleados,&cantEmpleados);
                    printf("\nCantidad de empleados: %d\n", cantEmpleados);
                    rewind(elArchivo);
                    break;
                case 2:
                    generarArchivoBinario(empleados, &cantEmpleados);
                    break;
                case 3:
                    generarArchivoEmpleados(empleados, &cantEmpleados);
                    rewind(elArchivo);
                    generarArchivoOficios(empleados, &cantEmpleados);
                    break;
                case 4:
                    //rewind(elArchivoBinario);  <--- No es necesario, de hecho no permite la lectura del binario.
                    elArchivoBinario = fopen("empleadosVentas.dat", "rb");
                    if (elArchivoBinario != NULL)
                    {
                        leerArchivoBinario(elArchivoBinario);
                        fclose(elArchivoBinario);
                    }
                    else{
                        printf("No se pudo abrir el archivo");
                        system("pause");
                        system("cls");
                    }
                    break;
                    break;
                case 5:
                    break;
                default:
                    printf("Opcion no valida\n");
            }
        } while (opcion != 5); 
        
        fclose(elArchivo);
    }
    else{
        printf("No se pudo abrir el archivo");
        system("pause");
        system("cls");
    }
}


/*La funcion leer archivo, leera el archivo CSV (planilla de calculos) y guardara los datos del
mismo en una estructura llamada empleado que almacene esos datos. Usar STRTOK para separar los datos 
de las celdas y guardar cada uno en los campos de la estructura Empleado*/
void leerArchivo(FILE *elArchivo, Empleado empleados[], int *cantEmpleados){
    char linea[100];
    char *token;
    int i = 0;
    while(fgets(linea, 100, elArchivo) != NULL){
        token = strtok(linea, ";");
        empleados[i].legajo = atoi(token);
        token = strtok(NULL, ";");
        strcpy(empleados[i].apellido, token);
        token = strtok(NULL, ";");
        strcpy(empleados[i].oficio, token);
        token = strtok(NULL, ";");
        empleados[i].salario = atof(token);
        token = strtok(NULL, ";");
        strcpy(empleados[i].sector, token);
        token = strtok(NULL, ";");
        i++;
    }
    for(int j = 0; j < i; j++){
        printf("Legajo: %d\nApellido: %s\nOficio: %s\nSalario: %.2f\nSector: %s\n", empleados[j].legajo, empleados[j].apellido, empleados[j].oficio, empleados[j].salario, empleados[j].sector);
    }
    *cantEmpleados=i;
    system("pause");
    system("cls");
}

void generarArchivoBinario(Empleado empleados[], int *cantEmpleados){
    FILE *elArchivoBinario;
    elArchivoBinario = fopen("empleadosVentas.dat", "wb");
    if (elArchivoBinario != NULL){
        for(int i = 0; i < *cantEmpleados; i++){
            if(strcmp(empleados[i].sector,"VENTAS") == 1){
                fwrite(&empleados[i], sizeof(Empleado), 1, elArchivoBinario);
            }
        }
        fclose(elArchivoBinario);
    }
    else{
        printf("No se pudo abrir el archivo");
        system("pause");
        system("cls");
    }
}

void leerArchivoBinario(FILE *elArchivoBinario){
    Empleado empleado;
    //rewind(elArchivoBinario);  <--- No es necesario, de hecho no permite la lectura del binario.
    while(!feof(elArchivoBinario)){
        fread(&empleado, sizeof(Empleado), 1, elArchivoBinario);
        printf("Legajo: %d\nApellido: %s\nOficio: %s\nSalario: %.2f\nSector: %s\n", empleado.legajo, empleado.apellido, empleado.oficio, empleado.salario, empleado.sector);
    }
    system("pause");
    system("cls");
}

/*void leerArchivoBinario(FILE *elArchivoBinario){
    Empleado empleado;
    //rewind(elArchivoBinario);  <--- No es necesario, de hecho no permite la lectura del binario.
    fflush(stdin);
    while(fread(&empleado, sizeof(Empleado), 1, elArchivoBinario)){
        printf("Legajo: %d\nApellido: %s\nOficio: %s\nSalario: %.2f\nSector: %s\n", empleado.legajo, empleado.apellido, empleado.oficio, empleado.salario, empleado.sector);
    }
    system("pause");
    system("cls");
}*/

void generarArchivoEmpleados(Empleado empleados[], int *cantEmpleados){
    FILE *elArchivoEmpleados;
    elArchivoEmpleados = fopen("Empleados.txt", "w");
    if (elArchivoEmpleados != NULL){
        for(int i = 0; i < *cantEmpleados; i++){
            if(strcmp(empleados[i].oficio,"EMPLEADO") == 0){
                fprintf(elArchivoEmpleados, "Legajo: %d\nApellido: %s\nOficio: %s\nSalario: %.2f\nSector: %s\n", empleados[i].legajo, empleados[i].apellido, empleados[i].oficio, empleados[i].salario, empleados[i].sector);
            }
        }
        fclose(elArchivoEmpleados);
    }
    else{
        printf("No se pudo abrir el archivo");
        system("pause");
        system("cls");
    }
}

void generarArchivoOficios(Empleado empleados[], int *cantEmpleados){
    FILE *elArchivoOficios;
    elArchivoOficios = fopen("Oficios.txt", "w");
    if (elArchivoOficios != NULL){
        for(int i = 0; i < *cantEmpleados; i++){
            if(strcmp(empleados[i].oficio,"EMPLEADO") != 0){
                fprintf(elArchivoOficios, "Legajo: %d\nApellido: %s\nOficio: %s\nSalario: %.2f\nSector: %s\n", empleados[i].legajo, empleados[i].apellido, empleados[i].oficio, empleados[i].salario, empleados[i].sector);
            }
        }
        fclose(elArchivoOficios);
    }
    else{
        printf("No se pudo abrir el archivo");
        system("pause");
        system("cls");
    }
}