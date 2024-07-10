/*programa que calcule el factorial de un numero ingresado como parametro a una funcion void */
#include <stdio.h>
#include <stdlib.h>

int factorial(int n){
    if(n==0){
        return 1;
    }else{
        return n*factorial(n-1);
    }
}

int main(){
    int n;
    printf("Ingrese un numero: ");
    scanf("%d",&n);
    printf("El factorial de %d es %d\n",n,factorial(n));
    return 0;
}