#ifndef MENU_H
#define MENU_H

#include "Cofre.h"
#include "Display.h"
#include "Teclado.h"
#include "Alarme.h"

class Menu {
private:
    Cofre cofre;
    Display display;
    Teclado teclado;
    Alarme alarme;
    int tentativas;

public:
    Menu() {
        tentativas = 0;
        
       
        cofre.adicionarUsuario(Usuario(1, "Admin", "1234", true));
        cofre.adicionarUsuario(Usuario(2, "Carlos", "5678", false));
    }

    void iniciar() {
        display.iniciar();
        cofre.iniciar();
    }

    void selecao() {
        display.mostrar("1-Login             3-Cadastrar         2-Listar"); 
        char opcao = teclado.lerTecla();

        switch (opcao) {
            case '1':
                login();
                break;

            case '2':
                listarUsuarios(); 
                break;

            case '3':
                cadastrarUsuario(); 
                break;

            default:
                display.mostrar("Opcao invalida");
                delay(1500);
                break;
        }
    }

    bool validarAcessoAdmin() {
        
        int id = teclado.lerId(display, "Admin ID:");
        String senha = teclado.lerSenha(display, "Admin Senha:");

        return cofre.validarAdmin(id, senha);
    }

    void listarUsuarios() {
        if (!validarAcessoAdmin()) {
            display.mostrar("Sem permissao");
            delay(1000);
            return;
        }

        display.mostrar("Ordenando...");
        cofre.ordenarUsuariosPorId(); 
        delay(1000);

        Usuario* lista = cofre.getUsuarios();
        int qtd = cofre.getQtdUsuarios();

        if (qtd == 0) {
            display.mostrar("Nenhum usuario");
            delay(1000);
        } else {
            display.listaUsuarios(lista, qtd); 
        }
    }

    void cadastrarUsuario() {
        if (!validarAcessoAdmin()) {
            display.mostrar("Sem permissao");
            delay(1000);
            return;
        }

        int id;
        String senha;
        bool repetido;

        Usuario* usuarios = cofre.getUsuarios();
        int qtdUsuarios = cofre.getQtdUsuarios();

        do {
            repetido = false;
           
            id = teclado.lerId(display, "Novo ID:");

            for (int i = 0; i < qtdUsuarios; i++) {
                if (usuarios[i].getId() == id) {
                    display.mostrar("ID existente");
                    delay(1500);
                    repetido = true;
                    break;
                }
            }
        } while (repetido);

        do {
            repetido = false;
            
            senha = teclado.lerSenha(display, "Senha 4 dig:");

            for (int i = 0; i < qtdUsuarios; i++) {
                if (usuarios[i].getSenha() == senha) {
                    display.mostrar("Senha existe");
                    delay(1500);
                    repetido = true;
                    break;
                }
            }
        } while (repetido);

        Usuario novo(id, "User " + String(id), senha, false); 

        if (cofre.adicionarUsuario(novo)) {
            display.mostrar("Cadastrado!");
        } else {
            display.mostrar("Memoria cheia");
        }

        delay(1000);
    }

    
    void login() {
        
        int id = teclado.lerId(display, "ID:");
        String senha = teclado.lerSenha(display, "Senha:");

        if (cofre.autenticar(id, senha)) {
            tentativas = 0; 
            
            
            cofre.abrir();
            display.mostrar("Cofre aberto!");
            delay(1000); 

            display.mostrar("Porta aberta...");

            
            while (cofre.portaEncostada() == false) {
                delay(50); 
            }

            display.mostrar("Fechando tranca");
            delay(1000);
            cofre.fechar(); 
            
            display.mostrar("Cofre trancado");
            delay(1000);
        } else {
            display.mostrar("Acesso negado");
            delay(1000);
            tentativas++;

            
            if (tentativas >= 3) {
                alarme.disparar(); 
                
                bool liberado = false;
                while (!liberado) {
                    display.mostrar("BLOQUEADO!      Insira Admin ID:");
                    int adminId = teclado.lerId(display, "Admin ID:");
                    
                    display.mostrar("Admin Senha:");
                    String adminSenha = teclado.lerSenha(display, "Admin Senha:");
                    
                    
                    if (cofre.validarAdmin(adminId, adminSenha)) {
                        liberado = true; 
                        display.mostrar("Alarme desligado");
                        delay(1000);
                    } else {
                        display.mostrar("Admin invalido!");
                        delay(1000);
                       
                    }
                }
                
                alarme.desligar(); 
                tentativas = 0;    
            }
        }
    }
};

#endif
