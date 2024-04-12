#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//a) El largo de la cadena, realizando una función llamada CuentaCaracteres 
int CuentaCaracteres(char *cadena);

//b) La cantidad de palabras ingresadas ,realizando una función llamada CuentaPalabras
int CuentaPalabras(char *cadena);

//c) La cantidad de letras y números, que posee ese texto ingresado, realizando una función CuentaLetras
int CuentaLetras(char *cadena);

//d) Convertir la cadena ingresada en Mayúscula ,esa conversión dejarla en otra cadena, realizando una función llamada Mayúscula
void mayuscula(char *cadena, char *cadenaEnMayuscula);

//e) Extraer la ultima palabra de la cadena ,en una función llamada ExtraerPalabra
void extraerPalabra(char *cadena);

int main(){
    char cadena[100];
    char cadenaEnMayuscula[100];
    printf("Ingrese una cadena: ");
    gets(cadena); //de esta manera se puede ingresar una cadena con espacios, como una frase.
    //scanf("%s", cadena); <--- de esta manera no se puede ingresar una cadena con espacios, solo una palabra.
    printf("\n\n-\tLa cantidad de caracteres de la cadena es: %d\n", CuentaCaracteres(cadena));
    printf("------------------------------------------------------\n");
    printf("-\tLa cantidad de palabras de la cadena es: %d\n", CuentaPalabras(cadena));
    printf("------------------------------------------------------\n");
    printf("-\tLa cantidad de letras y numeros de la cadena es: %d\n", CuentaLetras(cadena));
    printf("------------------------------------------------------\n");
    mayuscula(cadena, cadenaEnMayuscula);
    printf("-\tLa cadena en mayuscula es: %s\n", cadenaEnMayuscula);
    printf("------------------------------------------------------\n");
    extraerPalabra(cadena);
    printf("--------------------------------------------\n");
    return 0;
}

int CuentaCaracteres(char *cadena){
    int i = 0;
    while(cadena[i] != '\0'){
        i++;
    }
    return i;

}

int CuentaPalabras(char *cadena){
    int i = 0;
    int palabras = 0;
    while(cadena[i] != '\0'){
        if(cadena[i] == ' '){
            palabras++;
        }
        i++;
    }
    return palabras + 1;
}

int CuentaLetras(char *cadena){
    int i = 0;
    int letras = 0;
    while(cadena[i] != '\0'){
        if((cadena[i] >= 'a' && cadena[i] <= 'z') || (cadena[i] >= 'A' && cadena[i] <= 'Z')){
            letras++;
        }
        if (cadena[i] >= '0' && cadena[i] <= '9'){
            letras++;
        }
        
        i++;
    }
    return letras;
}

void mayuscula(char *cadena, char *cadenaEnMayuscula){
    int i = 0;
    char cadenaMayuscula[100];
    while(cadena[i] != '\0'){
        if(cadena[i] >= 'a' && cadena[i] <= 'z'){
            cadenaMayuscula[i] = toupper(cadena[i]);
        }
        else if(cadena[i] == ' '){
            cadenaMayuscula[i] = ' ';
        }
        else{
            cadenaMayuscula[i] = cadena[i];
        }
        i++;
    }
    strcpy(cadenaEnMayuscula, cadenaMayuscula);
}

void extraerPalabra(char *cadena){
    int i = 0;
    int j = 0;
    char ultimaPalabra[100];
    while(cadena[i] != '\0'){
        if(cadena[i] == ' '){
            j = 0;
        }
        else{
            ultimaPalabra[j] = cadena[i];
            j++;
        }
        i++;
    }
    ultimaPalabra[j] = '\0';
    printf("-\tLa ultima palabra de la cadena es: %s\n", ultimaPalabra);
}
