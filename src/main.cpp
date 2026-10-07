#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("==============================");
    Serial.println("SMART KEYCHAIN V2");
    Serial.println("ENVIRONMENT TEST");
    Serial.println("ESP32-C3 OK");
    Serial.println("==============================");
}

void loop()
{
    static unsigned long lastPrint = 0;

    if (millis() - lastPrint >= 1000)
    {
        lastPrint = millis();

        Serial.println("V2 ENVIRONMENT RUNNING");
    }
}
