#ifndef USUARIO_H
#define USUARIO_H
#include <string>
using namespace std;
class Usuario {
private:
    int id;
    string nome;
    string senha;
    bool admin;

public:
	Usuario() {
    id = 0;
    nome = "";
    senha = "";
    admin = false;
}
    Usuario(int id, string nome, string senha, bool admin = false) {
        this->id = id;
        this->nome = nome;
        this->senha = senha;
        this->admin = admin;
    }
    
    int getId() {
        return id;
    }

    string getNome() {
        return nome;
    }

    string getSenha() {
        return senha;
    }

    bool isAdmin() {
        return admin;
    }
    
    bool verificarSenha(string tentativa) {
        return senha == tentativa;
    }
};
#endif
