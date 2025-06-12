#include <stdio.h>
#include <string.h>

#define MAX 50
#define cant_pers 5
#define Agregarpdrt 1
#define Buscarpdrt 2
#define Imprimir 3
#define Salir 4


struct inventario{
    char producto[MAX];
    int cantidad;
    float precio;
};
    

int imprimiropciones(void);
void agregarproducto(struct inventario inventario[], int *i);
void buscarproducto(struct inventario inventario[], int i);
void imprimirproductos(struct inventario inventario[], int i);



int main()
{
    int ingreso;
    int i = 0;
    char sep;
    struct inventario inventario[cant_pers];
    do{
        ingreso=imprimiropciones();
        switch (ingreso){
            case Agregarpdrt: 
                agregarproducto(inventario, &i);
            break;
                
            case Buscarpdrt:
                buscarproducto(inventario, i);
            break;
                
            case Imprimir:
                imprimirproductos(inventario, i);
            break;
                
            case Salir:
            break;
                
            default:
                printf("Lo ingresado no está en los valores especificados");
            break;
        }
        
        printf("\n ¿Quiere seguir usando el programa? (s-n)");
        scanf(" %c", &sep);
    }while (sep=='s');

    return 0;
}




int imprimiropciones() {
    int ingreso;
    printf("\n\n¿Que queres hacer?"); 
    printf("\n 1. Agregar producto");
    printf("\n 2. Buscar producto");
    printf("\n 3. Imprimir todos los productos y sus stocks y precios");
    printf("\n 4. Salir");
    printf("\nOpcion: ");
    scanf("%d", &ingreso);
    while (getchar() != '\n');
    return ingreso;
}



void agregarproducto(struct inventario inventario[], int *i){
    char rta;
    do{
        printf("\nIngresa el nombre del producto en minusculas: ");
        scanf("\n %[^\n]", inventario[*i].producto);
        printf("\nAhora ingrese el stock de ese producto: ");
        scanf("%d", &inventario[*i].cantidad);
        printf("\nAhora ingrese el precio de ese producto: ");
        scanf("%f", &inventario[*i].precio);
        i++;
        printf("\n¿Quiere seguir agregando productos? s o n");
        scanf(" %c", &rta);
    }while(rta=='s');
}



void buscarproducto(struct inventario inventario[], int i) {
    char nombre[MAX];
    int encontrado =0;

    printf("\nIngresá el nombre del producto que queres buscar: ");
    scanf(" %[^\n]", nombre);

    for (int b = 0; b < i; b++) {
        if (strcmp(inventario[b].producto, nombre) == 0) { //para comparar palabras busque en internet y encontré strcmp(), que es una función de la biblioteca string que compara dos cadenas de caracteres y devuelve 0 si son iguales
            printf("\nProducto encontrado:");
            printf("\nNombre: %s", inventario[b].producto);
            printf("  Cantidad: %d", inventario[b].cantidad);
            printf("  Precio: %.2f\n", inventario[b].precio);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nproducto no encontrado\n");
    }
}


void imprimirproductos(struct inventario inventario[], int i){
    if (i == 0) {
                printf("\nNo hay productos ingresados todavia\n");
    }else {
        printf("\nLista de productos ingresados:\n");
        for (int a = 0; a < i; a++) {
            printf("\nProducto: %s", inventario[a].producto);
            printf("  Cantidad: %d", inventario[a].cantidad);
            printf("  Precio: %f\n", inventario[a].precio);
        }
    }
}
