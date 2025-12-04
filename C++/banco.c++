#include <iostream>
#include <fstream>  
using namespace std;

int menu();

int main() {
    double saldo = 10000.0;  
    int opcionprogram;
    double monto;

    ofstream archivo("C:\\Users\\sechaniz.ETRR\\Desktop\\VCSCODE EN C\\bancosantu.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    archivo << "INICIO DEL PROGRAMA\n";

    do {
        opcionprogram = menu();

        switch(opcionprogram) {

            case 1:
                cout << "Su saldo es: $" << saldo << endl;
                archivo << "Consulta de saldo: $" << saldo << endl;
                break;

            case 2:
                cout << "Ingrese el monto a ingresar: ";
                cin >> monto;
                if (monto > 0) {
                    saldo += monto;
                    cout << "Deposito exitoso. Nuevo saldo: $" << saldo << endl;
                    archivo << "Deposito de $" << monto 
                            << " | Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "Monto invalido.\n";
                    archivo << "Intento de deposito invalido.\n";
                }
                break;

            case 3:
                cout << "Ingrese monto a retirar: ";
                cin >> monto;
                if (monto > 0 && monto <= saldo) {
                    saldo -= monto;
                    cout << "Retiro exitoso. Nuevo saldo: $" << saldo << endl;
                    archivo << "Retiro de $" << monto 
                            << " | Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "Monto invalido o fondos insuficientes.\n";
                    archivo << "Intento de retiro invalido o saldo insuficiente.\n";
                }
                break;

            case 0:
                cout << "Chau\n";
                archivo << "-FIN\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcionprogram != 0);

    archivo.close(); 

    return 0;
}

int menu() {
    int opcion;
    cout << "\nCAJERO\n";
    cout << "1 Consultar saldo\n";
    cout << "2 Depositar dinero\n";
    cout << "3 Retirar dinero\n";
    cout << "0 Salir\n";
    cout << "Elija una opcion: ";
    cin >> opcion;
    return opcion;
}
