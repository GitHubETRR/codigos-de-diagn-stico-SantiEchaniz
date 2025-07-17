#include <iostream>
#include <cstdlib>
#include <ctime>    
#define numeroSecreto 23

using namespace std;

int main() {
    int intento = 0;
    int intentos = 0;


    cout << "adivina el numero =" << endl;
    cout << "Deci un numero del 1 al 100" << endl;

    do {
        cout << "Proba: ";
        cin >> intento;
        intentos++;

        if (intento < numeroSecreto) {
            cout << "Demasiado bajo. Intenta otra vez." << endl;
        } else if (intento > numeroSecreto) {
            cout << "Demasiado alto. Intenta otra vez." << endl;
        } else {
            cout << "Adivinaste el numero en "<< intentos << " intentos" << endl;
            
        }
    } while (intento != numeroSecreto);

    return 0;
}
