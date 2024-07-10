/*Modularizar a través de funciones, los procedimientos del programa.
char *crearCadena(char *, int);
char *realocarCadena(char *, int);
void cargarCadena(char *, int);
void mostrarCadena(char *, char *);
armar un vector dinamico de caracteres el cual contenga el abecedario en mayusculas o minusculas */
#include <stdio.h>
#include <stdlib.h>

char *crearCadena(char *, int);
char *realocarCadena(char *, int);
void cargarCadena(char *, int);
void mostrarCadena(char *, char *);

int main() {
    char *cadena = NULL;
    int longitud = 5; // Tamaño inicial de la cadena

    cadena = crearCadena(cadena, longitud);
    if (cadena == NULL) {
        return 1;
    }

    cargarCadena(cadena, longitud);
    mostrarCadena(cadena, "Cadena inicializada:");
    longitud = 15; // Cambia la longitud de la cadena
    cadena = realocarCadena(cadena, longitud);
    cargarCadena(cadena, longitud);
    mostrarCadena(cadena, "Cadena con memoria expandida:");

    free(cadena);
    return 0;
}


int main() {
    char *cadena = NULL; // Inicializa un puntero a char (cadena) a NULL
    char caracter;
    int longitud = 0; // Inicializa la longitud de la cadena a 0
    int capacidad = 10; // Tamaño inicial de la memoria asignada

    cadena = (char *)malloc(capacidad * sizeof(char));
    if (cadena == NULL) {
        printf("Error: No se pudo asignar memoria dinámica.\n");
        return 1;
    }
    printf("Ingresa caracteres (presiona Enter para finalizar):\n");
    // Lee caracteres hasta que se presiona Enter (tecla '\n')
    while ((caracter = getchar()) != '\n') {
        // Aumenta la longitud de la cadena en 1
        longitud++;
        if (longitud >= capacidad) {
            // Si la longitud supera la capacidad actual,
            // realoca memoria
            capacidad *= 2;
            cadena = (char *)realloc(cadena, capacidad * sizeof(char));

            if (cadena == NULL) {
                printf("Error: No se pudo asignar más memoria dinámica.\n");
                return 1;
            }
        }
        // Agrega el nuevo caracter a la cadena
        cadena[longitud - 1] = caracter;
    }
    // Agrega el carácter nulo
    // para formar una cadena válida en C
    cadena[longitud] = '\0';

    printf("La cadena ingresada es: %s\n", cadena);
    // Liberar la memoria dinámica cuando ya no se necesite
    free(cadena);

    return 0;
}
