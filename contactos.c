#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define agrecontacto 1
#define mostrcontactos 2
#define buscarcontacto 3
#define elimcontacto 4
#define salir 5
#define MAX 100

typedef struct contacto {
    char nombre[MAX];
    char numero[MAX];
    char mail[MAX];
    char notas[MAX];
    struct contacto *sig;
} contacto;

int ingreso();
contacto* agregar_contacto(contacto* agenda);
void imprimir(contacto* agenda);
void buscar(contacto* agenda);
contacto* eliminar(contacto* agenda);
void guardar_en_archivo(contacto* agenda);
void liberar_memoria(contacto* agenda);
contacto* cargar_desde_archivo();

int main() {
    int opcion;
    contacto *agenda = cargar_desde_archivo();
    do {
        opcion = ingreso();
        switch (opcion) {
            case agrecontacto:
                agenda = agregar_contacto(agenda);
                break;
                
            case mostrcontactos:
                imprimir(agenda);
                break;
                
            case buscarcontacto:
                buscar(agenda);
                break;
                
            case elimcontacto:
                agenda = eliminar(agenda);
                break;
                
            case salir:
                guardar_en_archivo(agenda);
                liberar_memoria(agenda);
                printf("chau\n");
                break;
                
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != salir);
    
    return 0;
}

int ingreso() {
    int opcion;
    printf("\nMenu\n");
    printf("1-Agregar contacto\n");
    printf("2-Mostrar contactos\n");
    printf("3-Buscar contacto\n");
    printf("4-Eliminar contacto\n");
    printf("5-Salir\n");
    printf("\nOpcion: ");
    scanf("%d", &opcion);
    while (getchar() != '\n'); // limpio
    return opcion;
}

contacto* agregar_contacto(contacto* agenda) {
    contacto* nuevo = malloc(sizeof(contacto));
    if (!nuevo) {
        printf("No se pudo conseguir memoria\n");
        return agenda;
    }
    printf("Nombre: ");
    fgets(nuevo->nombre, MAX, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0;

    printf("Numero: ");
    fgets(nuevo->numero, MAX, stdin);
    nuevo->numero[strcspn(nuevo->numero, "\n")] = 0;

    printf("Mail: ");
    fgets(nuevo->mail, MAX, stdin);
    nuevo->mail[strcspn(nuevo->mail, "\n")] = 0;

    printf("Notas: ");
    fgets(nuevo->notas, MAX, stdin);
    nuevo->notas[strcspn(nuevo->notas, "\n")] = 0;

    nuevo->sig = agenda;
    return nuevo;
}

void imprimir(contacto* agenda) {
    if (!agenda) {
        printf("Vacio\n");
        return;
    }
    printf("\nContactos:\n");
    while (agenda) {
        int i;
        printf("Contacto %d:", i);
        printf("Nombre: %s\n", agenda->nombre);
        printf("Numero: %s\n", agenda->numero);
        printf("Email: %s\n", agenda->email);
        printf("Notas: %s\n", agenda->notas);
        printf("------------------------\n");
        agenda = agenda->sig;
        i++;
    }
}

void buscar(contacto* agenda) {
    char nombre[MAX];
    printf("Nombre a buscar: ");
    fgets(nombre, MAX, stdin);
    nombre[strcspn(nombre, "\n")] = 0;
    while (agenda) {
        if (strcmp(agenda->nombre, nombre) == 0) {
            printf("Contacto encontrado:\n");
            printf("Nombre: %s\n", agenda->nombre);
            printf("Número: %s\n", agenda->numero);
            printf("Email: %s\n", agenda->email);
            printf("Notas: %s\n", agenda->notas);
            return;
        }
        agenda = agenda->sig;
    }
    printf("El contacto no se encontro\n");
}

contacto* eliminar(contacto* agenda) {
    char nombre[MAX];
    printf("A quien quiero eliminar: ");
    fgets(nombre, MAX, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    contacto *actual = agenda;
    contacto *anterior = NULL;

    while (actual) {
        if (strcmp(actual->nombre, nombre) == 0) {
            if (anterior) {
                anterior->sig = actual->sig;
            } else {
                agenda = actual->sig;
            }
            free(actual);
            printf("Contacto eliminado\n");
            return agenda;
        }
        anterior = actual;
        actual = actual->sig;
    }

    printf("Contacto no existe\n");
    return agenda;
}

void guardar_en_archivo(contacto* agenda) {
    FILE *archivo = fopen("C:\Users\sechaniz\Desktop\TAREASSANTU\ContactosSantu.txt", "w");
    if (!archivo) {
        printf("No se pudo guardar el archivo\n");
        return;
    }
    while (agenda) {
        fprintf(archivo, "%s\n%s\n%s\n%s\n", agenda->nombre, agenda->numero, agenda->email, agenda->notas);
        agenda = agenda->sig;
    }
    fclose(archivo);
    printf("Agenda guardada en archivo\n");
}

contacto* cargar_desde_archivo() {
    FILE *archivo = fopen("C:\Users\sechaniz\Desktop\TAREASSANTU\ContactosSantu.txt", "r");
    if (!archivo) {
        // estaba vació, así que null
        return NULL;
    }

    contacto *agenda = NULL, *nuevo;
    char linea[MAX];

    while (fgets(linea, MAX, archivo)) {
        nuevo = malloc(sizeof(contacto));
        if (!nuevo) {
            printf("No se pudo obtener memnoria\n");
            break;
        }

        strcpy(nuevo->nombre, linea);
        nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0;

        if (!fgets(nuevo->numero, MAX, archivo)) break;
        nuevo->numero[strcspn(nuevo->numero, "\n")] = 0;

        if (!fgets(nuevo->email, MAX, archivo)) break;
        nuevo->email[strcspn(nuevo->email, "\n")] = 0;

        if (!fgets(nuevo->notas, MAX, archivo)) break;
        nuevo->notas[strcspn(nuevo->notas, "\n")] = 0;

        nuevo->sig = agenda;
        agenda = nuevo;
    }

    fclose(archivo);
    return agenda;
}



void liberar_memoria(contacto* agenda) {
    contacto* aux;
    while (agenda) {
        aux = agenda;
        agenda = agenda->sig;
        free(aux);
    }
}
