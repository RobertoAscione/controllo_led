// versione 1.2
/*
Comando Serial	Azione
0	Nessun effetto (LED spenti)
1	Effetto dissolvenza (FADE)
2	Effetto modulato casuale (RANDOM_MODULATION)
d	Attiva/disattiva stampe debug
Comando Serial	Azione
s<number>	Setta velocità fade (ms) — s50 = fade veloce
r<number>	Setta rotazione (ms) — r200 = LED cambia ogni 200ms
b<number>	Setta blink (ms) — b100 = lampeggio ogni 100ms
v<number>	Setta sensibilità VOICE_SIM — v2.0 = più rapida
d	Toggle modalità debug
0, 1, 2	Cambia effetto attivo


*/

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

#define MAX_LEDS 8

// Tipi di effetti disponibili
enum EffectType {
    NONE,
    RANDOM_BLINK,
    ROTATE,
    FADE,
    VOICE_SIM,
    RANDOM_MODULATION
};

class LEDController {
public:
    // Costruttore: pin dei LED e numero di LED
    LEDController(uint8_t ledPins[], uint8_t count);
    
    // Inizializza i pin
    void begin();

    // Imposta o rimuove un effetto
    void setEffect(EffectType effect);
    void clearEffect();

    // Da richiamare nel loop()
    void update();

    // Parametri configurabili
    void setBlinkInterval(unsigned long interval);
    void setRotationSpeed(unsigned long speed);
    void setFadeSpeed(unsigned long speed);
    void setVoiceSensitivity(float factor);

    // Debug mode
    void setDebug(bool enable);

private:
    uint8_t _pins[MAX_LEDS];
    uint8_t _count;
    EffectType _effect;
    unsigned long _lastUpdate;

    // Parametri effetti
    unsigned long _blinkInterval;
    unsigned long _rotationSpeed;
    unsigned long _fadeSpeed;
    float _voiceFactor;

    // Stato per FADE
    int _fadeValue;
    int _fadeDirection;

    // Stato per ROTATE
    uint8_t _currentLED;

    // Stato per RANDOM_MODULATION
    unsigned long _nextUpdate[MAX_LEDS];
    unsigned long _modInterval[MAX_LEDS];
    uint8_t _targetValue[MAX_LEDS];
    uint8_t _currentValue[MAX_LEDS];
    int8_t _direction[MAX_LEDS];

    // Flag debug
    bool _debugMode = false;

    // Effetti
    void randomBlink();
    void rotate();
    void fade();
    void voiceSim();
    void randomModulation();
};

#endif
