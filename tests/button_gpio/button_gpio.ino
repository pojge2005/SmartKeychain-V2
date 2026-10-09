#include <Arduino.h>

const uint8_t buttonPins[] = {0, 1, 3, 10};
bool previousState[] = {HIGH, HIGH, HIGH, HIGH};

void setup() {
    Serial.begin(115200);

    for (uint8_t i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    delay(1000);
    Serial.println();
    Serial.println("BUTTON GPIO TEST READY");
    Serial.println("Press and release each button.");
}

void loop() {
    for (uint8_t i = 0; i < 4; i++) {
        bool state = digitalRead(buttonPins[i]);

        if (state != previousState[i]) {
            previousState[i] = state;
            Serial.printf("GPIO %u: %s\n",
                          buttonPins[i],
                          state == LOW ? "PRESSED" : "RELEASED");
        }
    }

    delay(10);
}
