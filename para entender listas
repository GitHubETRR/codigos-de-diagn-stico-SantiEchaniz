#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Definición del nodo
struct inventario {
    char producto[MAX];
    int cantidad;
    float precio;
    struct inventario* siguiente;
};

// Prototipos
void imprimiropciones();
void buscarproducto(struct inventario* head);
void imprimirproductos(struct inventario* head);

int main() {
    int ingreso;
    char rta;
    char sep;
    struct inventario* head = NULL;

    do {
        imprimiropciones();
        scanf("%d", &ingreso);

        switch (ingreso) {
            case 1:
                do {
                    struct inventario* nuevo = (struct inventario*)malloc(sizeof(struct inventario));
                    if (!nuevo) {
                        printf("Error de memoria.\n");
                        return 1;
                    }

                    printf("\nIngresa el nombre del producto en minúsculas: ");
                    scanf(" %[^\n]", nuevo->producto);

                    printf("Ahora ingrese el stock de ese producto: ");
                    scanf("%d", &nuevo->cantidad);

                    printf("Ahora ingrese el precio de ese producto: ");
                    scanf("%f", &nuevo->precio);

                    nuevo->siguiente = head;  // Insertar al inicio
                    head = nuevo;

                    printf("\n¿Quiere seguir agregando productos? (s/n): ");
                    scanf(" %c", &rta);

                } while (rta == 's');
                break;

            case 2:
                buscarproducto(head);
                break;

            case 3:
                imprimirproductos(head);
                break;

            default:
                printf("Lo ingresado no está en los valores especificados.\n");
                break;
        }

        printf("\n¿Quiere seguir usando el programa? (s/n): ");
        scanf(" %c", &sep);

    } while (sep == 's');

    // Liberar memoria
    struct inventario* actual = head;
    while (actual != NULL) {
        struct inventario* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }

    return 0;
}

void imprimiropciones() {
    printf("\n¿Qué quieres hacer?");
    printf("\n1. Agregar producto");
    printf("\n2. Buscar producto");
    printf("\n3. Imprimir todos los productos y sus stocks y precios");
    printf("\nOpción: ");
}

void buscarproducto(struct inventario* head) {
    char nombre[MAX];
    int encontrado = 0;

    printf("\nIngresá el nombre del producto que querés buscar: ");
    scanf(" %[^\n]", nombre);

    while (head != NULL) {
        if (strcmp(head->producto, nombre) == 0) {
            printf("\nProducto encontrado:");
            printf("\nNombre: %s", head->producto);
            printf("  Cantidad: %d", head->cantidad);
            printf("  Precio: %.2f\n", head->precio);
            encontrado = 1;
            break;
        }
        head = head->siguiente;
    }

    if (!encontrado) {
        printf("\nProducto no encontrado.\n");
    }
}

void imprimirproductos(struct inventario* head) {
    if (head == NULL) {
        printf("\nNo hay productos ingresados todavía.\n");
        return;
    }

    printf("\nLista de productos ingresados:\n");
    while (head != NULL) {
        printf("\nProducto: %s", head->producto);
        printf("  Cantidad: %d", head->cantidad);
        printf("  Precio: %.2f\n", head->precio);
        head = head->siguiente;
    }
}

        printf("  Cantidad: %d", head->cantidad);
        printf("  Precio: %.2f\n", head->precio);
        head = head->siguiente;
    }
}
