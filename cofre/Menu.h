#ifndef MENU_H
#define MENU_H

#include "Cofre.h"
#include "Display.h"
#include "Teclado.h"
#include "Alarme.h"

using namespace std;

class Menu {
private:
    Cofre cofre;
    Display display;
    Teclado teclado;
    Alarme alarme;

    int tentativas;
    int acessoGlobal;

public:

   Menu() {
    acessoGlobal = 0;
    tentativas = 0;

    cofre.adicionarUsuario(Usuario(1,"carlos","123",true));
    cofre.adicionarUsuario(Usuario(2,"maria","456",false));

    //cout << "Quantidade de usuarios: "  << cofre.getUsuarios().size() << endl;
}

    void selecao() {

        int opcao;

        display.mostrar("1 login");
        display.mostrar("2 lista de usuarios");
        display.mostrar("3 cadastrar usuario");

        cin >> opcao;

        switch(opcao) {

            case 1:
                login();
                break;

            case 2:

                if (validarAcessoAdmin()) {

                    display.ListaUsuarios(cofre.getUsuarios(), cofre.getqtdUsuarios());

                    display.mostrar("pressione 1 para voltar");
                    cin >> acessoGlobal;

                    if (acessoGlobal == 1) {
                        selecao();
                    }
                    else {

                        display.mostrar("valor invalido!");

                        while (acessoGlobal != 1) {
                            display.mostrar("pressione 1 para voltar");
                            cin >> acessoGlobal;
                        }

                        selecao();
                    }
                }

                break;

            case 3:
                cadastrarUsuario();
                break;

            default:
                display.mostrar("opcao invalida");
        }
    }

    bool validarAcessoAdmin() {

    display.mostrar("Qual o seu ID:");
    int id = teclado.lerId();

    display.mostrar("Qual a sua Senha:");
    string senha = teclado.lerSenha();

 Usuario* usuarios = cofre.getUsuarios();
 int qtdUsuarios = cofre.getqtdUsuarios();

   // cout << "Quantidade no cofre: " << usuarios.size() << endl;

    for (int  i = 0; i < qtdUsuarios; i++) {
    	
        if (usuarios[i].getId() == id && usuarios[i].getSenha() == senha) {

            return usuarios[i].isAdmin();
        }
    }

    return false;
}

    void cadastrarUsuario() {

        if (!validarAcessoAdmin()) {
            return;
        }

        int id;
        string nome;
        string senha;

        Usuario* usuarios = cofre.getUsuarios();
        int qtdUsuarios = cofre.getqtdUsuarios();

        bool repetido;

        do {

            repetido = false;

            display.mostrar("Digite um ID:");
            cin >> id;

            for (int i = 0; i < qtdUsuarios; i++) {

                if (id == usuarios[i].getId()) {

                    display.mostrar("ID ja cadastrado!");
                    repetido = true;
                    break;
                }
            }

        } while (repetido);

        do {

            repetido = false;

            display.mostrar("Digite um Nome:");
            getline(cin >> ws, nome);

            for (int i = 0; i < qtdUsuarios; i++) {

                if (nome == usuarios[i].getNome()) {

                    display.mostrar("Nome ja cadastrado!");
                    repetido = true;
                    break;
                }
            }

        } while (repetido);

        do {

            repetido = false;

            display.mostrar("Digite uma senha numerica:");
            getline(cin >> ws, senha);

            for (int i = 0; i <qtdUsuarios; i++) {

                if (senha == usuarios[i].getSenha()) {

                    display.mostrar("Senha ja cadastrada!");
                    repetido = true;
                    break;
                }
            }

        } while (repetido);

        Usuario usuario(id, nome, senha);

        cofre.adicionarUsuario(usuario);

        display.mostrar("Usuario cadastrado com sucesso!");

        display.mostrar("pressione 1 para voltar");
        cin >> acessoGlobal;

        if (acessoGlobal == 1) {

            selecao();

        } else {

            display.mostrar("valor invalido!");

            while (acessoGlobal != 1) {

                display.mostrar("pressione 1 para voltar");
                cin >> acessoGlobal;
            }

            selecao();
        }
    }

    void login() {

        display.mostrar("Qual o seu ID:");
        int id = teclado.lerId();

        display.mostrar("Qual a sua Senha:");
        string senha = teclado.lerSenha();

        if (cofre.autenticar(id, senha)) {

            cofre.abrir();

            display.mostrar("Cofre Aberto");

            tentativas = 0;

            display.mostrar("para fechar o cofre digite 5");

            int i;
            cin >> i;

            if (i == 5) {

                cofre.fechar();

                display.mostrar("Cofre Fechado");

                selecao();
            }

        } else {

            display.mostrar("Acesso Negado");

            tentativas++;

            if (tentativas >= 3) {

                alarme.disparar();

                tentativas = 0;
            }
        }
    }
};

#endif
