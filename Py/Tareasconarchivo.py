from enum import Enum
import json
import os

ARCHIVO = "C:\Users\sechaniz.ETRR\Desktop\VCSCODE EN C\tareas.json"

class EstadoTarea(Enum):
    PENDIENTE = 1
    ENPROCESO = 2
    COMPLETADA = 3

tareas = []

def cargar_tareas():
    if not os.path.exists(ARCHIVO):
        return
    try:
        with open(ARCHIVO, "r", encoding="utf-8") as f:
            data = json.load(f)
        tareas.clear()
        for item in data:
            estado = item.get("estado")
            if isinstance(estado, int):
                estado_enum = EstadoTarea(estado)
            else:
                estado_enum = EstadoTarea[estado]
            tareas.append({"nombre": item["nombre"], "estado": estado_enum})
    except Exception as e:
        print(f"Advertencia: no se pudieron cargar las tareas ({e}).")

def guardar_tareas():
    try:
        data = [{"nombre": t["nombre"], "estado": t["estado"].value} for t in tareas]
        with open(ARCHIVO, "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=2)
    except Exception as e:
        print(f"Error al guardar tareas: {e}")

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
    guardar_tareas()
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
        guardar_tareas()
        print("actualizado correctamente")
    except ValueError:
        print("Ingrese un numero valido")

def main():
    cargar_tareas()
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
            guardar_tareas()
            break  
        else:
            print("Opción no válida")

main()
