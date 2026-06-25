#ifndef ALARME_H
#define ALARME_H

#include <Arduino.h>

class Alarme {
private:
    int pinoBuzzer;

public:
    Alarme(int pino = 3) {
        pinoBuzzer = pino;
        pinMode(pinoBuzzer, OUTPUT);
    }

    void disparar() {
        tone(pinoBuzzer, 1000); // Emite um som de 1000 Hz
    }

    void desligar() {
        noTone(pinoBuzzer); // Desliga o buzzer
    }
};

#endif
