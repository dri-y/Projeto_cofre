#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include "Usuario.h"
#include "Cofre.h"
using namespace std;
class Display {
public:
    void mostrar(string texto) {
        cout << texto << endl;
    }
    void ListaUsuarios(Usuario* usuarios, int qtdUsuarios) {
    cout << "\n=== USUARIOS CADASTRADOS ===\n";

    for (int i = 0; i < qtdUsuarios; i++) {
    cout
        << "ID: " << usuarios[i].getId()
        << " | Nome: " << usuarios[i].getNome()
        << endl;
    }
    cout << "============================\n";
    }
};
#endif
