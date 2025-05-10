// versione 1.2

#include "LEDController.h"
#include <math.h>

LEDController::LEDController(uint8_t ledPins[], uint8_t count)
    : _count(count), _effect(NONE), _lastUpdate(0),
      _fadeValue(0), _fadeDirection(5), _currentLED(0),
      _blinkInterval(150), _rotationSpeed(150), _fadeSpeed(30), _voiceFactor(1.0)
{
    if (_count > MAX_LEDS) _count = MAX_LEDS;
    for (uint8_t i = 0; i < _count; i++) {
        _pins[i] = ledPins[i];
    }
}

void LEDController::begin() {
    for (uint8_t i = 0; i < _count; i++) {
        pinMode(_pins[i], OUTPUT);
        analogWrite(_pins[i], 0);
    }
}

void LEDController::setEffect(EffectType effect) {
    _effect = effect;
}

void LEDController::clearEffect() {
    _effect = NONE;
    for (uint8_t i = 0; i < _count; i++) {
        analogWrite(_pins[i], 0);
    }
}

void LEDController::setBlinkInterval(unsigned long interval) {
    _blinkInterval = interval;
}

void LEDController::setRotationSpeed(unsigned long speed) {
    _rotationSpeed = speed;
}

void LEDController::setFadeSpeed(unsigned long speed) {
    _fadeSpeed = speed;
}

void LEDController::setVoiceSensitivity(float factor) {
    _voiceFactor = factor;
}

void LEDController::update() {
    switch (_effect) {
        case RANDOM_BLINK: randomBlink(); break;
        case ROTATE:       rotate(); break;
        case FADE:         fade(); break;
        case VOICE_SIM:    voiceSim(); break;
        default: break;
    }
}

// ... implementazioni aggiornate

void LEDController::randomBlink() {
    if (millis() - _lastUpdate > _blinkInterval) {
        for (uint8_t i = 0; i < _count; i++) {
            analogWrite(_pins[i], random(0, 2) * 255);
        }
        _lastUpdate = millis();
    }
}

void LEDController::rotate() {
    if (millis() - _lastUpdate > _rotationSpeed) {
        for (uint8_t i = 0; i < _count; i++) {
            analogWrite(_pins[i], (i == _currentLED) ? 255 : 0);
        }
        _currentLED = (_currentLED + 1) % _count;
        _lastUpdate = millis();
    }
}

void LEDController::fade() {
    if (millis() - _lastUpdate > _fadeSpeed) {
        _fadeValue += _fadeDirection;
        if (_fadeValue <= 0 || _fadeValue >= 255) {
            _fadeDirection = -_fadeDirection;
        }
        for (uint8_t i = 0; i < _count; i++) {
            analogWrite(_pins[i], _fadeValue);
        }
        _lastUpdate = millis();
    }
}

void LEDController::voiceSim() {
    if (millis() - _lastUpdate > 50) {
        for (uint8_t i = 0; i < _count; i++) {
            int value = abs(sin((millis() + i * 250) * _voiceFactor / 300.0)) * 255;
            analogWrite(_pins[i], value);
        }
        _lastUpdate = millis();
    }
}
