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
    char telefono[MAX];
    char email[MAX];
    char notas[MAX];
    struct contacto *sig;
} contacto;

void ingreso();
contacto* agregar_contacto(contacto* agenda);
void imprimir(contacto* agenda);
void buscar(contacto* agenda);
contacto* eliminar(contacto* agenda);
void guardar_en_archivo(contacto* agenda);
void liberar_memoria(contacto* agenda);

int main()
{
    do {
        int ingreso
        ingreso=ingreso();
        switch (ingreso) {
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


ingreso(){
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
