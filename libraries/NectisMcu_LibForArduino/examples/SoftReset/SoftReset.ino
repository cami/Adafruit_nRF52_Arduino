#include "NectisCellular.h"
#include "NectisMcu.h"

NectisCellular Nectis;

#define PIN_SOFT_RESET_ENABLE       GROVE_ANALOG_1_1


void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");

  mcu::InitMcu();
  
  Nectis.Begin();
  Nectis.InitLteM();
  
  pinMode(PIN_SOFT_RESET_ENABLE, INPUT);
  
  Serial.println("### Setup completed.");
}

void loop() {
  int buttonState = digitalRead(PIN_SOFT_RESET_ENABLE);
  bool isRequestedToSoftReset = (buttonState == 1);

  if (isRequestedToSoftReset) {
    Serial.println("### Soft Reset");
    delay(1000);
    
    mcu::SoftReset();
  }
}
