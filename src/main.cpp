#include <Arduino.h>
#include "functies.h"

void setup() {
    initialisatie();                                       // Configureer de pinnen
    resettest();                                           // Zet alles uit bij de start
}       

void loop() {  
    if (detectprobe()) {                                   // Controleer of detectprobe actief is
        resettest();                                       // Reset dus zet alles uit
        return;
    }     
    starttest();                                           // Wachten op start

    bool result = schakelrelais(HIGH, LOW);                // Schakel relais 1
    if(result) result = schakelrelais(HIGH, HIGH);         // Schakel relais 1 en 2
    if(result) result = schakelrelais(HIGH, LOW);          // Schakel relais 1 
    if(result) result = schakelrelais(HIGH, HIGH);         // Schakel relais 1 en 2
    if(result) result = schakelrelais(LOW, HIGH);          // Schakel relais 2
    if(result) result = schakelrelais(HIGH, HIGH);         // Schakel relais 1 en 2 
    if(result) result = schakelrelais(HIGH, LOW);          // Schakel relais 1
    if(result) {                                           // Test geslaagd dus reset test
        Serial.println("Test geslaagd");
        digitalWrite(relais_1, LOW);
        digitalWrite(relais_2, LOW); 
        digitalWrite(led_groen, HIGH);  
    }                              
    else {
        Serial.println("Test mislukt");                    // Test mislukt 
        digitalWrite(relais_1, LOW);
        digitalWrite(relais_2, LOW);
    }
}