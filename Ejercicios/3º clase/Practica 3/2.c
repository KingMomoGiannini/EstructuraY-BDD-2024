/*2.	Se ingresa un texto o frase y se muestra el texto original desde 
un archivo de texto y luego se muestra la cadena mas larga de cada renglón.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void escribirTexto(FILE *elArchivo);
void leerArchivo(FILE *elArchivo);

int main(){
    int opcion;
    FILE *elArchivo;
    elArchivo = fopen("textoEj2.txt", "a+");
    if (elArchivo != NULL){
        do
        {
            printf("1. Ingresar texto\n2. Mostrar cadena mas larga\n3. Salir\n");
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
    char cadena[100][100];
    char cadenaLarga[100];
    int i = 0;
    int j = 0;
    int linea = 0;
    int max = 0;
    //recorrer caracter a caracter y contar las palabras
    while(!feof(elArchivo)){
        c = fgetc(elArchivo);
        if (c != '\n' && c != ' '){ // Use && instead of || to check for both conditions
            cadena[i][j] = c;
            j++;
        }
        else if (c == ' ' || c == '\n'){ // Use || instead of && to check for either condition
            cadena[i][j] = '\0';
            if (j > max){
                max = j;
                strcpy(cadenaLarga, cadena[i]);
            }
            i++;
            j = 0;
        }
        if (c == '\n'){ // Move this block outside the else if condition
            linea++;
            printf("Cadena mas larga de la linea %d: %s\n",linea,cadenaLarga);
            max = 0;
        }
    }

}