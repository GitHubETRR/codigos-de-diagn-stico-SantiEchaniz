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
    char nota[MAX];
    struct contacto *sig;
} contacto_t;


int main()
{
     do {
        menu();
        printf("Elegi una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case agrecontacto:
              agenda = agregar_contacto(agenda);
            break;
  
            case mostrcontactos:
              mostrar_contactos(agenda);
            break;

            case buscarcontacto:
              buscar_contacto(agenda);
            break;

            case elimcontacto:
              agenda = eliminar_contacto(agenda);
            break;

            case salir:
              guardar_archivo(agenda);
              liberar_memoria(agenda);
              printf("chau\n");
            break;

            default:
              printf("Opcion invalida\n");
            break;
        }

    } while (opcion != 6);

    return 0;
    return 0;
}
