#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

struct Vuelo {
    int numero{};
    string destino;
    string salida;
    string llegada;
    string estado;
};

template<typename T>
T leerNumero(const string& mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Entrada invalida, intenta de nuevo." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerTexto(const string& mensaje) {
    string s;
    while (true) {
        cout << mensaje;
        cin >> ws;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "Texto vacio, intenta de nuevo." << endl;
    }
}

string aMinusculas(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return static_cast<char>(tolower(c)); });
    return s;
}

class Aerolinea {
private:
    vector<Vuelo> vuelos;
    string rutaArchivo;

    bool cargarVuelos() {
        vuelos.clear();
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo de vuelos.");
        }

        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            istringstream iss(linea);
            Vuelo v;
            if (!(iss >> v.numero >> v.destino >> v.salida >> v.llegada >> v.estado)) {
                continue;
            }
            vuelos.push_back(v);
        }

        return !vuelos.empty();
    }

    bool guardarVuelos() const {
        ofstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            return false;
        }
        for (const auto& v : vuelos) {
            archivo << v.numero << ' '
                    << v.destino << ' '
                    << v.salida << ' '
                    << v.llegada << ' '
                    << v.estado << '\n';
        }
        return true;
    }

    void mostrarVuelos() const {
        if (vuelos.empty()) {
            cout << "\nNo hay vuelos cargados." << endl;
            return;
        }

        cout << "\nLISTA DE VUELOS" << endl;
        for (const auto& v : vuelos) {
            cout << "Vuelo " << v.numero
                 << " -> " << v.destino
                 << " [" << v.salida << " - " << v.llegada << "] "
                 << "(" << v.estado << ")" << endl;
        }
    }

    const Vuelo* buscarPorNumero(int num) const {
        auto it = find_if(vuelos.begin(), vuelos.end(),
                          [num](const Vuelo& v) {
                              return v.numero == num;
                          });

        if (it == vuelos.end()) return nullptr;
        return &(*it);
    }

    Vuelo* buscarEditablePorNumero(int num) {
        auto it = find_if(vuelos.begin(), vuelos.end(),
                          [num](const Vuelo& v) {
                              return v.numero == num;
                          });

        if (it == vuelos.end()) return nullptr;
        return &(*it);
    }

    void buscarVueloPorNumero() const {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados para buscar." << endl;
            return;
        }

        int num = leerNumero<int>("Ingresa el numero de vuelo: ");
        const Vuelo* v = buscarPorNumero(num);

        if (!v) {
            cout << "No se encontro el vuelo con ese numero." << endl;
            return;
        }

        cout << "\nINFORMACION DEL VUELO AEROLINEAS ARGENTINAS" << endl;
        cout << "Numero : " << v->numero << endl;
        cout << "Destino: " << v->destino << endl;
        cout << "Salida : " << v->salida << endl;
        cout << "Llegada: " << v->llegada << endl;
        cout << "Estado : " << v->estado << endl;
    }

    void buscarVuelosPorDestino() const {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados para buscar." << endl;
            return;
        }

        string dest = leerTexto("Ingresa el destino (o parte del destino): ");
        string destMin = aMinusculas(dest);

        vector<const Vuelo*> resultados;

        for (const auto& v : vuelos) {
            if (aMinusculas(v.destino).find(destMin) != string::npos) {
                resultados.push_back(&v);
            }
        }

        if (resultados.empty()) {
            cout << "No se encontraron vuelos con ese destino." << endl;
            return;
        }

        cout << "\nVUELOS ENCONTRADOS PARA DESTINO \"" << dest << "\":" << endl;
        for (const auto* v : resultados) {
            cout << "Vuelo " << v->numero
                 << " -> " << v->destino
                 << " (" << v->estado << ")" << endl;
        }
    }

    void listarPorEstado() const {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados." << endl;
            return;
        }

        string est = leerTexto("Ingresa el estado (Ej: EnHorario, Demorado, Cancelado): ");
        string estMin = aMinusculas(est);

        vector<const Vuelo*> resultados;

        for (const auto& v : vuelos) {
            if (aMinusculas(v.estado) == estMin) {
                resultados.push_back(&v);
            }
        }

        if (resultados.empty()) {
            cout << "No se encontraron vuelos con ese estado." << endl;
            return;
        }

        cout << "\nVUELOS CON ESTADO \"" << est << "\":" << endl;
        for (const auto* v : resultados) {
            cout << "Vuelo " << v->numero
                 << " -> " << v->destino
                 << " [" << v->salida << " - " << v->llegada << "]" << endl;
        }
    }

    void agregarVuelo() {
        Vuelo v;
        v.numero = leerNumero<int>("Numero de vuelo: ");

        if (buscarPorNumero(v.numero)) {
            cout << "Ya existe un vuelo con ese numero." << endl;
            return;
        }

        cout << "IMPORTANTE: evita usar espacios en destino, salida, llegada y estado." << endl;
        cout << "Ejemplos: 'Madrid', '10:30', 'EnHorario', 'Demorado'.\n";

        cout << "Destino: ";
        cin >> v.destino;
        cout << "Hora de salida: ";
        cin >> v.salida;
        cout << "Hora de llegada: ";
        cin >> v.llegada;
        cout << "Estado: ";
        cin >> v.estado;

        vuelos.push_back(v);
        cout << "Vuelo agregado correctamente (aun no guardado en archivo)." << endl;
    }

    void cambiarEstadoVuelo() {
        if (vuelos.empty()) {
            cout << "No hay vuelos cargados." << endl;
            return;
        }

        int num = leerNumero<int>("Numero de vuelo a modificar: ");
        Vuelo* v = buscarEditablePorNumero(num);

        if (!v) {
            cout << "No se encontro el vuelo." << endl;
            return;
        }

        cout << "Estado actual: " << v->estado << endl;
        cout << "IMPORTANTE: evita usar espacios. Ej: EnHorario, Demorado, Cancelado.\n";
        cout << "Nuevo estado: ";
        string nuevo;
        cin >> nuevo;
        v->estado = nuevo;
        cout << "Estado actualizado (aun no guardado en archivo)." << endl;
    }

    void ordenarPorNumero() {
        sort(vuelos.begin(), vuelos.end(),
             [](const Vuelo& a, const Vuelo& b) {
                 return a.numero < b.numero;
             });
        cout << "Vuelos ordenados por numero." << endl;
    }

    void ordenarPorDestino() {
        sort(vuelos.begin(), vuelos.end(),
             [](const Vuelo& a, const Vuelo& b) {
                 return a.destino < b.destino;
             });
        cout << "Vuelos ordenados por destino." << endl;
    }

    void recargarDesdeArchivo() {
        try {
            if (cargarVuelos()) {
                cout << "Vuelos recargados desde el archivo." << endl;
            } else {
                cout << "Archivo vacio o sin vuelos validos." << endl;
            }
        } catch (const exception& e) {
            cout << "Error al recargar: " << e.what() << endl;
        }
    }

public:
    Aerolinea(const string& ruta = "vuelos.txt") : rutaArchivo(ruta) {
        try {
            if (!cargarVuelos()) {
                cout << "El archivo se abrio pero no se encontraron vuelos." << endl;
            }
        } catch (const exception& e) {
            cout << "Error, sistema no disponible: " << e.what() << endl;
        }
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

            opcion = leerNumero<int>("Seleccione una opcion: ");

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
