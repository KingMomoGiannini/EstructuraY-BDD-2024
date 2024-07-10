#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int *vec;
    int i,n = 30; // Tama�o del array

    // Asignaci�n de memoria usando malloc
    vec = (int *)malloc(n * sizeof(int));
    srand(time(NULL));
    if (vec == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return 1;
    }

    // Inicializaci�n del array
    for ( i = 0; i < n; i++) {
        vec[i] = rand()%(101);
    }

    // Imprimir el array
    printf("Array inicializado con malloc:\n");
    for ( i = 0; i < n; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");

    // Liberar la memoria asignada
    free(vec);
    return 0;
}
