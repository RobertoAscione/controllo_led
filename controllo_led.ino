#include "LEDController.h"

uint8_t leds[] = {3, 5, 6};
LEDController controller(leds, 3);

String serialInput = "";
bool debug = true;

void setup() {
    Serial.begin(9600);
    controller.begin();
    controller.setDebug(debug);

    Serial.println("Comandi:");
    Serial.println(" 0: OFF  | 1: FADE | 2: ROTATE| 3: RANDOM_BLINK | 4: RANDOM_MODULATION.   | 5: VOICE_SIM. ");
    Serial.println(" s<ms>: fade speed    | r<ms>: rotate speed");
    Serial.println(" b<ms>: blink speed   | v<factor>: voice sensitivity");
    Serial.println(" d: toggle debug");
}

void loop() {
    controller.update();

    // Lettura seriale "riga per riga"
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            parseSerialCommand(serialInput);
            serialInput = "";
        } else {
            serialInput += c;
        }
    }
}

void parseSerialCommand(String cmd) {
    cmd.trim();
    if (cmd == "0") {
        controller.clearEffect();
        Serial.println("→ Effetto disattivato.");
    } else if (cmd == "1") {
        controller.setEffect(FADE);
        Serial.println("→ FADE attivato.");
    } else if (cmd == "2") {
        controller.setEffect(ROTATE);
        Serial.println("→ ROTATE attivato.");
    } else if (cmd == "3") {
        controller.setEffect(RANDOM_BLINK);
        Serial.println("→ RANDOM_BLINK attivato.");
    } else if (cmd == "4") {
        controller.setEffect(RANDOM_MODULATION);
        Serial.println("→ RANDOM_MODULATION attivato.");
    } else if (cmd == "5") {
        controller.setEffect(VOICE_SIM);
        Serial.println("→ VOICE_SIM attivato.");
        
    } else if (cmd == "d") {
        debug = !debug;
        controller.setDebug(debug);
        Serial.println(debug ? "→ DEBUG ON" : "→ DEBUG OFF");
    } else if (cmd.startsWith("s")) {
        controller.setFadeSpeed(cmd.substring(1).toInt());
        Serial.println("→ Velocità FADE aggiornata.");
    } else if (cmd.startsWith("r")) {
        controller.setRotationSpeed(cmd.substring(1).toInt());
        Serial.println("→ Velocità ROTATE aggiornata.");
    } else if (cmd.startsWith("b")) {
        controller.setBlinkInterval(cmd.substring(1).toInt());
        Serial.println("→ Velocità BLINK aggiornata.");
    } else if (cmd.startsWith("v")) {
        controller.setVoiceSensitivity(cmd.substring(1).toFloat());
        Serial.println("→ Sensibilità VOICE aggiornata.");
    } else {
        Serial.println("→ Comando sconosciuto.");
    }
}
