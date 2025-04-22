#include <Arduino.h>
#include "functies.h"

uint16_t wachttijd = 125;                                  // Aantal ms tussen aansturen relais en starten meting
uint16_t indicatortijd = 100;                              // Aantal ms dat indicator lampje aan is tussen de stappen

// Functie om de pinnen in te stellen
void initialisatie() {
    Serial.begin(9600);
    pinMode(meting, INPUT_PULLUP);
    pinMode(relais_2, OUTPUT);
    pinMode(relais_1, OUTPUT);
    pinMode(led_geel, OUTPUT);
    pinMode(led_groen, OUTPUT);
    pinMode(led_rood, OUTPUT);
    pinMode(drukknop, INPUT_PULLUP);
    pinMode(detect_probe, INPUT_PULLUP);
    Serial.println("Initialisatie gelukt");
}

// Functie om de test te resetten
void resettest() {
    digitalWrite(led_geel, LOW);
    digitalWrite(led_groen, LOW);
    digitalWrite(led_rood, LOW);
    digitalWrite(relais_1, LOW);
    digitalWrite(relais_2, LOW);
}

// Functie om te controleren of de detect probe ingedrukt
bool detectprobe() {
    if (digitalRead(detect_probe) != LOW) {
        Serial.println("Detect probe is laag");
        digitalWrite(led_geel, LOW);        // Zet alle LED's uit
        digitalWrite(led_groen, LOW);
        digitalWrite(led_rood, LOW);
        return true;
    } else {
        digitalWrite(led_geel, HIGH);  
        return false;
    }

}

// Functie om te wachten op de startvoorwaarden
void starttest() {
    delay(wachttijd);
    Serial.println("Wachten op startvoorwaarden");
    while (true) {
        if (digitalRead(detect_probe) != LOW) {
            resettest();
            return;
        }

        if (digitalRead(drukknop) == LOW && digitalRead(detect_probe) == LOW) {
            break;
        }
    }

    Serial.println("Test gestart");
    digitalWrite(led_groen, LOW);
    digitalWrite(led_rood, LOW);
}

// Functie voor relais te schakelen
bool schakelrelais(int status_relais1, int status_relais2) {
    if (detectprobe()) {
        return false;
    }
    
    digitalWrite(led_geel, LOW);
    digitalWrite(relais_1, status_relais1);
    digitalWrite(relais_2, status_relais2);
    delay(wachttijd);
    
    if (digitalRead(meting) != HIGH) {
        Serial.println("Stap geslaagd");
        digitalWrite(led_geel, HIGH);
        delay(indicatortijd);
        return true;
    } else {
        Serial.println("Stap mislukt");
        digitalWrite(led_rood, HIGH);
        return false;
    } 
}