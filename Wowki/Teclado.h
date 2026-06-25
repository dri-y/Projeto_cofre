#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>
#include <Keypad.h>

class Teclado {
private:
    const byte LINHAS = 4;
    const byte COLUNAS = 4;

    char teclas[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    byte pinosLinhas[4] = {4, 5, 6, 7};
    byte pinosColunas[4] = {8, 9, 10, 11};

    Keypad keypad = Keypad(makeKeymap(teclas),
                           pinosLinhas,
                           pinosColunas,
                           LINHAS,
                           COLUNAS);

public:
    char lerTecla() {
        char tecla;

        do {
            tecla = keypad.getKey();
        } while (tecla == NO_KEY);

        return tecla;
    }

    String lerSenha() {
        String senha = "";

        while (senha.length() < 4) {
            char tecla = lerTecla();

            if (tecla >= '0' && tecla <= '9') {
                senha += tecla;
            }
        }

        return senha;
    }

    int lerId() {
        String texto = "";

        while (true) {
            char tecla = lerTecla();

            if (tecla == '#') {   // '#' confirma a entrada
                break;
            }

            if (tecla >= '0' && tecla <= '9') {
                texto += tecla;
            }
        }

        return texto.toInt();
    }
};

#endif
