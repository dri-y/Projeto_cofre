#ifndef COFRE_H
#define COFRE_H

#include <iostream>
#include "Usuario.h"
using namespace std;

class Cofre {
private:
    static int total_usuarios = 100;
    Usuario usuarios[total_usuarios];
    int qtdUsuarios;
    bool aberto;
public:
    Cofre() {
        aberto = false;
        qtdUsuarios = 0;
    }
    
    void adicionarUsuario(Usuario user) {
        if(qtdUsuarios < total_usuarios){
        	usuarios[qtdUsuarios] = user;
        	qtdUsuarios++;
        	return true;
		}
		return false;
    }
    
    Usuario* getUsuarios() {
        return usuarios;
    }
    int getqtdUsuarios(){
    	return qtdUsuarios;
	}
    bool autenticar(int id, string senha) {
        for(int i = 0; i < qtdUsuarios; i++) {
            if(usuarios[i].getId() == id &&
               usuarios[i].verificarSenha(senha)) {
                return true;
            }
        }
        return false;
    }
    bool validarAdmin(int id, string senha) {
       for (int i = 0; i < qtdUsuarios; i++) {
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
    void ordenarUsuariosPorId(){
    	for(int i=0;i< qtdUsuarios-1; i++){
    		for(int j=0; j < qtdUsuarios-i-1; j++){
    			if(usuarios[j]).getId()>usuarios[j+1].getId()){
    				Usuario temp = usuarios[j];
    				usuarios[j] = usuarios[j+1];
    				usuarios[j+1] = temp;
				}
			}
		}
	}
};
#endif
