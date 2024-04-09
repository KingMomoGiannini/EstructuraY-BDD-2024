#include <stdio.h>

int main() {
    int lista[] = {24, 30, 15, 45, 34};
    int *ptr = lista; 

    for (int i = 0; i < sizeof(lista) / sizeof(int); i++) {
        printf("n%d: %d \n",i+1, *ptr); 
        ptr++; 
    }
    return 0;
}