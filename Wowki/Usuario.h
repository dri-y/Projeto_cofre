#ifndef USUARIO_H
#define USUARIO_H
#include <Arduino.h>
using namespace std;
class Usuario {
private:
    int id;
    String nome;
    String senha;
    bool admin;

public:
	Usuario() {
    id = 0;
    nome = "";
    senha = "";
    admin = false;
}
    Usuario(int id, String nome, String senha, bool admin = false) {
        this->id = id;
        this->nome = nome;
        this->senha = senha;
        this->admin = admin;
    }
    
    int getId() {
        return id;
    }

    String getNome() {
        return nome;
    }

    String getSenha() {
        return senha;
    }

    bool isAdmin() {
        return admin;
    }
    
    bool verificarSenha(String tentativa) {
        return senha == tentativa;
    }
};
#endif
