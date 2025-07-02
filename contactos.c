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
    char email[MAX];
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

int main(){
    int opcion;
    contacto *agenda = NULL;
    do {
        opcion=ingreso();
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
            break;
        }

    } while (opcion != salir);
    return 0;
}


int ingreso(){
    int opcion;
    printf("\nMenu\n");
    printf("1.Agregar contacto\n");
    printf("2.Mostrar contactos\n");
    printf("3.Buscar contacto\n");
    printf("4.Eliminar contacto\n");
    printf("5.Salir\n");
    printf("           Opcion: ");
    scanf("%d", &opcion);
    return opcion;
}


contacto* agregar_contacto(contacto* agenda) {
    contacto* nuevo = malloc(sizeof(contacto));
    if (!nuevo) {
        printf("no se pudo conseguir memoria\n");
        return agenda;
    }
    printf("Nombre:");
    fgets(nuevo->nombre, MAX, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0;
    printf("Numero:");
    fgets(nuevo->numero, MAX, stdin);
    nuevo->numero[strcspn(nuevo->numero, "\n")] = 0;
    nuevo->sig = agenda;
    return nuevo;
}


void imprimir(contacto* agenda) {
    if (!agenda) {
        printf("está vacio\n");
        return;
    }
    printf("\nContactos:\n");
    while (agenda) {
        printf("Nombre: %s\n", agenda->nombre);
        printf("Numero: %s\n\n", agenda->numero);
        agenda = agenda->sig;
    }
}


void buscar(contacto* agenda) {
    char nombre[MAX];
    printf("Nombre a buscar: ");
    fgets(nombre, MAX, stdin);
    nombre[strcspn(nombre, "\n")] = 0;
    while (agenda) {
        if (strcmp(agenda->nombre, nombre) == 0) {
            printf("Contacto:\nNombre: %s\nNumero: %s\n", agenda->nombre, agenda->numero);
            return;
        }
        agenda = agenda->sig;
    }
    printf("No se encontro el contacto\n");
}


void guardar_en_archivo(contacto* agenda) {
    FILE *archivo = fopen("C:\\Users\\sechaniz\\Desktop\\OTROS\\ContactosSantu.txt", "w");
    if (!archivo) {
        printf("No se pudo guardar el archivo\n");
        return;
    }
    while (agenda) {
        fprintf(archivo, "%s\n%s\n", agenda->nombre, agenda->numero);
        agenda = agenda->sig;
    }
    fclose(archivo);
    printf("Guardado'\n");
}


void liberar_memoria(contacto* agenda) {
    contacto* aux;
    while (agenda) {
        aux = agenda;
        agenda = agenda->sig;
        free(aux);
    }
}
