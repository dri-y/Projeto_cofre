#ifndef TECLADO_H
#define TECLADO_H

#include <Ard#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>
#include <Keypad.h>
#include "Display.h" 

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

    
    String lerSenha(Display &display, String textoBase = "Senha:") {
        String senha = "";
        
        while (true) {
            
            String mascara = "";
            for (int i = 0; i < senha.length(); i++) {
                mascara += "*";
            }
            display.mostrar(textoBase + " " + mascara);

            
            if (senha.length() == 4) {
                delay(300);
                return senha;
            }

            char tecla = lerTecla();

            
            if (tecla == '*' && senha.length() > 0) {
                senha.remove(senha.length() - 1);
            } 
           
            else if (tecla >= '0' && tecla <= '9') {
                senha += tecla;
            }
        }
    }

    
    int lerId(Display &display, String textoBase = "ID:") {
        String idStr = "";

        while (true) {
           
            display.mostrar(textoBase + " " + idStr);

            char tecla = lerTecla();

            
            if (tecla == '#' && idStr.length() > 0) {
                return idStr.toInt();
            }
            
            else if (tecla == '*' && idStr.length() > 0) {
                idStr.remove(idStr.length() - 1);
            }
            
            else if (tecla >= '0' && tecla <= '9') {
                idStr += tecla;
            }
        }
    }
};

#endifuino.h>
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
            if (tecla != NO_KEY) {
            Serial.print("Tecla lida: ");
            Serial.println(tecla);
        }
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

            if (tecla == '#') {   
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
