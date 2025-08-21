#include <iostream>
using namespace std;


class Animal {
public:
    void comer() {
        cout << "Este animal puede comer." << endl;
    }
};


class Perro : public Animal {
public:
    void ladrar() {
        cout << "El perro puede ladrar." << endl;
    }
};

int main() {
    Perro miPerro;
    miPerro.comer(); 
    miPerro.ladrar(); 
    return 0;
}
