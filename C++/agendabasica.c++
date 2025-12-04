#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Contacto {
    string nombre;
    string telefono;
};

void agregarContacto() {
    Contacto c;
    cout << "Ingrese nombre: ";
    cin.ignore();
    getline(cin, c.nombre);
    cout << "Ingrese telefono: ";
    getline(cin, c.telefono);

    ofstream archivo("agendasantu.txt", ios::app);
    if (archivo.is_open()) {
        archivo << c.nombre << ";" << c.telefono << endl;
        archivo.close();
        cout << "Contacto guardado!" << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

void mostrarContactos() {
    ifstream archivo("agendasantu.txt");
    string linea;
    if (archivo.is_open()) {
        cout << "\nLista de contactos\n";
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main() {
    int opcion;
    do {
        cout << "\nagenda\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Mostrar contactos\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: agregarContacto(); break;
            case 2: mostrarContactos(); break;
            case 3: cout << "Saliendo" << endl; break;
            default: cout << "Opcion no valida.\n"; break;
        }
    } while(opcion != 3);

    return 0;
}
