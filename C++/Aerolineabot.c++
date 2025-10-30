#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Vuelo {
    int numero;
    string destino;
    string salida;
    string llegada;
    string estado;
};


int cargarVuelos(Vuelo vuelos[], int maxVuelos) {
    ifstream archivo("C:\Users\sechaniz.ETRR\Desktop\VCSCODE EN C\vuelos.txt");
    if (!archivo) {
        cout << "Error: no se pudo abrir el archivo de vuelos." << endl;
        return 0;
    }

    int i = 0;
    while (archivo >> vuelos[i].numero >> vuelos[i].destino >> vuelos[i].salida >> vuelos[i].llegada >> vuelos[i].estado) {
        i++;
        if (i >= maxVuelos) break;
    }

    archivo.close();
    return i;
}

void mostrarMenu() {
    cout << "\nMENU AEROLINEAS ARGENTINAS" << endl;
    cout << "1. Ver lista de vuelos" << endl;
    cout << "2. Buscar vuelo por numero" << endl;
    cout << "3. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarVuelos(Vuelo vuelos[], int cantidad) {
    cout << "\nLISTA DE VUELOS" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << "Vuelo " << vuelos[i].numero << " -> " << vuelos[i].destino << " (" << vuelos[i].estado << ")" << endl;
    }
}

void buscarVuelo(Vuelo vuelos[], int cantidad) {
    int num;
    cout << "Ingresa el numero de vuelo: ";
    cin >> num;
    bool encontrado = false;

    for (int i = 0; i < cantidad; i++) {
        if (vuelos[i].numero == num) {
            cout << "\nINFORMACION DEL VUELO" << endl;
            cout << "Numero: " << vuelos[i].numero << endl;
            cout << "Destino: " << vuelos[i].destino << endl;
            cout << "Salida: " << vuelos[i].salida << endl;
            cout << "Llegada: " << vuelos[i].llegada << endl;
            cout << "Estado: " << vuelos[i].estado << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro el vuelo con numero " << num << "." << endl;
    }
}

int main() {
    const int MAX_VUELOS = 100;
    Vuelo vuelos[MAX_VUELOS];
    int cantidad = cargarVuelos(vuelos, MAX_VUELOS);

    if (cantidad == 0) {
        cout << "No hay vuelos cargados." << endl;
        return 0;
    }

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarVuelos(vuelos, cantidad);
                break;
            case 2:
                buscarVuelo(vuelos, cantidad);
                break;
            case 3:
                cout << "Saliendo del sistema" << endl;
                break;
            default:
                cout << "Opcion invalida. Intenta nuevamente." << endl;
        }

    } while (opcion != 3);

    return 0;
}
