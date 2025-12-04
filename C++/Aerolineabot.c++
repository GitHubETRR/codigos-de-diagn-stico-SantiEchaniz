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

class Aerolinea {
private:
    Vuelo vuelos[100];
    int cantidad;

    int cargarVuelos() {
        ifstream archivo("C:\Users\sechaniz.ETRR\Desktop\VCSCODE EN C\vuelos.txt");
        if (!archivo) {
            cout << "Error, sistema no disponible" << endl;
            cantidad = 0;
            return 0;
        }

        int i = 0;
        while (archivo >> vuelos[i].numero >> vuelos[i].destino >> vuelos[i].salida >> vuelos[i].llegada >> vuelos[i].estado) {
            i++;
            if (i >= 100) break;
        }
        archivo.close();
        cantidad = i;
        return cantidad;
    }

    void mostrarVuelos() {
        cout << "\nLISTA DE VUELOS" << endl;
        for (int i = 0; i < cantidad; i++) {
            cout << "Vuelo " << vuelos[i].numero << " -> " << vuelos[i].destino << " (" << vuelos[i].estado << ")" << endl;
        }
    }

    void buscarVuelo() {
        int num;
        cout << "Ingresa el numero de vuelo: ";
        cin >> num;
        bool encontrado = false;

        for (int i = 0; i < cantidad; i++) {
            if (vuelos[i].numero == num) {
                cout << "\nINFORMACION DEL VUELO AEROLINEAS ARGENTINAS" << endl;
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
            cout << "No se encontro el vuelo con ese numero " << endl;
        }
    }

public:
    Aerolinea() {
        cantidad = cargarVuelos();
        if (cantidad == 0) {
            cout << "No hay vuelos cargados." << endl;
        }
    }

    void mostrarMenu() {
        int opcion;
        do {
            cout << "\n MENU AEROLINEAS ARGENTINAS" << endl;
            cout << "1. Ver lista de vuelos" << endl;
            cout << "2. Buscar vuelo por numero" << endl;
            cout << "3. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    mostrarVuelos();
                    break;
                case 2:
                    buscarVuelo();
                    break;
                case 3:
                    cout << "Saliendo del sistema" << endl;
                    break;
                default:
                    cout << "Opcion invalida, Intenta nuevamente." << endl;
            }

        } while (opcion != 3);
    }
};

int main() {
    Aerolinea sistema;
    sistema.mostrarMenu();
    return 0;
}
