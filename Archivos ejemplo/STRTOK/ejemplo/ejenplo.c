#include <stdio.h>
#include <string.h>

int main(){
    char cadena[] = "Hola mundo soy una cadena separada por espacios",
    delimitador[] = " ";



    char *token = strtok(cadena, delimitador);
    if(token != NULL){
        while(token != NULL){
            // S�lo en la primera pasamos la cadena; en las siguientes pasamos NULL
            printf("Token: %s\n", token);
           
            token = strtok(NULL, delimitador);


        }



    }
}
