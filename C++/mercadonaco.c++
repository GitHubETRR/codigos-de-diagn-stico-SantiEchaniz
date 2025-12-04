#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

int menu();

struct Movimiento {
    string tipo;
    double monto;
};

int main() {
    double saldo = 10000.0;
    int opcionprogram;
    double monto = 0;
    string alias = "miCuentaPricnipal";
    vector<Movimiento> movs;

    auto mostrarSaldo = [&](bool conDetalle = false) {
        cout << "Su saldo es: $" << fixed << setprecision(2) << saldo << endl;
        if (conDetalle && !movs.empty()) {
            cout << "Ultimos movimietos:" << endl;
            int limite = movs.size() > 5 ? 5 : (int)movs.size();
            for (int i = (int)movs.size() - limite; i < (int)movs.size(); ++i) {
                cout << "- " << movs[i].tipo << " $" << fixed << setprecision(2) << movs[i].monto << endl;
            }
        } else if (conDetalle) {
            cout << "Todavia no tiene ningun movimiendo cargado.\n";
        }
    };

    do {
        opcionprogram = menu();

        switch (opcionprogram) {
            case 1:
                mostrarSaldo();
                break;
            case 2:
                cout << "Ingrese el monto a ingresar: ";
                if (!(cin >> monto)) {
                    cout << "Entrada rara, no la entiendo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (monto > 0) {
                    saldo += monto;
                    movs.push_back({"Deposito", monto});
                    cout << "Deposito exitoso. Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "Monto invalido.\n";
                }
                break;
            case 3:
                cout << "Ingrese monto a retirar: ";
                if (!(cin >> monto)) {
                    cout << "Eso no es un numero.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (monto > 0 && monto <= saldo) {
                    saldo -= monto;
                    movs.push_back({"Retiro", monto});
                    cout << "Retiro exitoso. Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "Monto invalido o fondos insuficientes.\n";
                }
                break;
            case 4: {
                cout << "Alias actual de la cuenta es: " << alias << endl;
                cout << "Ingrese nuevo alias (sin espacios, sino explota todo): ";
                string nuevoAlias;
                cin >> nuevoAlias;
                if (nuevoAlias.size() > 2) {
                    alias = nuevoAlias;
                    cout << "Alias cambiando ok, ahora es: " << alias << endl;
                } else {
                    cout << "Alias demasiado cortito, no me gusta.\n";
                }
                break;
            }
            case 5: {
                cout << "Ingrese alias destino: ";
                string dest;
                cin >> dest;
                cout << "Monto a transferir: ";
                if (!(cin >> monto)) {
                    cout << "No entiendo cuanto quiere trasnferir.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (monto > 0 && monto <= saldo) {
                    saldo -= monto;
                    movs.push_back({"Transf a " + dest, monto});
                    cout << "Trasnferencia echa a " << dest << ". Nuevo saldo: $" << saldo << endl;
                } else {
                    cout << "No se puede hacer esa trasferencia.\n";
                }
                break;
            }
            case 6:
                mostrarSaldo(true);
                break;
            case 0:
                cout << "Chauuu, gracias por venir al cajero\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcionprogram != 0);

    return 0;
}

int menu() {
    int opcion;
    cout << "\nCAJERO\n";
    cout << "1 Consultar saldo simple\n";
    cout << "2 Depositar dinero\n";
    cout << "3 Retirar dinero\n";
    cout << "4 Cambiar alias de la cuentra\n";
    cout << "5 Hacer trasnferencia\n";
    cout << "6 Ver saldo con movimietos\n";
    cout << "0 Salir\n";
    cout << "Elija una opcion: ";
    if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        opcion = -1;
    }
    return opcion;
}
