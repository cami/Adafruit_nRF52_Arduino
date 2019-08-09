#include <NectisCellular.h>

NectisCellular Nectis;

void setup() {
    Serial.begin(115200);
    Serial.println("setup");
}

void loop() {
    float UsbVoltageLevelMv;
    UsbVoltageLevelMv = Nectis.ReadVusb();
    
    Serial.printf("%f[mV]\n",UsbVoltageLevelMv);
    
    delay(5000);
}
