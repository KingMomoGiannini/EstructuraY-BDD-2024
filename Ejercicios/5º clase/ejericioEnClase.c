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
/*void generarArchivoEmpleados(FILE *elArchivo);
void generarArchivoOficios(FILE *elArchivo);
*/
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
            printf("1. Leer archivo de texto\n2. Generar archivo binario con empleados del sector VENTAS\n3. Generar archivo de texto con empleados cuyo oficio sea EMPLEADO y un archivo de texto con los demas empleados\n4.Salir\n5. Leer archivo Binario\n");
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
                /*case 3:
                    rewind(elArchivo);
                    generarArchivoEmpleados(elArchivo);
                    rewind(elArchivo);
                    generarArchivoOficios(elArchivo);
                    break;
                    */
                case 4:
                    break;
                case 5:
                    rewind(elArchivoBinario);
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
                default:
                    printf("Opcion no valida\n");
            }
        } while (opcion != 4); 
        
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
    rewind(elArchivoBinario);
    while(!feof(elArchivoBinario)){
        fread(&empleado, sizeof(Empleado), 1, elArchivoBinario);
        printf("Legajo: %d\nApellido: %s\nOficio: %s\nSalario: %.2f\nSector: %s\n", empleado.legajo, empleado.apellido, empleado.oficio, empleado.salario, empleado.sector);
    }
    system("pause");
    system("cls");
}