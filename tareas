#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct tarea {
    char descripcion[MAX];
    struct tarea *next;
} tarea_t;


tarea_t *agregar_tarea(tarea_t *lista);
void mostrar_tareas(tarea_t *lista);
void liberar(tarea_t *lista);



int main() {
    tarea_t *mi_lista = NULL;
    int opcion;

    do {
        printf("\nmenu\n");
        printf("1. agregar tarea\n");
        printf("2. vver tareas\n");
        printf("3. salir\n");
        printf("Elegi una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                mi_lista = agregar_tarea(mi_lista);
                break;
            case 2:
                mostrar_tareas(mi_lista); 
            break;

            case 3:
                liberar(mi_lista); //
                printf("fin"\n");
                break;
            default:
                printf("Opción invalida\n");
        }

    } while (opcion != 3);

    return 0;
}





tarea_t *agregar_tarea(tarea_t *lista) {
    tarea_t *nueva = (tarea_t *)malloc(sizeof(tarea_t));
    if (nueva == NULL) {
        printf("Error memoria\n");
        return lista;
    }

    printf("Ingresá la descripción de la tarea: ");
    fgets(nueva->descripcion, MAX, stdin);
    nueva->descripcion[strcspn(nueva->descripcion, "\n")] = 0;
    nueva->next = lista; // se agrega al principiop
    printf("Tarea agregada!\n");

    return nueva;
}

void mostrar_tareas(tarea_t *lista) {
    if (lista == NULL) {
        printf("No hay tareas.\n");
        return;
    }

    printf("\nTareas\n");
    while (lista != NULL) { //el null porq si es opuesto significa que tiene algo
        printf("- %s\n", lista->descripcion);
        lista = lista->next;
    }
}

void liberar(tarea_t *lista) {
    tarea_t *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}
