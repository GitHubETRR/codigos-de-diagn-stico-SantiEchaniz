#include <iostream>
using namespace std;


int main() {
    double saldo = 10000.0;  // saldo inicial
    int opcion;
    double monto;

    do {
        cout << "\nCAJERO\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Retirar dinero\n";
        cout << "0. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Su saldo es: $" << saldo << endl;
                break;
            case 2:
                cout << "Ingrese monto a depositar: ";
                cin >> monto;
                if (monto > 0) {
                    saldo += monto;
                    cout << "Deposito exitoso. Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "Monto invalido.\n";
                }
                break;
            case 3:
                cout << "Ingrese monto a retirar: ";
                cin >> monto;
                if (monto > 0 && monto <= saldo) {
                    saldo -= monto;
                    cout << "Retiro exitoso. Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "Monto invalido o fondos insuficientes.\n";
                }
                break;
            case 0:
                cout << "Gracias por usar el cajero. Adios!\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    return 0;
}
