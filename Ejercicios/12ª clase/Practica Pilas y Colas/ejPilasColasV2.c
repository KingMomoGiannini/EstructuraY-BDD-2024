/*Programa basado en la misma consigna.
En esta versión, el ejercicio está bien realizado*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct cliente {
    int id;
    char nombre[50];
    int accion; // 1 = compra, 2 = devolución
    struct cliente *sig;
} Cliente;

typedef struct producto {
    int id_producto;
    struct producto *ptr;
} Producto;

void ingresarCliente(Cliente *cliente);
void acolar(Cliente cliente, Cliente **cola);
void desacolar( Cliente **cola);
void apilar(int idProducto, Producto **pila);
void desapilar( Producto **pila);
void listarCola( Cliente *cola);
void listarPila( Producto *pila);
void procesarDevoluciones(Producto **pila);
int menu(void);

int main(){
    Cliente elCliente,*cola = NULL; 
    Producto *pila = NULL;
    int op, id_producto;
    do {
        op = menu();
        switch (op) {
            case 1:
                ingresarCliente(&elCliente);
                acolar(elCliente, &cola);
                break;
            case 2:
                if (cola == NULL) {
                    printf("COLA VACIA!!\n");
                    system("pause");
                } else {
                    printf("Cliente Atendido - ID: %d, Nombre: %s, Accion: %s\n", cola->id, cola->nombre, cola->accion == 1 ? "Compra" : "Devolucion");
                    if (cola->accion == 2) {
                        printf("Ingrese ID del Producto Devuelto: ");
                        scanf("%d", &id_producto);
                        apilar(id_producto, &pila);
                    }
                    desacolar(&cola);
                    system("pause");
                }
                break;
            case 3:
                listarCola(cola);
                break;
            case 4:
                while (cola != NULL) {
                    desacolar(&cola);
                }
                break;
            case 5:
                listarPila(pila);
                break;
            case 6:
                procesarDevoluciones(&pila);
                break;
        }
    } while (op != 7);
    return 0;
}

void ingresarCliente(Cliente *cliente){
    printf("Ingrese ID del Cliente: ");
    scanf("%d", &cliente->id);
    printf("Ingrese Nombre del Cliente: ");
    fflush(stdin);
    gets(cliente->nombre);
    printf("Ingrese Accion del Cliente (1=Compra, 2=Devolucion): ");
    scanf("%d", &cliente->accion);
}

void acolar(Cliente cliente, Cliente **cola) {
    Cliente *nuevo = (Cliente *)malloc(sizeof(Cliente));
    nuevo->id = cliente.id;
    strcpy(nuevo->nombre, cliente.nombre);
    nuevo->accion = cliente.accion;
    nuevo->sig = NULL;
    if (*cola == NULL) {
        *cola = nuevo;
    } else {
        Cliente *aux = *cola;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

void desacolar(Cliente **cola) {
    if (*cola == NULL) {
        printf("COLA VACIA!!\n");
        system("pause");
    } else {
        Cliente *aux = *cola;
        *cola = (*cola)->sig;
        free(aux);
    }
}

void apilar(int id_producto, Producto **pila) {
    Producto *nuevo = (Producto *)malloc(sizeof(Producto));
    nuevo->id_producto = id_producto;
    nuevo->ptr = *pila;
    *pila = nuevo;
}

void desapilar( Producto **pila) {
    if (pila == NULL) {
        printf("PILA VACIA\n");
        system("pause");
    } else {
        Producto *aux = *pila;
        *pila = (*pila)->ptr;
        free(aux);
    }
}

void listarCola( Cliente *cola) {
    if (cola == NULL) {
        printf("COLA VACIA!!\n");
        system("pause");
    } else {
        Cliente *aux = cola;
        printf("Clientes en Cola:\n");
        while (aux != NULL) {
            printf("ID: %d, Nombre: %s, Accion: %s\n", aux->id, aux->nombre, aux->accion == 1 ? "Compra" : "Devolucion");
            aux = aux->sig;
        }
        system("pause");
    }
}

void listarPila( Producto *pila) {
    if (pila == NULL) {
        printf("PILA VACIA\n");
    } else {
        Producto *aux = pila;
        printf("Productos en la Pila de Devoluciones:\n");
        while (aux != NULL) {
            printf("ID Producto: %d\n", aux->id_producto);
            aux = aux->ptr;
        }
        system("pause");
    }
}

void procesarDevoluciones( Producto **pila) {
    printf("Procesando Devoluciones...\n");
    while (*pila != NULL) {
        printf("ID Producto: %d\n", (*pila)->id_producto);
        desapilar(&(*pila));
    }
    printf("Devoluciones procesadas.\n");
    system("pause");
}

int menu(void) {
    int op;
    do {
        printf("\nMENU DE OPCIONES\n");
        printf("1- Ingresar Cliente (Cola)\n");
        printf("2- Atender Cliente\n");
        printf("3- Listar Clientes en Cola\n");
        printf("4- Vaciar Cola de Clientes\n");
        printf("5- Listar Productos en la Pila de Devoluciones\n");
        printf("6- Procesar Devoluciones\n");
        printf("7- Salir\n");
        printf("Ingrese Opcion: ");
        scanf("%d", &op);
    } while (op < 1 || op > 7);
    return op;
}