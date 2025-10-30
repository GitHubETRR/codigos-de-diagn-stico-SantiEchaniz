from enum import Enum

class EstadoTarea(Enum):
    PENDIENTE = 1
    ENPROCESO = 2
    COMPLETADA = 3

tareas = []


def mostrar_menu():
    print("\nMenu")
    print("1.Agregar tarea")
    print("2.Mostrar tareas")
    print("3.Cambiar estado de una tarea")
    print("4.Cerrar")


def agregar_tarea():
    nombre = input("Ingresa el nombre de la tarea: ")
    tarea = {"nombre": nombre, "estado": EstadoTarea.PENDIENTE}
    tareas.append(tarea)
    print(f"Tarea '{nombre}' agregada con estado PENDIENTE.")

def mostrar_tareas():
    if not tareas:
        print("No hay tareas registradas.")
    else:
        print("\nTAREAS")
        for i, tarea in enumerate(tareas, start=1):
            print(f"{i}. {tarea['nombre']} - {tarea['estado'].name}")


def cambiar_estado():
    mostrar_tareas()
    if not tareas:
        return
    
    try:
        indice = int(input("Ingresa el número de la tarea a modificar: ")) - 1
        if indice < 0 or indice >= len(tareas):
            print("Numero no existe")
            return

        print("\nSelecciona nuevo estado:")
        for estado in EstadoTarea:
            print(f"{estado.value}. {estado.name}")

        opcion = int(input("Opción: "))
        nuevo_estado = EstadoTarea(opcion)
        tareas[indice]['estado'] = nuevo_estado
        print("actualizado correctamente")
    except ValueError:
        print("Ingrese un numero válido")
    except KeyError:
        print("Esta mal")


def main():
    while True:
        mostrar_menu()
        opcion = input("Seleccione una opcion: ")

        if opcion == "1":
            agregar_tarea()
        elif opcion == "2":
            mostrar_tareas()
        elif opcion == "3":
            cambiar_estado()
        elif opcion == "4":
            print("chau")
        break;
main()