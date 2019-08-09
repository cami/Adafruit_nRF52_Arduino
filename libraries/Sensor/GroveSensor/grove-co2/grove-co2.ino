/*
 * http://wiki.seeedstudio.com/Grove-CO2_Sensor/
 * This sketch enables you to measure CO2 consentration with GroveSensor-co2 sensor
 */
#include <NectisCellular.h>
#include <NectisCellularUart.h>

NectisCellular Nectis;
NectisCellularUart NectisUart;


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
    
    // Initialize Uart between BL654 and GroveSensor sensor (Grove_GPIO_5_1, Grove_GPIO_5_2)
    NectisUart.GroveUartSetup();
    NectisUart.GroveUartBegin();
    
    NectisUart.Co2Calibration();
    
    Serial.println("### Setup completed.");
}

void loop() {
    if(NectisUart.Co2Read()) {
        Serial.println("CO2 data received");
    }
    delay(1000);
}


