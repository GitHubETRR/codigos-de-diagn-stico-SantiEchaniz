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
} tarea;

int ingreso(void);
tarea *tareasguardadas();
tarea *agregar_tarea(tarea *lista);
void imprimiryguardar(tarea *lista);
void tareahecha(tarea **lista);
void liberar(tarea *lista);



int main() {
    tarea *milista = tareasguardadas();
    int opcion;

    do {
        opcion = ingreso();
    
        switch (opcion) {
            case agregar:
                milista = agregar_tarea(milista);
            break;
                
            case mostrar:
                imprimiryguardar(milista); 
            break;
            
            case hecho:
                tareahecha(&milista);
            break;

            case reestablecer:
                liberar(milista);
                printf("Fin\n");
                break;
            default:
                printf("Opción invalida\n");
        }

    } while (opcion != reestablecer);

    return 0;
}

tarea *cargar_tareas() {
    FILE *archivo = fopen("C:\\Users\\sechaniz\\Desktop\\TAREASSANTU\\tareas.txt", "r");
    if (!archivo) return NULL;

    tarea *lista = NULL;
    char materia[MAX];
    char descripcion[MAX];

    while (fgets(materia, MAX, archivo) && fgets(descripcion, MAX, archivo)) {
        // Limpiar saltos de línea
        materia[strcspn(materia, "\n")] = 0;
        descripcion[strcspn(descripcion, "\n")] = 0;

        tarea *nueva = malloc(sizeof(tarea));
        if (!nueva) break;

        strcpy(nueva->materia, materia);
        strcpy(nueva->descripcion, descripcion);
        nueva->next = lista;
        lista = nueva;
    }

    fclose(archivo);
    return lista;
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



tarea *agregar_tarea(tarea *lista){
    tarea *nueva = (tarea *)malloc(sizeof(tarea));
    if (nueva == NULL) {
        printf("no se pudo reservar memoria, error\n");
        
        return lista;
    }
    printf("De que materia es esa tarea/pendiente: ");
    fgets(nueva->materia, MAX, stdin);
    nueva->materia[strcspn(nueva->materia, "\n")] = 0;
    printf("Ingresá la descripción de la tarea/pendiente: ");
    fgets(nueva->descripcion, MAX, stdin);
    nueva->descripcion[strcspn(nueva->descripcion, "\n")] = 0;
    nueva->next = lista;
    printf("Agregado!\n");
    
    return nueva;
}


void imprimiryguardar(tarea *lista){
    FILE *archivo = fopen("C:\\Users\\sechaniz\\Desktop\\TAREASSANTU\\tareas.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo crear o abrir el archivo\n");
        return;
    }

    if (lista == NULL) {
        printf("No hay tareas/pendientes\n");
        fprintf(archivo, "No hay tareas/pendientes\n");
        fclose(archivo);
        return;
    }
    while (lista) {
        printf("- %s: %s\n", lista->materia, lista->descripcion);
        fprintf(archivo, "%s\n%s\n", lista->materia, lista->descripcion);
        lista = lista->next;
    }

    fclose(archivo);
    printf("\nLas tareas/pendientes se guardaron\n");
}





void tareahecha(tarea **lista) {
    char materia_buscada[MAX];
    printf("Nombre de la materia de la tarea hecha: ");
    getchar(); // para limpiar el \n que haya quedado
    fgets(materia_buscada, MAX, stdin);
    materia_buscada[strcspn(materia_buscada, "\n")] = 0;

    tarea *actual = *lista;
    tarea *anterior = NULL;
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




void liberar(tarea *lista){
    tarea *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}
