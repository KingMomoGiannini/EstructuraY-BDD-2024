#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nombre[30];
    int cantidad;
    int precio;
} Producto;

typedef struct nodo {
    char nombre[30];
    int cantidad;
    struct nodo *sig;
} Nodo;

Nodo *nuevoNodo(char *nombre, int cantidad){
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    strcpy(nuevo->nombre, nombre);
    nuevo->cantidad = cantidad;
    nuevo->sig = NULL;
    return nuevo;
}

void insertarNodo(Nodo **lista, char *nombre, int cantidad) {
    Nodo *nuevo = nuevoNodo(nombre, cantidad);
    nuevo->sig = *lista;
    *lista = nuevo;
}

int menu(void) {
    int opcion;
    printf("Menu de Opciones:\n");
    printf("1. Cargar productos en el archivo\n");
    printf("2. Cargar lista de compras\n");
    printf("3. Ver lista de compras\n");
    printf("4. Ver stock de productos\n");
    printf("5. Realizar compra\n");
    printf("6. Ver productos que no se pudieron comprar\n");
    printf("7. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void cargarProductos(FILE *archivo) {
    Producto productos[] = {
        {1102, "Leche", 150, 500},
        {1103, "Manteca", 50, 300},
        {1104, "Polenta", 230, 400},
        {1105, "Vino", 340, 500},
        {1106, "Fideos", 200, 600},
        {1107, "Aceite", 0, 400},
        {1108, "Arroz", 345, 300},
        {1109, "Yogur", 60, 400}
    };
    int cantidad = sizeof(productos) / sizeof(productos[0]);

    fwrite(productos, sizeof(Producto), cantidad, archivo);
    printf("Productos cargados en el archivo con éxito.\n");
    system("pause");
    system("cls");
}

void verStock(FILE *archivo) {
    Producto producto;
    rewind(archivo);
    printf("Stock de Productos:\n");
    printf("Codigo\tNombre\t\tCantidad\tPrecio\n");
    while (fread(&producto, sizeof(Producto), 1, archivo)) {
        printf("%d\t%-10s\t%d\t\t$ %d\n", producto.codigo, producto.nombre, producto.cantidad, producto.precio);
    }
    system("pause");
    system("cls");
}

void verLista(Nodo *cabeza) {
    Nodo *actual = cabeza;
    printf("Lista de Compras:\n");
    while (actual != NULL) {
        printf("%s\t%d\n", actual->nombre, actual->cantidad);
        actual = actual->sig;
    }
    system("pause");
    system("cls");
}

/*Listar nombres de productos como menu de opciones*/
char *menuProductos(int opcion) {
    char *nomProducto;
    do{
        switch (opcion) {
            case 1:
                nomProducto = "Arroz"; // "Arroz";
                break;
            case 2:
                nomProducto = "Aceite";
                break;
            case 3:
                nomProducto = "Leche";
                break;
            case 4:
                nomProducto = "Manteca";
                break;
            case 5:
                nomProducto = "Fideos";
                break;
            case 6:
                nomProducto = "Manzana";
                break;
            case 7:
                nomProducto = "Polenta";
                break;
            case 8:
                nomProducto = "Vino";
                break;
            case 9:
                nomProducto = "Yogur";
                break;
            default:
                printf("Opcion incorrecta, SE ROMPIO TODOOOOO.\n");
                system("pause");
                system("cls");
                break;
        }
    } while (opcion < 1 || opcion > 9);
    return nomProducto;
}

void enumProductos() {
    printf("1. Arroz\n");
    printf("2. Aceite\n");
    printf("3. Leche\n");
    printf("4. Manteca\n");
    printf("5. Fideos\n");
    printf("6. Manzana\n");
    printf("7. Polenta\n");
    printf("8. Vino\n");
    printf("9. Yogur\n");
}

/*Lista de Compras*/
void cargarLista(Nodo **lista) {
    Nodo *nuevo, *actual;
    char nombre[30];
    int cantidad, opcion;
    printf("Ingrese el nombre del producto: \n");
    enumProductos();
    fflush(stdin);
    scanf("%d", &opcion);
    strcpy(nombre, menuProductos(opcion));
    printf("Ingrese la cantidad: ");
    scanf("%d", &cantidad);
    insertarNodo(&(*lista), nombre, cantidad);
    system("pause");
    system("cls");
}

//Comprar productos de la lista de compras
void comprarProductos(FILE *archivo, Nodo **lista, int *costoTotal, int *stockInsuficiente, int *productoNoDisponible) {
    Producto producto;
    Nodo *actual = *lista, *anterior = NULL;
    archivo = fopen("productos.dat", "r+b");
    while (actual != NULL) {
        rewind(archivo);
        while (fread(&producto, sizeof(Producto), 1, archivo)) { //leo el archivo de productos
            if (strcmp(producto.nombre, actual->nombre) == 0) { //si el producto a comprar esta en el archivo
                if (producto.cantidad >= actual->cantidad) { //y si hay stock suficiente
                    *costoTotal += producto.precio * actual->cantidad;//calculo el costo total de la cantidad de productos que tengo en la lista
                    producto.cantidad -= actual->cantidad; //resto la cantidad de productos comprados al stock
                    fseek(archivo, -sizeof(Producto), SEEK_CUR); //me posiciono en el producto que quiero modificar
                    fwrite(&producto, sizeof(Producto), 1, archivo); //modifico el stock del producto en el archivo de productos
                    if (anterior == NULL) { //si el producto a comprar es el primero de la lista
                        *lista = actual->sig; //actualizo la lista
                        free(actual); 
                        actual = *lista;
                    } else {
                        anterior->sig = actual->sig; //si el producto a comprar no es el primero de la lista
                        free(actual);
                        actual = anterior->sig; //actualizo la lista
                    }
                } else {  //si no hay stock suficiente
                    *stockInsuficiente = 1; //aviso que no se pudo comprar uno o mas productos por stock insuficiente
                    actual = actual->sig; //actualizo la lista
                }
                break;
            }
            else if (strcmp(producto.nombre, actual->nombre) == 1) { //si el producto a comprar no esta en el archivo
                *productoNoDisponible = 1;
            }
        }
        
    }
    fclose(archivo);
}



int main() {
    FILE *archivo;
    Nodo *lista = NULL,*actual, *noCompra = NULL;
    Producto producto;
    int opcion, costoTotal = 0, stockInsuficiente = 0, productoNoDisponible = 0;
    system("cls");
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                archivo = fopen("productos.dat", "w+b");
                if (archivo != NULL){
                    cargarProductos(archivo);
                    fclose(archivo);
                }
                else{
                    printf("No se pudo abrir el archivo.\n");
                }
                break;
            case 2:
                cargarLista(&lista);
                break;
            case 3:
                verLista(lista);
                break;
            case 4:
                archivo = fopen("productos.dat", "r+b");
                if(archivo!=NULL){
                    verStock(archivo);
                    fclose(archivo);
                }
                else{
                    printf("No se pudo abrir el archivo.\n");
                }
                break;
            case 5:
                actual = lista;
                if(actual != NULL){
                    comprarProductos(archivo, &lista, &costoTotal, &stockInsuficiente, &productoNoDisponible);
                }
                break;
            case 6:
                if (stockInsuficiente == 1) {
                    printf("No se pudo comprar uno o mas productos por stock insuficiente.\n");
                }
                if (productoNoDisponible == 1) {
                    printf("No se pudo comprar uno o mas productos porque no estan disponibles en el supermercado.\n");
                    free(lista);
                }
                system("pause");
                system("cls");
                break;
        }
    } while (opcion != 7);
    printf("Costo total de la compra: $ %d\n", costoTotal);
    return 0;
}

