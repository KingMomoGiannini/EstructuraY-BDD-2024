/* Funciones necesarias para la estructura tipo cola:

void acolar(nodo, nodo **, nodo **)
nodo *nuevonodo(nodo);
nodo desacoar(nodo **);
void listar(nodo*);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_dato(void);
void dato_eliminado(nodo);
int menu(void);

y una funcion que permita guardar los datos acolados en un archivo binario .dat */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define s scanf

typedef struct elemento
{
    int dato;
    struct elemento *sig;
}nodo;

typedef struct
{
    int dato;
}nodoDato;

void acolar(nodo, nodo **, nodo **);
nodo *nuevonodo(nodo);
nodo desacolar(nodo **);
void listar(nodo*);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_dato(void);
void dato_eliminado(nodo);
int menu(void);
void guardarEnArchivo(nodo *, FILE *archivoDatos);
void leerArchivo(FILE *archivoDatos);

int main()
{
    FILE *archivoDatos;
    nodo *p=NULL, *aux, r;
    int op;
    do
    {
        op=menu();
        switch(op)
        {
            case 1:
                r=ingresar_dato();
                acolar(r, &p, &aux);
                break;
            case 2:
                if(verificar(p) != NULL){
                    r=desacolar(&p);
                    dato_eliminado(r);
                }
                else
                    printf("\nNo hay elementos en la cola\n");
                break;
            case 3:
                if(verificar(p) != NULL)
                {
                    printf("\nContenido de la cola:\n\n");
                    listar(p);
                    getch();
                }
                else
                    printf("\nNo hay elementos en la cola\n");
                break;
            case 4:
                if(verificar(p) != NULL)
                {
                    vaciar(&p);
                    printf("\nCola vaciada\n");
                    printf("\nPresione una tecla para continuar...");
                    getch();
                }
                else
                    printf("\nNo hay elementos en la cola\n");
                break;
            case 5:
                if(verificar(p) != NULL)
                {
                    guardarEnArchivo(p,&archivoDatos);
                    printf("\nDatos guardados en archivo\n");
                    printf("\nPresione una tecla para continuar...");
                    getch();
                }
                else
                    printf("\nNo hay elementos en la cola\n");
                break;
            case 6:
                if (verificar(p) != NULL)
                {
                    leerArchivo(archivoDatos);
                    printf("\nPresione una tecla para continuar...");
                    getch();
                }
                else{
                    printf("\nNo hay elementos en la cola\n");
                }
                break;             
        }
    }while(op!=7);
    return 0;
}

int menu(void)
{
    int op;
    system("cls");
    printf("\n\t**********MENU PRINCIPAL**********\n");
    do
    {  
        printf("\n\t\t1.- Acolar");
        printf("\n\t\t2.- Desacolar");
        printf("\n\t\t3.- Listar");
        printf("\n\t\t4.- Vaciar");
        printf("\n\t\t5.- Guardar en archivo");
        printf("\n\t\t6.- Leer archivo");
        printf("\n\t\t7.- Salir");
        printf("\n\t\tOpcion: ");
        s("%d", &op);
    } while (op<1 || op>7);
    return (op);
}

void acolar(nodo r, nodo **p, nodo **aux)
{
    nodo *nuevo;
    nuevo=nuevonodo(r);
    if(*p==NULL)
        *p=nuevo;
    else
        (*aux)->sig=nuevo;
    *aux=nuevo;
}

nodo *nuevonodo(nodo r)
{
    nodo *x;
    x=(nodo *)malloc(sizeof(nodo));
    if(x==NULL)
    {
        printf("\nNo hay memoria disponible\n");
    }
    x->dato = r.dato;
    x->sig = NULL;
    return (x);
}

nodo desacolar(nodo **p)
{
    nodo r, *aux;
    r=**p;
    aux=*p;
    *p = (*p)->sig;
    free(aux);
    return (r);
}

void listar(nodo *p)
{
    if(p){
        printf("\tDireccion:<%p> dato:%d siguiente-> %p\n", p, p->dato, p->sig);
        listar(p->sig);
    }
}

void vaciar(nodo **p)
{
    nodo *aux;
    while(*p!=NULL)
    {
        aux=*p;
        *p=(*p)->sig;
        free(aux);
    }
}

nodo *verificar(nodo *p)
{
    if(p == NULL){
        system("cls");
        printf("\nCola vacia mmmmmmmm...\n");
        printf("\nPresione una tecla para continuar...");
        getch();
    }
    return (p);
}

nodo ingresar_dato(void)
{
    nodo r;
    system("cls");
    printf("\nIngrese el dato(numero): ");
    s("%d", &r.dato);
    return (r);
}

void dato_eliminado(nodo r)
{
    system("cls");
    printf("\nEl dato eliminado es: %d\n", r.dato);
    printf("\nPresione una tecla para continuar...");
    getch();
}

void guardarEnArchivo(nodo *p, FILE *archivoDatos)
{
    archivoDatos=fopen("datos.dat", "wb");
    if(archivoDatos != NULL){
        while(p != NULL)
        {
            nodoDato elDato = {p->dato};
            fwrite(&elDato, sizeof(nodoDato), 1, archivoDatos);
            p = p->sig;
        }
        fclose(archivoDatos);
    }
    else{
        printf("\nError al abrir el archivo\n");
    }
}

void leerArchivo(FILE *archivoDatos){
    nodoDato elDato;
    archivoDatos=fopen("datos.dat", "rb");
    if(archivoDatos!=NULL){
        while(fread(&elDato, sizeof(nodoDato), 1, archivoDatos))
        {
            printf("\tDato:%d \n", elDato.dato);
        }
        fclose(archivoDatos);
    }
    else{
        printf("\nError al abrir el archivo\n");
    }
}

