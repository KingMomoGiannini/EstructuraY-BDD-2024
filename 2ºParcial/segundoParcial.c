#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define p printf
#define s scanf

typedef struct
{
    long int cod;
    char desc[25];
    int cant;
    float pre;
} registro;

typedef struct elemento
{
    registro datos;
    struct elemento *sig;
} nodo;

void cargapila(nodo **, registro[], int);
nodo *ingresarDato(int, registro[]);    
void apilar(nodo **, nodo *);
void mostrar(nodo *);
void mostrarArchivo(FILE *);
int menu(void);
void agregarDatos(nodo **, nodo *);
void cargarArchivo(FILE *, nodo *);
void liberarPila(nodo **);

int main()
{
    system("cls");
    registro info[] = {
        {100235, "Nebulizador", 50, 145.20},
        {100312, "Tensiometro", 120, 159.35},
        {200045, "Caloventor", 35, 46.00},
        {200511, "Estufa halogena", 15, 72.58},
        {400805, "Afeitadora", 100, 215.40},
        {400322, "Cortadora de Cabello", 210, 29.45}    
    };

    registro infocom[] = {
        {500100, "Reproductor de DVD", 24, 200.53},
        {100312, "Tensiometro", 50, 159.35},
        {500235, "Televisor 21", 30, 565.60},
        {200511, "Estufa halogena", 30, 72.58}
    };
    FILE *arch;
    nodo *PilaOriginal = NULL, *PilaCompras = NULL;
    int op;
    do
    {
        op = menu();
        switch (op)
        {
            case 1:
                cargapila(&PilaOriginal, info, 6);
                cargapila(&PilaCompras, infocom, 4);
                break;
            case 2:
                agregarDatos(&PilaOriginal, PilaCompras);
                break;
            case 3:
                p("\n\nCONTENIDO DE LA PILA ORIGINAL !!!\n\n");
                mostrar(PilaOriginal);
                p("\n\nCONTENIDO DE LA PILA DE COMPRAS\n\n");
                mostrar(PilaCompras);
                break;
            case 4:
                cargarArchivo(arch, PilaOriginal);
                mostrarArchivo(arch);
                break;
            case 5:
                liberarPila(&PilaOriginal);
                liberarPila(&PilaCompras);
                break;
        }
    } while (op != 5);
    return 0;
}

void cargapila(nodo **x, registro y[], int z)
{
    int i;
    nodo *q;
    for (i = 0; i < z; i++)
    {
        q = ingresarDato(i, y);
        apilar(&(*x), q);
    }
}

nodo *ingresarDato(int i, registro y[])
{
    nodo *q;
    q = (nodo *)malloc(sizeof(nodo));
    q->datos = y[i];
    q->sig = NULL;
    return q;
}

void apilar(nodo **x, nodo *y)
{
    y->sig = *x;
    *x = y;
}

void mostrar(nodo *x)
{
    while (x)
    {
        p("\n\n%ld\t\t%s\t%6d\t\t\t%6.2f", x->datos.cod, x->datos.desc, x->datos.cant, x->datos.pre);
        x = x->sig;
    }
    p("\n\n");
    system("pause");
}

int menu(void)
{
    int op;
    do
    {
        system("cls");
        p("\n\t\t\t\t MENU DE OPCIONES (PILAS)\n\n");
        p("\n\t\t\t - CARGAR  DATOS     <1>");
        p("\n\t\t\t - AGREGAR DATOS     <2>");
        p("\n\t\t\t - LISTAR DATOS      <3>");
        p("\n\t\t\t - CARGAR EN ARCHIVO <4>");
        p("\n\t\t\t - BORRAR Y SALIR    <5>");
        p("\n\t\t\t - INGRESE OPCION [1-5]:  ");
        s("%d", &op);
    } while (op < 1 || op > 5);
    return op;
}

void mostrarArchivo(FILE *x)
{
    x = fopen("articulos.dat", "rb");
    registro r;
    p("\n\t\t CONTENIDO DE LOS REGISTROS EN EL ARCHIVO\n\n");
    p("\n\n Codigo\t\tNombre\t\t\tCantidad\t\tPrecio\n\n");
    rewind(x);
    fread(&r, sizeof(r), 1, x);
    while (!feof(x))
    {
        p("\n\n%ld\t\t%s\t%6d\t\t\t%6.2f", r.cod, r.desc, r.cant, r.pre);
        fread(&r, sizeof(r), 1, x);
    }
    fclose(x);
    system("pause");
}

void liberarPila(nodo **pila)
{
    nodo *aux;
    while (*pila)
    {
        aux = *pila;
        *pila = (*pila)->sig;
        free(aux);
    }
}

void cargarArchivo(FILE *arch, nodo *pila)
{
    arch = fopen("articulos.dat", "wb");
    if (arch != NULL)
    {
        while (pila)
        {
            fwrite(&pila->datos, sizeof(registro), 1, arch);
            pila = pila->sig;
        }
    }
    else
    {
        p("Error al abrir el archivo\n");
    }
    fclose(arch);
}

void agregarDatos(nodo **pilaOriginal, nodo *pilaCompras)
{
    nodo *auxOriginal = *pilaOriginal;
    nodo *auxCompras = pilaCompras;
    nodo *nuevoNodo;
    int encontrado = 0;

    while (auxCompras)
    {
        while (auxOriginal)
        {
            if (auxCompras->datos.cod == auxOriginal->datos.cod)
            {
                auxOriginal->datos.cant += auxCompras->datos.cant;
                encontrado = 1;
                break;
            }
            auxOriginal = auxOriginal->sig;
        }

        if (!encontrado)
        {
            nuevoNodo = (nodo *)malloc(sizeof(nodo));
            if (nuevoNodo == NULL)
            {
                p("Error al asignar memoria\n");
                return;
            }

            nuevoNodo->datos = auxCompras->datos;
            nuevoNodo->sig = *pilaOriginal;
            *pilaOriginal = nuevoNodo;
        }

        encontrado = 0;
        auxCompras = auxCompras->sig;
    }
}