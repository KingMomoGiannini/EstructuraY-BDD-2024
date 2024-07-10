#include <stdio.h>
#include <stdlib.h>

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
