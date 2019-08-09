/*
 * http://wiki.seeedstudio.com/Grove-Button/
 * This sketch enables to use GroveSensor-button.
 * When you press the button, you can find it on the serial monitor of ArduinoIDE.
 */

#include <NectisCellular.h>

#define BUTTON_PIN  (GROVE_ANALOG_1_1)
#define INTERVAL    (100)

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
    
    pinMode(BUTTON_PIN, INPUT);
    
    Serial.println("### Setup completed.");
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);
    Serial.print(buttonState ? '*' : '.');
    delay(INTERVAL);
}

