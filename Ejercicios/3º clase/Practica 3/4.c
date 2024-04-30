/*4.	Teniendo en cuenta el ejercicio 3 de la Practica 1 realizar un menú:
a.	Que permita realizar el alta de un empleado.
b.	Mostrar los empleados de la empresa.
c.	Mostrar los datos de un empleado en particular.
d.	Mostrar la cantidad de empleados por sector y generar un informe con esa información en un archivo de texto.
e.	Leer un archivo de texto llamado empleado.txt y  generar un archivo de texto con los empleados que cobran 5000$ de sueldo y con un aumento de 1000$.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int dni;
    char nombre[50];
    char apellido[50];
    char sector[50];
    float sueldo;
}Empleado;

void listarEmpleadosDelArchivo(FILE *elArchivo, Empleado *empleados, int *cantEmpleado);
void cargarEmpleadoEnArchivo(Empleado *empleados, int *cantEmpleado, FILE *elArchivo);
void mostrarEmpleados(Empleado *empleados, int cantEmpleados, FILE *elArchivo);
void mostrarEmpleado(Empleado *empleados, int cantEmpleados, int dni);
void cantidadEmpleadosPorSector(Empleado *empleados, int cantEmpleados,FILE *informe);
void leerArchivo(FILE *elArchivo, FILE *mayorSueldo);


int main(){
    Empleado empleados[100];
    int cantEmpleados = 0;
    int opcion;
    FILE *informe;
    FILE *elArchivo;
    FILE *mayorSueldo;
    informe = fopen("informe.txt", "a+");//Crea el  informe
    elArchivo = fopen("empleados.txt", "a+");//guarda a los empleados y sus datos
    mayorSueldo = fopen("empleadosMayorSueldo.txt", "w+");//guarda a los empleados y sus datos con aumento de sueldo
    system("cls");
    if(informe != NULL && elArchivo != NULL){
        listarEmpleadosDelArchivo(elArchivo, empleados, &cantEmpleados);
        do{
            int dni;
            printf("1. Cargar empleado\n2. Mostrar empleados\n3. Mostrar empleado\n4. Cantidad de empleados por sector\n5. Leer archivo\n6. Salir\n");
            scanf("%d", &opcion);
            switch (opcion)
            {
                case 1:
                    cargarEmpleadoEnArchivo(empleados, &cantEmpleados, elArchivo);
                    break;
                case 2:
                    rewind(elArchivo);
                    mostrarEmpleados(empleados, cantEmpleados, elArchivo);
                    break;
                case 3:
                    printf("Ingrese el DNI del empleado a buscar: ");
                    scanf("%d", &dni);
                    mostrarEmpleado(empleados, cantEmpleados, dni);
                    break;
                case 4:
                    cantidadEmpleadosPorSector(empleados, cantEmpleados, informe);
                    break;
                case 5:
                    rewind(elArchivo);
                    leerArchivo(elArchivo, mayorSueldo);
                    break;
                case 6:
                    break;
                default:
                    printf("Opcion no valida\n");
                    break;
            }
        }while(opcion != 6);
        fclose(informe);
        fclose(elArchivo);
        fclose(mayorSueldo);
    }
    else{
        printf("No se pudo abrir el archivo");
    }
    return 0;
}

void cargarEmpleadoEnArchivo(Empleado *empleados, int *cantEmpleado, FILE *elArchivo){
    int dni;
    int i;
    int existe;
    do{
        existe=0;
        printf("Ingrese el DNI del empleado: ");
        scanf("%d", &dni);
        if(dni != -1){
            existe = 0;
            for(i = 0; i < *cantEmpleado; i++){
                if(empleados[i].dni == dni){
                    existe = 1;
                }
            }
            if(existe == 0){
                empleados[*cantEmpleado].dni = dni;
                fflush(stdin);
                printf("Ingrese el nombre del empleado: ");
                scanf("%s", empleados[*cantEmpleado].nombre);
                printf("Ingrese el apellido del empleado: ");
                scanf("%s", empleados[*cantEmpleado].apellido);
                printf("Ingrese el sector del empleado: ");
                scanf("%s", empleados[*cantEmpleado].sector);
                printf("Ingrese el sueldo del empleado: ");
                scanf("%f", &empleados[*cantEmpleado].sueldo);
                fprintf(elArchivo, "%d %s %s %s %.2f\n", empleados[*cantEmpleado].dni, empleados[*cantEmpleado].nombre, empleados[*cantEmpleado].apellido, empleados[*cantEmpleado].sector, empleados[*cantEmpleado].sueldo);
                (*cantEmpleado)++;
            }else{
                printf("El empleado ya fue ingresado\n");
            }
        }
    }while(dni != -1);
}

void mostrarEmpleados(Empleado *empleados, int cantEmpleados, FILE *elArchivo){
    while(!feof(elArchivo)){
        fscanf(elArchivo, "%d %s %s %s %f", &empleados[cantEmpleados].dni, empleados[cantEmpleados].nombre, empleados[cantEmpleados].apellido, empleados[cantEmpleados].sector, &empleados[cantEmpleados].sueldo);
        printf("DNI: %d\nNombre: %s\nApellido: %s\nSector: %s\nSueldo: %.2f\n", empleados[cantEmpleados].dni, empleados[cantEmpleados].nombre, empleados[cantEmpleados].apellido, empleados[cantEmpleados].sector, empleados[cantEmpleados].sueldo);
        cantEmpleados++;
    }
}

void mostrarEmpleado(Empleado *empleados, int cantEmpleados, int dni){//buscar empleado en la lista cargada
    int i;
    for(i = 0; i < cantEmpleados; i++){
        if(empleados[i].dni == dni){
            printf("DNI: %d\nNombre: %s\nApellido: %s\nSector: %s\nSueldo: %.2f\n", empleados[i].dni, empleados[i].nombre, empleados[i].apellido, empleados[i].sector, empleados[i].sueldo);
        }
    }
}

void cantidadEmpleadosPorSector(Empleado *empleados, int cantEmpleados, FILE *informe){
    char sectores[100][50];
    int cantidad[100];
    int i;
    int j;
    int existe;
    int cantSectores = 0;
    for(i = 0; i < cantEmpleados; i++){
        existe = 0;
        for(j = 0; j < cantSectores; j++){
            if(strcmp(empleados[i].sector, sectores[j]) == 0){
                cantidad[j]++;
                existe = 1;
            }
        }
        if(existe == 0){
            strcpy(sectores[cantSectores], empleados[i].sector);
            cantidad[cantSectores] = 1;
            cantSectores++;
        }
    }
    for(i = 0; i < cantSectores; i++){
        printf("Sector: %s Cantidad de empleados: %d\n", sectores[i], cantidad[i]);
        fprintf(informe, "Sector: %s Cantidad de empleados: %d\n", sectores[i], cantidad[i]);
    }
}

void leerArchivo(FILE *elArchivo, FILE *mayorSueldo){
    Empleado empleados[100];
    int cantEmpleados = 0;
    while(!feof(elArchivo)){
        fscanf(elArchivo, "%d %s %s %s %f", &empleados[cantEmpleados].dni, empleados[cantEmpleados].nombre, empleados[cantEmpleados].apellido, empleados[cantEmpleados].sector, &empleados[cantEmpleados].sueldo);
        if(empleados[cantEmpleados].sueldo >= 5000){
            empleados[cantEmpleados].sueldo += 1000;
            fprintf(mayorSueldo, "%d %s %s %s %.2f\n", empleados[cantEmpleados].dni, empleados[cantEmpleados].nombre, empleados[cantEmpleados].apellido, empleados[cantEmpleados].sector, empleados[cantEmpleados].sueldo);
        }
        cantEmpleados++;
    }
}

void listarEmpleadosDelArchivo(FILE *elArchivo, Empleado *empleados, int *cantEmpleado){//Crea un array de empleados, cargando el mismo con los que estan en el archivo
    while(!feof(elArchivo)){
        fscanf(elArchivo, "%d %s %s %s %f", &empleados[*cantEmpleado].dni, empleados[*cantEmpleado].nombre, empleados[*cantEmpleado].apellido, empleados[*cantEmpleado].sector, &empleados[*cantEmpleado].sueldo);
        (*cantEmpleado)++;
    }
}
