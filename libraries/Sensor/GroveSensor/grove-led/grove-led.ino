/*
 * This sketch enables to blink GroveSensor-led.
 */

#include <NectisCellular.h>

#define LED_CHECK_PIN   (GROVE_ANALOG_1_1)

NectisCellular Nectis;


void setup() {
    delay(200);
    Serial.begin(115200);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Nectis.Init();
    
    Serial.println("### Power supply cellular git ON.");
    Nectis.PowerSupplyCellular(true);
    delay(500);
    
    Serial.println("### Power supply GroveSensor ON.");
    Nectis.PowerSupplyGrove(true);
    delay(500);
    
    Serial.println("### LED_CHECK_PIN ON.");
    pinMode(LED_CHECK_PIN, OUTPUT);
}

void loop() {
    Serial.println("### LED_CHECK_PIN HIGH/LOW.");
    
    digitalWrite(LED_CHECK_PIN, HIGH);
    delay(200);
    digitalWrite(LED_CHECK_PIN, LOW);
    delay(200);
}