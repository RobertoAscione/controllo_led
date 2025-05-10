#include "LEDController.h"

// Definisci i pin PWM collegati ai LED
uint8_t leds[] = {3, 5, 6, 9};
LEDController controller(leds, 4);

void setup() {
    controller.begin();

    // Attiva l'effetto RANDOM_MODULATION
    controller.setEffect(RANDOM_MODULATION);
}

void loop() {
    controller.update(); // Aggiorna continuamente l'effetto
}