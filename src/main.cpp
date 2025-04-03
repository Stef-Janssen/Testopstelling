#include <Arduino.h>
#include "functies.h"

void setup() {
    initialisatie();                             // Configureer de pinnen
    resettest();                                 // Zet alles uit bij de start
}

void loop() {
    starttest();                                 // Wachten op start
    if (stap1_5()) {                             // Stap 1 uitvoeren
        if (stap2_4()) {                         // Stap 2 uitvoeren
            if (stap3()) {                       // Stap 3 uitvoeren                             
                if (stap2_4())  {                // Stap 4 uitvoeren
                    if (stap1_5())  {            // Stap 5 uitvoeren
                        testgeslaagd();          // test is gelukt
                    }
                }
            }    
        }
    }
    eindigtest();                                // Test eindigen
}