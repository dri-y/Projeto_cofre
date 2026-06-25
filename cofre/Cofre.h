#ifndef COFRE_H
#define COFRE_H
#include <vector>
#include "Usuario.h"
using namespace std;
class Cofre {
private:
    vector<Usuario> usuarios;
    bool aberto;
public:
    Cofre() {
        aberto = false;
    }
    
    void adicionarUsuario(Usuario usuario) {
        usuarios.push_back(usuario);
    }
    
    vector<Usuario> getUsuarios() {
        return usuarios;
    }
    
    bool autenticar(int id, string senha) {
        for(int i = 0; i < usuarios.size(); i++) {
            if(usuarios[i].getId() == id &&
               usuarios[i].verificarSenha(senha)) {
                return true;
            }
        }
        return false;
    }
    bool validarAdmin(int id, string senha) {
       for (int i = 0; i < usuarios.size(); i++) {
           if (usuarios[i].getId() == id && usuarios[i].getSenha() == senha) {
            return usuarios[i].isAdmin();
           }
       }
        return false;
    }
    
    void abrir() {
        aberto = true;
    }
    
    void fechar() {
        aberto = false;
    }
    
    bool estaAberto() {
        return aberto;
    }
};
#endif