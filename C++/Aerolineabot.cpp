#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Vuelo {
    int numero;
    string destino;
    string salida;
    string llegada;
    string estado;
};

int leerNumero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Entrada invalida, ingresa un numero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerCadenaSimple(const string& mensaje) {
    string texto;
    cout << mensaje;
    cin >> texto;
    return texto;
}

class Aerolinea {
private:
    vector<Vuelo> vuelos;
    string rutaArchivo;

    bool cargarVuelos() {
        vuelos.clear();
        ifstream archivo(rutaArchivo.c_str());
        if (!archivo) {
            cout << "No se pudo abrir el archivo de vuelos." << endl;
            return false;
        }

        Vuelo v;
        while (archivo >> v.numero >> v.destino >> v.salida >> v.llegada >> v.estado) {
            vuelos.push_back(v);
        }

        if (vuelos.empty()) {
            cout << "El archivo se abrio pero no se encontraron vuelos." << endl;
            return false;
        }

        return true;
    }

    bool guardarVuelos() const {
        ofstream archivo(rutaArchivo.c_str());
        if (!archivo) {
            return false;
        }

        for (size_t i = 0; i < vuelos.size(); i++) {
            archivo << vuelos[i].numero << ' '
                    << vuelos[i].destino << ' '
                    << vuelos[i].salida << ' '
                    << vuelos[i].llegada << ' '
                    << vuelos[i].estado << '\n';
        }

        return true;
    }

    void mostrarVuelos() const {
        if (vuelos.empty()) {
            cout << "\nNo hay vuelos cargados." << endl;
            return;
        }

        cout << "\nLISTA DE VUELOS" << endl;
        for (size_t i = 0; i < vuelos.size(); i++) {
            cout << "Vuelo " << vuelos[i].numero
                 << " -> " << vuelos[i].destino
                 << " [" << vuelos[i].salida << " - " << vuelos[i].llegada << "] "
                 << "(" << vuelos[i].estado << ")" << endl;
        }
    }

    int buscarIndicePorNumero(int num) const {
        for (size_t i = 0; i < vuelos.size(); i++) {
            if (vuelos[i].numero == num) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void buscarVueloPorNumero() const {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados para buscar." << endl;
            return;
        }

        int num = leerNumero("Ingresa el numero de vuelo: ");
        int indice = buscarIndicePorNumero(num);

        if (indice == -1) {
            cout << "No se encontro el vuelo con ese numero." << endl;
            return;
        }

        const Vuelo& v = vuelos[indice];

        cout << "\nINFORMACION DEL VUELO AEROLINEAS ARGENTINAS" << endl;
        cout << "Numero : " << v.numero << endl;
        cout << "Destino: " << v.destino << endl;
        cout << "Salida : " << v.salida << endl;
        cout << "Llegada: " << v.llegada << endl;
        cout << "Estado : " << v.estado << endl;
    }

    void buscarVuelosPorDestino() const {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados para buscar." << endl;
            return;
        }

        string dest = leerCadenaSimple("Ingresa el destino (o parte, sin espacios): ");

        bool encontrado = false;
        cout << "\nVUELOS ENCONTRADOS PARA DESTINO \"" << dest << "\":" << endl;

        for (size_t i = 0; i < vuelos.size(); i++) {
            if (vuelos[i].destino.find(dest) != string::npos) {
                cout << "Vuelo " << vuelos[i].numero
                     << " -> " << vuelos[i].destino
                     << " (" << vuelos[i].estado << ")" << endl;
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron vuelos con ese destino." << endl;
        }
    }

    void listarPorEstado() const {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados." << endl;
            return;
        }

        string est = leerCadenaSimple("Ingresa el estado (Ej: EnHorario, Demorado, Cancelado): ");

        bool encontrado = false;
        cout << "\nVUELOS CON ESTADO \"" << est << "\":" << endl;

        for (size_t i = 0; i < vuelos.size(); i++) {
            if (vuelos[i].estado == est) {
                cout << "Vuelo " << vuelos[i].numero
                     << " -> " << vuelos[i].destino
                     << " [" << vuelos[i].salida << " - " << vuelos[i].llegada << "]" << endl;
                encontrado = true;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron vuelos con ese estado." << endl;
        }
    }

    void agregarVuelo() {
        Vuelo v;
        v.numero = leerNumero("Numero de vuelo: ");

        if (buscarIndicePorNumero(v.numero) != -1) {
            cout << "Ya existe un vuelo con ese numero." << endl;
            return;
        }

        cout << "IMPORTANTE: evita usar espacios en destino, salida, llegada y estado." << endl;
        cout << "Ejemplos: Madrid / 10:30 / EnHorario / Demorado\n";

        v.destino = leerCadenaSimple("Destino: ");
        v.salida = leerCadenaSimple("Hora de salida: ");
        v.llegada = leerCadenaSimple("Hora de llegada: ");
        v.estado = leerCadenaSimple("Estado: ");

        vuelos.push_back(v);
        cout << "Vuelo agregado correctamente (aun no guardado en archivo)." << endl;
    }

    void cambiarEstadoVuelo() {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados." << endl;
            return;
        }

        int num = leerNumero("Numero de vuelo a modificar: ");
        int indice = buscarIndicePorNumero(num);

        if (indice == -1) {
            cout << "No se encontro el vuelo." << endl;
            return;
        }

        cout << "Estado actual: " << vuelos[indice].estado << endl;
        cout << "IMPORTANTE: evita usar espacios. Ej: EnHorario, Demorado, Cancelado." << endl;

        string nuevo = leerCadenaSimple("Nuevo estado: ");
        vuelos[indice].estado = nuevo;

        cout << "Estado actualizado (aun no guardado en archivo)." << endl;
    }

    void ordenarPorNumero() {
        if (vuelos.size() < 2) {
            cout << "No hay suficientes vuelos para ordenar." << endl;
            return;
        }

        for (size_t i = 0; i < vuelos.size() - 1; i++) {
            for (size_t j = i + 1; j < vuelos.size(); j++) {
                if (vuelos[j].numero < vuelos[i].numero) {
                    Vuelo aux = vuelos[i];
                    vuelos[i] = vuelos[j];
                    vuelos[j] = aux;
                }
            }
        }

        cout << "Vuelos ordenados por numero." << endl;
    }

    void ordenarPorDestino() {
        if (vuelos.size() < 2) {
            cout << "No hay suficientes vuelos para ordenar." << endl;
            return;
        }

        for (size_t i = 0; i < vuelos.size() - 1; i++) {
            for (size_t j = i + 1; j < vuelos.size(); j++) {
                if (vuelos[j].destino < vuelos[i].destino) {
                    Vuelo aux = vuelos[i];
                    vuelos[i] = vuelos[j];
                    vuelos[j] = aux;
                }
            }
        }

        cout << "Vuelos ordenados por destino." << endl;
    }

    void recargarDesdeArchivo() {
        if (cargarVuelos()) {
            cout << "Vuelos recargados desde el archivo." << endl;
        } else {
            cout << "No se pudieron recargar los vuelos." << endl;
        }
    }

public:
    Aerolinea(const string& ruta = "vuelos.txt") {
        rutaArchivo = ruta;
        cargarVuelos();
    }

    void mostrarMenu() {
        int opcion = 0;
        do {
            cout << "\nMENU AEROLINEAS ARGENTINAS" << endl;
            cout << "1. Ver lista de vuelos" << endl;
            cout << "2. Buscar vuelo por numero" << endl;
            cout << "3. Buscar vuelos por destino" << endl;
            cout << "4. Listar vuelos por estado" << endl;
            cout << "5. Agregar nuevo vuelo" << endl;
            cout << "6. Cambiar estado de un vuelo" << endl;
            cout << "7. Ordenar vuelos por numero" << endl;
            cout << "8. Ordenar vuelos por destino" << endl;
            cout << "9. Guardar cambios en archivo" << endl;
            cout << "10. Recargar vuelos desde archivo" << endl;
            cout << "11. Salir" << endl;

            opcion = leerNumero("Seleccione una opcion: ");

            switch (opcion) {
                case 1:
                    mostrarVuelos();
                    break;
                case 2:
                    buscarVueloPorNumero();
                    break;
                case 3:
                    buscarVuelosPorDestino();
                    break;
                case 4:
                    listarPorEstado();
                    break;
                case 5:
                    agregarVuelo();
                    break;
                case 6:
                    cambiarEstadoVuelo();
                    break;
                case 7:
                    ordenarPorNumero();
                    break;
                case 8:
                    ordenarPorDestino();
                    break;
                case 9:
                    if (guardarVuelos()) {
                        cout << "Cambios guardados en " << rutaArchivo << endl;
                    } else {
                        cout << "No se pudo guardar el archivo." << endl;
                    }
                    break;
                case 10:
                    recargarDesdeArchivo();
                    break;
                case 11:
                    cout << "Saliendo del sistema..." << endl;
                    break;
                default:
                    cout << "Opcion invalida, intenta nuevamente." << endl;
            }

        } while (opcion != 11);
    }
};

int main() {

    Aerolinea sistema;

    sistema.mostrarMenu();
    return 0;
}
