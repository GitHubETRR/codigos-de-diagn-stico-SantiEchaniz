import csv

def guardar_grabacion(ruta_csv, nombre_archivo, camara, microfono):
    with open(ruta_csv, "a", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow([nombre_archivo, camara, microfono])

def main():
    ruta_csv = r"C:\Users\sechaniz.ETRR\Desktop\VCSCODE EN C\grabaciones.csv"

    print("ORGANIZADOR DE GRABACIONES")
    print("Escribi 'salir' cuando quieras terminar.\n")

    while True:
        nombre = input("Nombre de archivo y numero de toma: ").strip()
        if nombre.lower() == "salir":
            print("\nguardado")
            break

        camara = input("Camara usada: ").strip()
        microfono = input("Microfono usado: ").strip()

        guardar_grabacion(ruta_csv, nombre, camara, microfono)
        print("Guardado correctamente.\n")

if __name__ == "__main__":
    main()
