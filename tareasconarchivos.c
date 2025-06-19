#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define agregar 1
#define mostrar 2
#define hecho 3
#define reestablecer 4

typedef struct tarea {
    char materia[MAX];
    char descripcion[MAX];
    struct tarea *next;
} tarea_t;

int ingreso(void);
tarea_t *agregar_tarea(tarea_t *lista);
void mostrar_tareas(tarea_t *lista);
void tareahecha(tarea_t **lista);
void liberar(tarea_t *lista);



int main() {
    tarea_t *mi_lista = NULL;
    int opcion;

    do {
        opcion = ingreso();
    
        switch (opcion) {
            case agregar:
                mi_lista = agregar_tarea(mi_lista);
            break;
                
            case mostrar:
                mostrar_tareas(mi_lista); 
            break;
            
            case hecho:
                tareahecha(&mi_lista);
            break;

            case reestablecer:
                liberar(mi_lista);
                printf("Fin\n");
                break;
            default:
                printf("Opción invalida\n");
        }

    } while (opcion != reestablecer);

    return 0;
}



int ingreso() {
    int opcion;
    printf("\nMenu\n");
    printf("1. Agregar tarea\n");
    printf("2. Ver tareas\n");
    printf("3. Tarea hecha\n");
    printf("4. Salir\n");
    printf("Elegi una opción: ");
    scanf("%d", &opcion);
    getchar();
    return opcion;
}



tarea_t *agregar_tarea(tarea_t *lista){
    tarea_t *nueva = (tarea_t *)malloc(sizeof(tarea_t));
    if (nueva == NULL) {
        printf("Error memoria\n");
        
        return lista;
    }
    printf("De que materia es esa tarea: ");
    fgets(nueva->materia, MAX, stdin);
    nueva->materia[strcspn(nueva->materia, "\n")] = 0;
    printf("Ingresá la descripción de la tarea: ");
    fgets(nueva->descripcion, MAX, stdin);
    nueva->descripcion[strcspn(nueva->descripcion, "\n")] = 0;
    nueva->next = lista; // se agrega al principiop
    printf("Tarea agregada!\n");
    
    return nueva;
}


void mostrar_tareas(tarea_t *lista){
    FILE *archivo = fopen("C:\\Users\\sechaniz\\Desktop\\TAREASSANTU\\tareas.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo crear el archivo\n");
        return;
    }

    if (lista == NULL) {
        printf("No hay tareas.\n");
        fprintf(archivo, "No hay tareas.\n");
        fclose(archivo);
        return;
    }

    printf("\nTareas\n");
    fprintf(archivo, "Tareas:\n");

    while (lista != NULL) {
        printf("- %s:     %s\n", lista->materia, lista->descripcion);
        fprintf(archivo, "- %s:     %s\n", lista->materia, lista->descripcion);
        lista = lista->next;
    }

    fclose(archivo);
    printf("\nLas tarea se guardaron\n");
}





void tareahecha(tarea_t **lista) {
    char materia_buscada[MAX];
    printf("Nombre de la materia de la tarea hecha: ");
    scanf("%s", materia_buscada);
    tarea_t *actual = *lista;
    tarea_t *anterior = NULL;
    while (actual != NULL) {
        if (strcmp(actual->materia, materia_buscada) == 0) {
            printf("Tarea de '%s' hecha!\n", actual->materia);
            if (anterior == NULL) {
                *lista = actual->next;
            } else {
                anterior->next = actual->next;
            }
            free(actual);
            return;
        }
        anterior = actual;
        actual = actual->next;
    }

    printf("No tenés materias con ese nombre\n");
}



void liberar(tarea_t *lista){
    tarea_t *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}
