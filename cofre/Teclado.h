#ifndef TECLADO_H
#define TECLADO_H
#include <iostream>
using namespace std;
class Teclado {
public:
    int lerId() {
        int id;
        cin >> id;
        return id;
    }
    string lerSenha() {
        string senha;
        cin >> senha;
        return senha;
    }
};
#endif
