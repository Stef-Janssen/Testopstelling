#ifndef functies_h
#define functies_h

// Pin definities
#define meting 2
#define relais_2 4
#define relais_1 7
#define led_geel 9
#define led_groen 10
#define led_rood 11
#define drukknop 12
#define detect_probe 13

// Functies
void initialisatie();
void resettest();
bool detectprobe();
void starttest(); 
bool schakelrelais(int relais1_status, int relais2_status);

#endif