#ifndef COFRE_H
#define COFRE_H

#include "Usuario.h"
#include <Servo.h> 

using namespace std;

class Cofre {
private:
    static const int total_usuarios = 10;
    Usuario usuarios[total_usuarios];
    int qtdUsuarios;
    bool aberto;

    Servo servoTranca;    
    int pinoServo;        
    int pinoFimDeCurso;   

    const int ANGULO_TRANCADO = 0;
    const int ANGULO_DESTRANCADO = 90;

public:
    Cofre(int pinServo = 12, int pinFimDeCurso = 13) {
        aberto = false;
        qtdUsuarios = 0;
        pinoServo = pinServo;
        this->pinoFimDeCurso = pinFimDeCurso;
    }
    
    void iniciar() {
        servoTranca.attach(pinoServo);
        servoTranca.write(ANGULO_TRANCADO); 
        pinMode(pinoFimDeCurso, INPUT);     
    }
    
    bool adicionarUsuario(Usuario user) {
        if(qtdUsuarios < total_usuarios){
            usuarios[qtdUsuarios] = user;
            qtdUsuarios++;
            return true;
        }
        return false;
    }
    
    Usuario* getUsuarios() { return usuarios; }
    int getQtdUsuarios() { return qtdUsuarios; }

    bool autenticar(int id, String senha) {
        for(int i = 0; i < qtdUsuarios; i++) {
            if(usuarios[i].getId() == id && usuarios[i].verificarSenha(senha)) {
                return true;
            }
        }
        return false;
    }

    bool validarAdmin(int id, String senha) {
       for (int i = 0; i < qtdUsuarios; i++) {
           if (usuarios[i].getId() == id && usuarios[i].getSenha() == senha) {
                return usuarios[i].isAdmin();
           }
       }
        return false;
    }
    
  
    bool portaEncostada() {
        return digitalRead(pinoFimDeCurso) == HIGH; 
    }
    
    void abrir() {
        aberto = true;
        servoTranca.write(ANGULO_DESTRANCADO);
        delay(500); 
    }
    
    void fechar() {
        aberto = false;
        servoTranca.write(ANGULO_TRANCADO);
        delay(500);
    }
    
    bool estaAberto() { return aberto; }

    void ordenarUsuariosPorId(){
        for(int i=0; i < qtdUsuarios-1; i++){
            for(int j=0; j < qtdUsuarios-i-1; j++){
                if(usuarios[j].getId() > usuarios[j+1].getId()){ 
                    Usuario temp = usuarios[j];
                    usuarios[j] = usuarios[j+1];
                    usuarios[j+1] = temp;
                }
            }
        }
    }
};

#endif
