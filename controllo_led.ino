#include "LEDController.h"

// Definisci i pin PWM collegati ai LED
uint8_t leds[] = {3, 5, 6};
LEDController controller(leds, 4);

bool micActive = false;
unsigned long lastSwitch = 0;

void setup() {
    controller.begin();
    controller.setBlinkInterval(100);
    controller.setFadeSpeed(20);
    controller.setVoiceSensitivity(1.5);
}

void loop() {
    // esempio: alterna effetti ogni 5s
    if (millis() - lastSwitch > 5000) {
        micActive = !micActive;
        lastSwitch = millis();

        if (micActive) {
            controller.setEffect(VOICE_SIM);
        } else {
            controller.setEffect(FADE);
        }
    }

    controller.update();
}