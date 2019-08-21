#include <WioCellLibforArduino.h>

#define INTERVAL  (5000)

WioCellular Wio;

void setup() {
    delay(200);
    
    Serial.begin(115200);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Serial.println("### I/O Initialize.");
    Wio.Init();
    
    Serial.println("### Power supply ON.");
    Wio.PowerSupplyCellular(true);
    delay(500);
    
    Serial.println("### Turn on or reset.");
    if (!Wio.TurnOnOrReset()) {
        Serial.println("### ERROR! ###");
        return;
    }
    
    Serial.println("### Setup completed.");
}

void loop() {
    Serial.println("### Get time.");
    struct tm now;
    if (!Wio.GetTime(&now)) {
        Serial.println("### ERROR! ###");
        goto err;
    }
    Serial.print("UTC:");
    char str[100];
    sprintf(str, "%04d/%02d/%02d %02d:%02d:%02d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour,
            now.tm_min, now.tm_sec);
    Serial.println(str);
    
    err:
    delay(INTERVAL);
}

