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

        display.iniciar();

        // Usuários padrão
        cofre.adicionarUsuario(Usuario(1, "", "1234", true));
        cofre.adicionarUsuario(Usuario(2, "", "5678", false));
    }

    void selecao() {

        display.mostrar("1-Login");
        char opcao = teclado.lerTecla();

        switch (opcao) {

            case '1':
                login();
                break;

            default:
                display.mostrar("Opcao invalida");
                delay(1500);
                break;
        }
    }

    bool validarAcessoAdmin() {

        display.mostrar("ID:");
        int id = teclado.lerId();

        display.mostrar("Senha:");
        String senha = teclado.lerSenha();

        return cofre.validarAdmin(id, senha);
    }

    void cadastrarUsuario() {

        if (!validarAcessoAdmin()) {
            display.mostrar("Sem permissao");
            delay(2000);
            return;
        }

        int id;
        String senha;
        bool repetido;

        Usuario* usuarios = cofre.getUsuarios();
        int qtdUsuarios = cofre.getQtdUsuarios();

        // Verifica ID repetido
        do {

            repetido = false;

            display.mostrar("Novo ID:");
            id = teclado.lerId();

            for (int i = 0; i < qtdUsuarios; i++) {

                if (usuarios[i].getId() == id) {
                    display.mostrar("ID existente");
                    delay(1500);
                    repetido = true;
                    break;
                }
            }

        } while (repetido);

        // Verifica senha repetida
        do {

            repetido = false;

            display.mostrar("Senha 4 dig:");
            senha = teclado.lerSenha();

            for (int i = 0; i < qtdUsuarios; i++) {

                if (usuarios[i].getSenha() == senha) {
                    display.mostrar("Senha existe");
                    delay(1500);
                    repetido = true;
                    break;
                }
            }

        } while (repetido);

        Usuario novo(id, "", senha, false);

        if (cofre.adicionarUsuario(novo)) {
            display.mostrar("Cadastrado!");
        } else {
            display.mostrar("Memoria cheia");
        }

        delay(2000);
    }

    void login() {

        display.mostrar("ID:");
        int id = teclado.lerId();

        display.mostrar("Senha:");
        String senha = teclado.lerSenha();

        if (cofre.autenticar(id, senha)) {

            tentativas = 0;

            cofre.abrir();

            display.mostrar("Cofre aberto");

            // Aqui você pode movimentar o servo:
            // servo.write(90);

            delay(3000);

            cofre.fechar();

            // servo.write(0);

            display.mostrar("Cofre fechado");
            delay(2000);

        } else {

            display.mostrar("Acesso negado");
            delay(2000);

            tentativas++;

            if (tentativas >= 3) {

                alarme.disparar();
                delay(5000);
                alarme.desligar();

                tentativas = 0;
            }
        }
    }
};

#endif
