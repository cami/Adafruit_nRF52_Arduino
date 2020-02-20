#include <NectisCellular.h>
#include <NectisCellularOtaDfu.h>

#define LED_CHECK_PIN   (GROVE_ANALOG_1_1)

char FILE_NAME[32];
// The following values are got when you send HTTP post to AWS lambda and a firmware update is available.
const char* firmwareVersion = "0.0.1";
const char* filenameExtension = "bin";

NectisCellular Nectis;
NectisOtaDfu OtaDfu;


void setup() {
    Serial.begin(115200);
    delay(4000);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Serial.println("### I/O Initialize.");
    Nectis.Init();
    delay(100);
    Serial.println("### Power supply cellular ON.");
    Nectis.PowerSupplyCellular(true);
    delay(100);
    Serial.println("### Power supply ON.");
    // Make sure that the MODULE_PWR_PIN is set to HIGH.
    Nectis.PowerSupplyGrove(true);
    delay(100);
    
    pinMode(LED_CHECK_PIN, OUTPUT);
    
    
    sprintf(FILE_NAME, "fw_%s.%s", firmwareVersion, filenameExtension);
    Serial.printf("filename: %s\n", FILE_NAME);
    
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_BLUE, HIGH);
        digitalWrite(LED_CHECK_PIN, HIGH);
        digitalWrite(LED_RED, LOW);
        delay(500);
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_CHECK_PIN, LOW);
        digitalWrite(LED_RED, HIGH);
        delay(500);
    }
    
    Serial.println("### Setup completed.");
    Serial.println("Enter LTE-M DFU mode.");
    delay(100);
    
    OtaDfu.EnterLtemDfuMode();
}

void loop() {
}
