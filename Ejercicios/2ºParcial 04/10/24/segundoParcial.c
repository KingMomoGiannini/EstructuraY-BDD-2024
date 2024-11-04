/*Alumnos Rodas Thomas; Gilardenghi Matias; Giannini Sebastián */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LISTAS 5 
#define MAX_CADENA 81  
#define MAX_PROVINCIAS 3 
#define MAX_DISTRITOS 4 

typedef struct {
    int prov;
    int distrito;
    int lista;
    int votos;
} registro;

typedef struct elemento {
    int lista; 
    int votos; 
    struct elemento *sig;
} nodo;


void cargar(FILE* archivo, registro reg, FILE* binario);
void mostrar(FILE* archivo);
const char* obtenerNombreProvincia(int prov);
const char* obtenerNombreDistrito(int prov, int dis);
const char* obtenerNombreCandidato(int lista);
void liberarMemoria(nodo *);
void manejarErrorArchivo(FILE *, const char *);
int menu();
void buscar(FILE* , int , int , int );
void imprimeGeneral(FILE* archivo);
void insertar(nodo**,int,int);
void listar(nodo*);
void cargarListaEnlazada(FILE* , nodo**);
void mostrarListaEnlazada(nodo* cabeza);

int main() {
    FILE *archivo, *binario;
    char nombre[] = "../Votos.txt";
    char *nombin = "datos.dat";
    nodo *cabeza = NULL;
    registro reg;
    system("color 9f");

    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                archivo = fopen(nombre, "r");    
                manejarErrorArchivo(archivo, nombre);
                binario = fopen(nombin, "wb+");
                manejarErrorArchivo(binario, nombin);
                cargar(archivo, reg, binario);
                fclose(archivo);
                fclose(binario);
                break;
            case 2:
                binario = fopen(nombin, "rb");
                manejarErrorArchivo(binario, nombin);
                mostrar(binario);
                fclose(binario);
                break;
            case 3:
                binario = fopen("datos.dat", "rb");
                manejarErrorArchivo(binario, "datos.dat");
                int provincia, distrito, lista;
                printf("Ingrese Nº de Provincia[1-3]: ");
                scanf("%d", &provincia);
                printf("Ingrese Nº de Distrito[1-4]: ");
                scanf("%d", &distrito);
                printf("Ingrese Nº de Lista [1-5]: ");
                scanf("%d", &lista);
                buscar(binario, provincia, distrito, lista);
                break;
            case 4:
                binario = fopen("datos.dat", "rb");
                imprimeGeneral(binario);
                fclose(binario);
                break;
            case 5:
                binario= fopen("datos.dat","rb");
                cargarListaEnlazada(binario,&cabeza);
                fclose(binario);
                break;
            case 6:
                mostrarListaEnlazada(cabeza);
                break;
            case 7:
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 7);

    liberarMemoria(cabeza);

    return 0;
}

void cargar(FILE* archivo, registro reg, FILE *binario) {
    int provincia, distrito, lista, aux;
    rewind(archivo); 

    while (fscanf(archivo, "%d", &aux) != EOF) {
        provincia = aux / 100;          
        distrito = (aux % 100) / 10;      
        lista = aux % 10;                 
        reg.prov = provincia;
        reg.distrito = distrito;
        reg.lista = lista;
        reg.votos = 1;

        registro temp;
        int encontrado = 0;
        rewind(binario); 
        while (fread(&temp, sizeof(registro), 1, binario)) {
            if (temp.prov == reg.prov && temp.distrito == reg.distrito && temp.lista == reg.lista) {
                temp.votos += 1;
                fseek(binario, -sizeof(registro), SEEK_CUR);
                fwrite(&temp, sizeof(registro), 1, binario);
                encontrado = 1;
                break;
            }
        }
        
        if (!encontrado) {
            fseek(binario, 0, SEEK_END); 
            fwrite(&reg, sizeof(registro), 1, binario);
        }
    }
}

void mostrar(FILE* archivoBinario) {
    registro reg;
    rewind(archivoBinario);
    printf("Provincia\tDistrito\tLista\tVotos\n");
    while (!feof(archivoBinario)) {
        fread(&reg, sizeof(registro), 1, archivoBinario);
        printf("%s\t\t%s\t\t%s\t%d\n", obtenerNombreProvincia(reg.prov-1), obtenerNombreDistrito(reg.prov-1, reg.distrito-1), obtenerNombreCandidato(reg.lista-1), reg.votos);
    }
}

const char* obtenerNombreProvincia(int prov) {
    static const char* provincias[MAX_PROVINCIAS] = {"Buenos Aires", "Santa Fe", "Cordoba"};
    return (prov >= 0 && prov < MAX_PROVINCIAS) ? provincias[prov] : "Desconocida";
}

const char* obtenerNombreDistrito(int prov, int dis) {
    static const char* distritos[MAX_PROVINCIAS][MAX_DISTRITOS] = {
        {"La Plata", "Mar del Plata", "Lanús", "Lomas de Zamora"},
        {"Rosario", "Rafaela", "Venado Tuerto", "Reconquista"},
        {"Río Cuarto", "Villa Maria", "San Francisco", "Carlos Paz"}
    };
    return (prov >= 0 && prov < MAX_PROVINCIAS && dis >= 0 && dis < MAX_DISTRITOS) ?
        distritos[prov][dis] : "Desconocido";
}

const char* obtenerNombreCandidato(int lista) {
    static const char* candidatos[NUM_LISTAS] = {"Juan Gonzalez", "Marcos Alvarez", "Ana Lopez", "Nicolas Ramirez", "Sofia Flores"};
    return (lista >= 0 && lista < NUM_LISTAS) ? candidatos[lista] : "Desconocido";
}

void liberarMemoria(nodo *cabeza) {
    while (cabeza != NULL) {
        nodo *temp = cabeza;
        cabeza = cabeza->sig;
        free(temp);
    }
}

void manejarErrorArchivo(FILE *archivo, const char *nombre) {
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombre);
        exit(1);
    }
}

int menu() {
    int opcion;
    printf("\n\n********* MENU PRINCIPAL *********\n");
    printf("1. Cargar datos desde archivo de texto\n");
    printf("2. Mostrar registros del archivo binario\n");
    printf("3. Buscar datos por provincia, distrito y lista\n");
    printf("4. Mostrar resultado general de votos\n");
    printf("5. Ingresar Resultados a la lista Enlazada\n");
    printf("6. Mostrar la lista Enlazada\n");
    printf("7. Salir\n");
    printf("**********************************\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void buscar(FILE* archivo, int provincia, int distrito, int lista) {
    registro reg;
    rewind(archivo);
    int encontrado = 0;
    printf("Provincia\t\t\tDistrito\t\t\tLista\t\t\tVotos\n\n");
    while (fread(&reg, sizeof(registro), 1, archivo)) {
        if (reg.prov == provincia && reg.distrito == distrito && reg.lista == lista) {
            printf("%s\t\t\t%s\t\t\t%s\t\t\tvotos: %d\n", obtenerNombreProvincia(reg.prov-1), obtenerNombreDistrito(reg.prov-1,reg.distrito-1), obtenerNombreCandidato(reg.lista-1), reg.votos);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron resultados para la provincia %d, distrito %d y lista %d\n", provincia, distrito, lista);
    }
}

void imprimeGeneral(FILE* archivo){
    registro reg;
    rewind(archivo);
    int votos[NUM_LISTAS] = {0};
    while (fread(&reg, sizeof(registro), 1, archivo)) {
        votos[reg.lista-1] += reg.votos;
    }
    int i, j, aux;
    for (i = 0; i < NUM_LISTAS - 1; i++) {
        for (j = i + 1; j < NUM_LISTAS; j++) {
            if (votos[i] < votos[j]) {
                aux = votos[i];
                votos[i] = votos[j];
                votos[j] = aux;
            }
        }
    }
    printf("Lista\t\tVotos\n");
    for (i = 0; i < NUM_LISTAS; i++) {
        printf("%s\t\t%d\n", obtenerNombreCandidato(i), votos[i]);
    }
}

void insertar(nodo** cabeza, int lista, int votos) {
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->lista = lista;
    nuevo->votos = votos;
    nuevo->sig = *cabeza;
    *cabeza = nuevo;
}

void listar(nodo* cabeza) {
    nodo *actual = cabeza;
    printf("Lista\t\tVotos\n");
    while (actual != NULL) {
        printf("%s\t\t%d\n", obtenerNombreCandidato(actual->lista), actual->votos);
        actual = actual->sig;
    }
}

void cargarListaEnlazada(FILE *archivo, nodo** cabeza) {
    registro reg;
    rewind(archivo);
    int votos[NUM_LISTAS] = {0};
    while (fread(&reg, sizeof(registro), 1, archivo)) {
        votos[reg.lista-1] += reg.votos;
    }
    int i;
    for (i = 0; i < NUM_LISTAS; i++) {
        insertar(cabeza, i, votos[i]);
    }
}

void mostrarListaEnlazada(nodo* cabeza) {
    listar(cabeza);
}
