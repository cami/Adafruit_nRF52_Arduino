/*
 * http://wiki.seeedstudio.com/Grove-Relay/
 * This sketch enables to use GroveSensor-relay.
 */

#include <NectisCellular.h>

#define RELAY_PIN  (GROVE_ANALOG_1_1)

NectisCellular Nectis;


void setup() {
    delay(4000);
    
    Serial.begin(115200);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Serial.println("### I/O Initialize.");
    Nectis.Init();
    delay(100);
    Serial.println("### Power supply cellular ON.");
    Nectis.PowerSupplyCellular(true);
    delay(100);
    Serial.println("### Power supply ON.");
//  Make sure that the MODULE_PWR_PIN is set to HIGH.
    Nectis.PowerSupplyGrove(true);
    delay(100);
    
    pinMode(RELAY_PIN, OUTPUT);
    
    Serial.println("### Setup completed.");
}

void loop() {
    digitalWrite(RELAY_PIN, HIGH);
}

