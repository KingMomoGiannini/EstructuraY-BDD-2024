/*1 . Se ingresa un texto de varias líneas  desde teclado y se guarda en un archivo de texto .
Luego se muestra la cantidad de palabras que tiene cada línea*/

//agregar menu para contar palabras o escribir texto
//agregar opcion para salir del programa

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void escribirTexto(FILE *elArchivo);
void leerArchivo(FILE *elArchivo);

int main(){
    int opcion;
    FILE *elArchivo;
    elArchivo = fopen("texto.txt", "a+");
    if (elArchivo != NULL){
        do
        {
            printf("1. Ingresar texto\n2. Contar palabras\n3. Salir\n");
            scanf("%d", &opcion);
            switch (opcion)
            {
                case 1:
                    escribirTexto(elArchivo);
                    break;
                case 2:
                    rewind(elArchivo);
                    leerArchivo(elArchivo);
                    break;
                case 3:
                    break;
                default:
                    printf("Opcion no valida\n");
            }
        } while (opcion != 3); 
        
        fclose(elArchivo);
    }
    else{
        printf("No se pudo abrir el archivo");
    }
}

void escribirTexto(FILE *elArchivo){
    char texto[100];
    printf("Ingrese el texto a guardar en el archivo: ");
    fflush(stdin);
    gets(texto);
    fprintf(elArchivo, "%s\n", texto);
}

void leerArchivo(FILE *elArchivo){
    char c;
    int palabras = 0;
    //recorrer caracter a caracter y contar las palabras
    while(!feof(elArchivo)){
        c = fgetc(elArchivo);
        if(c == ' ' || c == '\n'){//si el caracter es un espacio, fin de archivo o salto de linea
            palabras++; //se incrementa la cantidad de palabras
        }
    }
        printf("La cantidad de palabras en la linea es: %d\n", palabras);
    
}