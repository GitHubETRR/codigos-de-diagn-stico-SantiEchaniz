#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

int menu() {
    int opcion;
    cout << "\nCAJERO\n";
    cout << "1 Consultar saldo simple\n";
    cout << "2 Depositar dinero\n";
    cout << "3 Retirar dinero\n";
    cout << "4 Cambiar alias de la cuenta\n";
    cout << "5 Hacer transferencia\n";
    cout << "6 Ver saldo con movimientos\n";
    cout << "0 Salir\n";
    cout << "Elija una opcion: ";
    if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        opcion = -1;
    }
    return opcion;
}

//CLASE MOVIMIENTO
class Movimiento {
private:
    string tipo;
    double monto;

public:
    Movimiento(const string& t, double m) : tipo(t), monto(m) {}

    string getTipo() const { return tipo; }
    double getMonto() const { return monto; }
};

//CLASE CUENTA
class Cuenta {
protected:
    double saldo;
    string alias;
    vector<Movimiento> movs;

protected:
    void registrarMovimiento(const string& tipo, double monto) {
        movs.emplace_back(tipo, monto);
    }

public:
    Cuenta(double saldoInicial, const string& aliasInicial)
        : saldo(saldoInicial), alias(aliasInicial) {}

    virtual ~Cuenta() {}

    double getSaldo() const { return saldo; }
    string getAlias() const { return alias; }

    void setAlias(const string& nuevoAlias) {
        alias = nuevoAlias;
    }

    void mostrarSaldo(bool conDetalle = false) const {
        cout << "Su saldo es: $" << fixed << setprecision(2) << saldo << endl;
        if (conDetalle && !movs.empty()) {
            cout << "Ultimos movimientos:" << endl;
            int limite = movs.size() > 5 ? 5 : (int)movs.size();
            for (int i = (int)movs.size() - limite; i < (int)movs.size(); ++i) {
                cout << "- " << movs[i].getTipo()
                     << " $" << fixed << setprecision(2)
                     << movs[i].getMonto() << endl;
            }
        } else if (conDetalle) {
            cout << "Todavia no tiene ningun movimiento cargado.\n";
        }
    }

    // se redefinen en las clases hijas
    virtual void depositar(double monto) = 0;
    virtual bool retirar(double monto) = 0;
    virtual bool transferir(const string& destino, double monto) = 0;
};

// CLASE CUENTA CONCRETA
class CuentaBancariaSimple : public Cuenta {
public:
    CuentaBancariaSimple(double saldoInicial, const string& aliasInicial)
        : Cuenta(saldoInicial, aliasInicial) {}

    void depositar(double monto) override {
        saldo += monto;
        registrarMovimiento("Deposito", monto);
    }

    bool retirar(double monto) override {
        if (monto <= saldo) {
            saldo -= monto;
            registrarMovimiento("Retiro", monto);
            return true;
        }
        return false;
    }

    bool transferir(const string& destino, double monto) override {
        if (monto <= saldo) {
            saldo -= monto;
            registrarMovimiento("Transferencia a " + destino, monto);
            return true;
        }
        return false;
    }
};

//CLASE CAJERO AUTOMATICO 
class CajeroAutomatico {
private:
    Cuenta* cuenta;

    double leerMonto(const string& mensaje) {
        double monto;
        while (true) {
            cout << mensaje;
            if (cin >> monto && monto > 0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return monto;
            }
            cout << "Monto invalido. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

public:
    explicit CajeroAutomatico(Cuenta* c) : cuenta(c) {}

    void ejecutar() {
        int opcion;
        do {
            opcion = menu();
            switch (opcion) {
                case 1: // Consultar saldo simple
                    cout << "Alias de la cuenta: " << cuenta->getAlias() << "\n";
                    cuenta->mostrarSaldo(false);
                    break;

                case 2: { // Transferir
                    double monto = leerMonto("Ingrese el monto a depositar: ");
                    cuenta->depositar(monto);
                    cout << "Deposito realizado correctamente.\n";
                    break;
                }

                case 3: { // Retirar
                    double monto = leerMonto("Ingrese el monto a retirar: ");
                    if (cuenta->retirar(monto)) {
                        cout << "Retiro exitoso.\n";
                    } else {
                        cout << "Fondos insuficientes.\n";
                    }
                    break;
                }

                case 4: { // Cambiar alias
                    string nuevoAlias;
                    cout << "Ingrese el nuevo alias (sin espacios): ";
                    cin >> nuevoAlias;
                    cuenta->setAlias(nuevoAlias);
                    cout << "Alias actualizado correctamente.\n";
                    break;
                }

                case 5: { // Transferencia
                    string destino;
                    cout << "Ingrese el alias de destino (sin espacios): ";
                    cin >> destino;
                    double monto = leerMonto("Ingrese el monto a transferir: ");
                    if (cuenta->transferir(destino, monto)) {
                        cout << "Transferencia realizada a " << destino << "\n";
                    } else {
                        cout << "No se pudo realizar la transferencia (fondos insuficientes).\n";
                    }
                    break;
                }

                case 6: // Ver saldo con movimientos
                    cout << "Alias de la cuenta: " << cuenta->getAlias() << "\n";
                    cuenta->mostrarSaldo(true);
                    break;

                case 0:
                    cout << "Saliendo del cajero...\n";
                    break;

                default:
                    cout << "Opcion invalida. Intente nuevamente.\n";
                    break;
            }
        } while (opcion != 0);
    }
};

int main() {
    // cuenta de prueba
    CuentaBancariaSimple miCuenta(10000.0, "santu.caja");

    // Cajero y le paso la cuenta
    CajeroAutomatico cajero(&miCuenta);

    // Inicio el menú del cajero
    cajero.ejecutar();

    return 0;
}
