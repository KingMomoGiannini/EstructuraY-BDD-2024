/*1 . Se ingresa un texto de varias líneas  desde teclado y se guarda en un archivo de texto .
Luego se muestra la cantidad de palabras que tiene cada línea*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void escribirTexto(FILE *elArchivo);
void leerArchivo(FILE *elArchivo);

int main(){
    FILE *elArchivo;
    elArchivo = fopen("texto.txt", "w+");
    if (elArchivo != NULL){
        escribirTexto(elArchivo);
        rewind(elArchivo);
        leerArchivo(elArchivo);
        fclose(elArchivo);
    }
    else{
        printf("No se pudo abrir el archivo");
    }
}

void escribirTexto(FILE *elArchivo){
    char texto[100];
    printf("Ingrese el texto a guardar en el archivo: ");
    gets(texto);
    fprintf(elArchivo, "%s", texto);
}

void leerArchivo(FILE *elArchivo){
    char c;
    int palabras = 0;
    //recorrer caracter a caracter y contar las palabras
    while(!feof(elArchivo)){
        c = fgetc(elArchivo);
        if(c == ' ' || c == EOF || c == '\n'){//si el caracter es un espacio, fin de archivo o salto de linea
            palabras++; //se incrementa la cantidad de palabras
        }
    }
        printf("La cantidad de palabras en la linea es: %d\n", palabras);
    
}