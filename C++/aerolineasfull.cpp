#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

typedef enum{
    MOSTRAR_INFO = 1,
    AGREGAR_VUELOS,
    GUARDAR_VUELOS,
    CARGAR_de_ARCHIVO,
    CAMBIAR_ESTADO_VUELOS,
    BUSCAR_X_NdeVUELO,
    BUSCAR_X_DESTINO,
    ORDENAR_X_ESTADO,
    ORDENAR_X_NdeVUELO,
    ORDENAR_X_DESTINO,
    SALIR,
}opcion_menu;

typedef enum{
    EN_HORARIO=1,
    DEMORADO,
    CANCELADO,
}opcion_estado;

//Clase vuelo

class Vuelo {
private:

    int numero;        //identificacion de vuelo
    string destino;    //lugar de destino
    string salida;     //hora de salida estimada
    string llegada;    //hora de llegada estimada
    string estado;     //estado del vuelo

public:
    //Constructores
    Vuelo() {
        numero = 0;
    }
    
    //Constructor con parametros
   Vuelo(int num, const string& dest, const string& sal, const string& lle, const string& est){
      numero = num;
      destino = dest;
      salida = sal;
      llegada = lle;
      estado = est;
    }
      
    //Getters
    int getNumero() const { return numero; }
    const string& getDestino() const { return destino; }
    const string& getSalida() const { return salida; }
    const string& getLlegada() const { return llegada; }
    const string& getEstado() const { return estado; }
    
    //Setters
    void setNumero(int n) { numero = n; }
    void setDestino(const string& d) { destino = d; }
    void setSalida(const string& s) { salida = s; }
    void setLlegada(const string& l) { llegada = l; }
    void setEstado(const string& e) { estado = e; }
    
    //Mostrar
    void mostrarResumen() const {
        cout << "Vuelo " << numero
             << " -> " << destino
             << " [" << salida << " - " << llegada << "] "
             << "(" << estado << ")" << endl;
    }

    void mostrarDetalle(const string& nombreAerolinea) const { //aca solo le doy el nombre, porq despues le doy el
        cout << "\nINFORMACION DEL VUELO " << nombreAerolinea << endl;
        cout << "Numero : " << numero << endl;
        cout << "Destino: " << destino << endl;
        cout << "Salida : " << salida << endl;
        cout << "Llegada: " << llegada << endl;
        cout << "Estado : " << estado << endl;
    }
};


//Funcion leer n de vuelo

int leerNumero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje; //muestra la opcion a completar
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //limpia el resto de la línea del buffer.
            return valor;
        }
        cout << "Entrada invalida, ingresa un numero." << endl;
        cin.clear(); //si pones letras
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//lee hasta el primer espacio
string leerCadenaSimple(const string& mensaje) {
    string texto;
    cout << mensaje;
    cin >> texto;
    return texto;
}


string elegirEstado() {
    while (true) {
        cout << "\nSeleccione el estado del vuelo:\n";
        cout << "1. En Horario\n";
        cout << "2. Demorado\n";
        cout << "3. Cancelado\n";
        
        int opcion = leerNumero("Opcion: ");
        
        switch (opcion) {
            case EN_HORARIO: 
                return "EnHorario";
                break;
                
            case DEMORADO: 
                return "Demorado";
                break;
                
            case CANCELADO:
                return "Cancelado";
                break;
                
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
                break;
        }
    }
}


class SistemaVuelos {
    protected:
        vector<Vuelo> vuelos;
        string rutaArchivo;
        
        bool cargarVuelos() { //el bool es para el if cargarvuelos(), si es true o false
            vuelos.clear();
            ifstream archivo(rutaArchivo.c_str());
            if (!archivo) {
                cout << "No se pudo abrir el archivo de vuelos." << endl;
                return false;
            }
            
            int num;
            string dest, sal, lle, est; //Declaro variables locales para leer cada campo
            
            while (archivo >> num >> dest >> sal >> lle >> est) {
                Vuelo v(num, dest, sal, lle, est);
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
            
            for (size_t i = 0; i < vuelos.size(); i++) { //Recorre el vector y para cada objeto escribe las vars
                archivo << vuelos[i].getNumero() << ' '
                        << vuelos[i].getDestino() << ' '
                        << vuelos[i].getSalida() << ' '
                        << vuelos[i].getLlegada() << ' '
                        << vuelos[i].getEstado() << '\n';
            }
            
            return true;
        } 
        
        void mostrarVuelos(const string& nombre) const {
            if (vuelos.empty()) {
                cout << "\nNo hay vuelos cargados." << endl;
                return;
            }
            
            cout << "\nLISTA DE VUELOS " << nombre << endl;
            for (size_t i = 0; i < vuelos.size(); i++) {
                vuelos[i].mostrarResumen();
            }
        }
        
        int buscarIndicePorNumero(int num) const {
            for (size_t i = 0; i < vuelos.size(); i++) {
                if (vuelos[i].getNumero() == num) { 
                    return static_cast<int>(i); //Encontro el vuelo, convierte para asegurarse de devolverlo como int ese i
                }
            }
            return -1;
    }

    public:
        SistemaVuelos(const string& ruta)
            : rutaArchivo(ruta) { //intenta cargar los datos
            cargarVuelos();
        }
    
    virtual ~SistemaVuelos() {} //DESTRUCTOR, si clase hija (como Aerolinea) tiene su propio destr, se llama correctamente.Buena práctica

    virtual void mostrarMenu() = 0; //Fuerzo a la clase hija a implementar su propio menu
};



class Aerolinea : public SistemaVuelos {
    private:
        string nombre; 
        void buscarVueloPorNumero() const {
            if (vuelos.empty()) {
                cout << "No hay vuelos cargados para buscar." << endl;
                return;
            }
            
            int num = leerNumero("Ingresa el numero de vuelo: ");
            int indice = buscarIndicePorNumero(num);
            
            if (indice == -1) { //no lo encuentra (-1), estado del programa
                cout << "No se encontro el vuelo con ese numero." << endl;
                return;
            }
            
            vuelos[indice].mostrarDetalle(nombre); //vuelos indice es un objeto Vuelo
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
                if (vuelos[i].getDestino().find(dest) != string::npos) { //Si no lo encuentra, devuelve string::npos -no encontrado
                    vuelos[i].mostrarResumen();
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
            
            string est = elegirEstado();
            bool encontrado = false;
            cout << "\nVUELOS CON ESTADO \"" << est << "\":" << endl;
            //Recorre los vuelos y compara getEstado() con ese string, muestra solo los que coinciden.

            for (size_t i = 0; i < vuelos.size(); i++) {
                if (vuelos[i].getEstado() == est) {
                    vuelos[i].mostrarResumen();
                    encontrado = true;
                }
            }
            
            if (!encontrado) {
                cout << "No se encontraron vuelos con ese estado." << endl;
            }
        }
        
        
        
        void agregarVuelo() {
            Vuelo v;
            int num = leerNumero("Numero de vuelo: ");
            
            if (buscarIndicePorNumero(num) != -1) {
                cout << "Ya existe un vuelo con ese numero." << endl;
                return;
            }
            
            cout << "\n\n\n\n---------------------------------------------------------------------" << endl;
            cout << "IMPORTANTE: evita usar espacios en destino, salida, llegada y estado." << endl;
            cout << " Ejemplos: Madrid / 10:30 / En Horario (menu) / Demorado\n";
            
            string dest = leerCadenaSimple("Destino: ");          //Destino
            string sal = leerCadenaSimple("Hora de salida: ");    //Hora de salida
            string lle = leerCadenaSimple("Hora de llegada: ");   //Hora de llegada
            string est = elegirEstado();                          //Estado del vuelo
            
            v.setNumero(num); //crea todas als varieables del nuevo objeto vuelo
            v.setDestino(dest);
            v.setSalida(sal);
            v.setLlegada(lle);
            v.setEstado(est);
            
            vuelos.push_back(v);
            cout << "Vuelo agregado correctamente (no guardado en archivo todavia)." << endl;
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
            
            cout << "Estado actual: " << vuelos[indice].getEstado() << endl;
            string nuevo = elegirEstado(); 
            vuelos[indice].setEstado(nuevo);
            cout << "Estado actualizado (aun no guardado en archivo)." << endl;
        }
        
        
        
        void ordenarPorNumero() {
            if (vuelos.size() < 2) {
                cout << "No hay suficientes vuelos para ordenar." << endl;
                return;
            }
            
            //Compara, si j es menor que i, los intercambia
            for (size_t i = 0; i < vuelos.size() - 1; i++) {
                for (size_t j = i + 1; j < vuelos.size(); j++) {
                    if (vuelos[j].getNumero() < vuelos[i].getNumero()) {
                        Vuelo aux = vuelos[i];
                        vuelos[i] = vuelos[j];
                        vuelos[j] = aux;
                    }
                }
            }
            
            cout << "Vuelos ordenados por numero." << endl;
        }
        
        
        
        void ordenarPorDestino() { //alfabeticamente
            if (vuelos.size() < 2) {
                cout << "No hay suficientes vuelos para ordenar." << endl;
                return;
            }
            
            for (size_t i = 0; i < vuelos.size() - 1; i++) {
                for (size_t j = i + 1; j < vuelos.size(); j++) {
                    if (vuelos[j].getDestino() < vuelos[i].getDestino()) {
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
        //CONSTRUCTOR VUELOS
        Aerolinea(const string& ruta = "C:\\Users\\sechaniz.ETRR\\Desktop\\VCSCODE EN C\\vuelos.txt",
                const string& nombreAerolinea = "AEROLINEAS ARGENTINAS")
            : SistemaVuelos(ruta), nombre(nombreAerolinea) {}
            
        void mostrarMenu() override {
            int opcion = 0;
            do {
                cout << "\nMENU " << nombre << endl;
                cout << "1. Ver lista de vuelos" << endl;
                cout << "2. Agregar nuevo vuelo" << endl;
                cout << "3. Guardar cambios en archivo" << endl;
                cout << "4. Recargar vuelos desde archivo" << endl;
                cout << "5. Cambiar estado de un vuelo" << endl;
                cout << "6. Buscar vuelo por numero" << endl;
                cout << "7. Buscar vuelos por destino" << endl;
                cout << "8. Listar vuelos por estado" << endl;
                cout << "9. Ordenar vuelos por numero" << endl;
                cout << "10. Ordenar vuelos por destino" << endl;
                cout << "11. Salir" << endl;
                
                opcion = leerNumero("Seleccione una opcion: ");
                
                switch (opcion) {
                    case MOSTRAR_INFO:
                        mostrarVuelos(nombre);
                        break;
                    
                    case AGREGAR_VUELOS:
                        agregarVuelo();
                        break;
                    
                    case GUARDAR_VUELOS:
                        if (guardarVuelos()) {
                            cout << "Cambios guardados en " << rutaArchivo << endl;
                        } else {
                            cout << "No se pudo guardar el archivo." << endl;
                        }
                        break;   
                    
                    case CARGAR_de_ARCHIVO:
                        recargarDesdeArchivo();
                        break;    
                    
                    case CAMBIAR_ESTADO_VUELOS:
                        cambiarEstadoVuelo();
                        break;
                        
                        
                    case BUSCAR_X_NdeVUELO:
                        buscarVueloPorNumero();
                        break;
                        
                    case BUSCAR_X_DESTINO:
                        buscarVuelosPorDestino();
                        break;
                        
                    case ORDENAR_X_ESTADO:
                        listarPorEstado();
                        break;
                        
                    case ORDENAR_X_NdeVUELO:
                        ordenarPorNumero();
                        break;
                        
                    case ORDENAR_X_DESTINO:
                        ordenarPorDestino();
                        break;
                        
                    case SALIR:
                        cout << "Saliendo del sistema..." << endl;
                        break;
                        
                    default:
                        cout << "Opcion invalida, intenta nuevamente." << endl;
                        break;
                }
                
            } while (opcion != SALIR);
        }
};

int main() {
    Aerolinea aerolinea("vuelos.txt", "AEROLINEAS ARGENTINAS"); //Crea un objeto Aerolinea
    SistemaVuelos* sistema = &aerolinea; //Guarda un puntero que apunta a ese objeto
    sistema->mostrarMenu(); //llamo al menu para empezar el programa
    return 0;
}
