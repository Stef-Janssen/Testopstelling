#include <Arduino.h>
#include "functies.h"

// Pin definities
#define meting 2
#define relais_2 4
#define relais_1 7
#define led_geel 9
#define led_groen 10
#define led_rood 11
#define drukknop 12
#define detect_probe 13

uint16_t wachttijd = 500;                        // Aantal ms tussen aansturen relais en starten meting
uint16_t indicatortijd = 250;                    // Aantal ms dat indicator lampje aan is tussen de stappen

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
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_rood, LOW);
    digitalWrite(relais_1, LOW);
    digitalWrite(relais_2, LOW);
}

// Functie om te controleren of de detect probe ingedrukt
bool detectprobe() {
    if (digitalRead(detect_probe) != LOW) {
        Serial.println("Detect probe is laag");
        digitalWrite(led_geel, LOW);
        digitalWrite(led_rood, HIGH);
        return true;
    }
    return false;
}

// Functie om te wachten op de startvoorwaarden
void starttest() {
    Serial.println("Wachten op startvoorwaarden");
    while (digitalRead(drukknop) == HIGH || digitalRead(detect_probe) == HIGH) {
    }
    resettest();
    Serial.println("Test gestart");
    digitalWrite(led_groen, LOW);
}

// Stap 1 en 5: relais 1 inschakelen en meting uitvoeren
bool stap1_5() {
    if (detectprobe()) {
        return false;
    }
    digitalWrite(led_geel, LOW);
    digitalWrite(relais_1, HIGH);
    digitalWrite(relais_2, LOW);
    delay(wachttijd);
    
    if (digitalRead(meting) != HIGH) {
        Serial.println("Stap 1_5 geslaagd");
        digitalWrite(led_geel, HIGH);
        delay(indicatortijd);
        return true;
    } else {
        Serial.println("Stap 1_5 mislukt");
        digitalWrite(led_rood, HIGH);
        return false;
    }
}

// Stap 2 en 4: relais 1 en 2 inschakelen en meting uitvoeren
bool stap2_4() {
    if (detectprobe()) {
        return false;
    }
    digitalWrite(led_geel, LOW);
    digitalWrite(relais_1, HIGH);
    digitalWrite(relais_2, HIGH);
    delay(wachttijd);
    
    if (digitalRead(meting) != HIGH) {
        Serial.println("Stap 2_4 geslaagd");
        digitalWrite(led_geel, HIGH);
        delay(indicatortijd);
        return true;
    } else {
        Serial.println("Stap 2_4 mislukt");
        digitalWrite(led_rood, HIGH);
        return false;
    }
}

// Stap 3: relais 2 inschakelen en meting uitvoeren
bool stap3() {
    if (detectprobe()) {
        return false;
    } 
    digitalWrite(led_geel, LOW);
    digitalWrite(relais_1, LOW);
    digitalWrite(relais_2, HIGH);
    delay(wachttijd);
    
    if (digitalRead(meting) != HIGH) {
        Serial.println("Stap 3 geslaagd");
        digitalWrite(led_geel, HIGH);
        delay(indicatortijd);
        return true;
    } else {
        Serial.println("Stap 3 mislukt");
        digitalWrite(led_rood, HIGH);
        return false;
    }
}

// Functie om geslaagde test aan te geven
void testgeslaagd() {
    Serial.println("test geslaagd");
    digitalWrite(led_geel,LOW);
    digitalWrite(led_groen,HIGH);
}

// Functie die de test eindigt
void eindigtest() {
    Serial.println("Test afgerond");
    digitalWrite(relais_1, LOW);
    digitalWrite(relais_2, LOW);
}