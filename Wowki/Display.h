#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Usuario.h"

class Display {
private:
    LiquidCrystal_I2C lcd;

public:
    Display() : lcd(0x27, 20, 4) {}

    void iniciar() {
        lcd.init();
        lcd.backlight();
    }

    void mostrar(String texto) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(texto);
    }

    void listaUsuarios(Usuario* usuarios, int qtdUsuarios) {
        lcd.clear();

        for (int i = 0; i < qtdUsuarios; i++) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ID:");
            lcd.print(usuarios[i].getId());

            lcd.setCursor(0, 1);
            lcd.print(usuarios[i].getNome());

            delay(1000); 
        }
    }
};

#endif
