#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <vector>
#include "Usuario.h"
#include "Cofre.h"
using namespace std;
class Display {
public:
    void mostrar(string texto) {
        cout << texto << endl;
    }
    void ListaUsuarios(vector<Usuario> usuarios) {
    cout << "\n=== USUÁRIOS CADASTRADOS ===\n";

    for (int i = 0; i < usuarios.size(); i++) {
    cout
        << "ID: " << usuarios[i].getId()
        << " | Nome: " << usuarios[i].getNome()
        << endl;
    }
    cout << "============================\n";
    }
};
#endif
