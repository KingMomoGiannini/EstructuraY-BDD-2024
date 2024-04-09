/*estructura que recopila los datos de una persona*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct persona{
    char nombre[20];
    char apellido[20];
    int edad;
    char sexo;
    } datos;

int main(){
    int i = 0;
    while(i<=10){
        datos persona[i];
        printf("Ingrese el nombre de la persona: ");
        scanf("%s", persona.nombre);
        printf("Ingrese el apellido de la persona: ");
        scanf("%s", persona.apellido);
        printf("Ingrese la edad de la persona: ");
        scanf("%d", &persona.edad);
        printf("Ingrese el sexo de la persona: ");
        scanf(" %c", &persona.sexo);
        printf("Nombre: %s\n", persona.nombre);
        printf("Apellido: %s\n", persona.apellido);
        printf("Edad: %d\n", persona.edad);
        printf("Sexo: %c\n", persona.sexo);
        i++;
    }
    
    return 0;

}