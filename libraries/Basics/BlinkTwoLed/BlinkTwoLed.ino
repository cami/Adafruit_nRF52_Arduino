/*
 * Alternately blink two LEDs on the board.
 */

#include <NectisCellular.h>

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

    Serial.println("### Setup completed.");
}

void loop() {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    delay(1000);
    
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
    delay(1000);
}