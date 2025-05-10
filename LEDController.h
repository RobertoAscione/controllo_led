#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

#define MAX_LEDS 8

// Effetti supportati
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
    LEDController(uint8_t ledPins[], uint8_t count);
    void begin();
    void setEffect(EffectType effect);
    void clearEffect();
    void update();

    // Parametri configurabili
    void setBlinkInterval(unsigned long interval);
    void setRotationSpeed(unsigned long speed);
    void setFadeSpeed(unsigned long speed);
    void setVoiceSensitivity(float factor);

private:
    uint8_t _pins[MAX_LEDS];
    uint8_t _count;
    EffectType _effect;
    unsigned long _lastUpdate;

    // Parametri effetto
    unsigned long _blinkInterval;
    unsigned long _rotationSpeed;
    unsigned long _fadeSpeed;
    float _voiceFactor;

    // Stato interno
    int _fadeValue;
    int _fadeDirection;
    uint8_t _currentLED;

    // Per RANDOM_MODULATION
    unsigned long _nextUpdate[MAX_LEDS];
    unsigned long _modInterval[MAX_LEDS];
    uint8_t _targetValue[MAX_LEDS];
    uint8_t _currentValue[MAX_LEDS];
    int8_t _direction[MAX_LEDS];

    void randomBlink();
    void rotate();
    void fade();
    void voiceSim();
    void randomModulation();
};

#endif
