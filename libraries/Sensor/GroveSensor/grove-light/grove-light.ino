#include <NectisCellular.h>

#define LIGHT_PIN       (GROVE_ANALOG_1_1)
#define INTERVAL        (100)

const int thresholdvalue=10;         //The threshold for which the LED should turn on.
float Rsensor; //Resistance of sensor in K

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
    
    pinMode(LIGHT_PIN,OUTPUT);            //Set the LED on Digital 12 as an OUTPUT
}

void loop() {
    int sensorValue = analogRead(LIGHT_PIN);
//    Rsensor=(float)(1023-sensorValue)*10/sensorValue;
//    if(Rsensor>thresholdvalue) {
//        digitalWrite(ledPin,HIGH);
//    }
//    else {
//        digitalWrite(ledPin,LOW);
//    }

    Serial.println("the analog read data is ");
    Serial.println(sensorValue);
//    Serial.println("the sensor resistance is ");
//    Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
    delay(1000);
}