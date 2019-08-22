#include "NectisCellular.h"

NectisCellular Nectis;

#define SOFT_RESET_BUTTON       GROVE_ANALOG_1_1
bool isSoftResetEnable = false;


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
  // Make sure that the MODULE_PWR_PIN is set to HIGH.
  Nectis.PowerSupplyGrove(true);
  delay(100);
  
  Nectis.Bg96Begin();
  Nectis.InitLteM();
  
  pinMode(GROVE_ANALOG_1_1, INPUT);
  
  Serial.println("### Setup completed.");
}

void loop() {
  int buttonState = digitalRead(SOFT_RESET_BUTTON);
  if (buttonState == 1) {
    isSoftResetEnable = true;
  }
  
  if (isSoftResetEnable) {
    Serial.println("Soft Reset");
    delay(1000);
    
    isSoftResetEnable = false;
    Serial.end();
    NVIC_SystemReset();
  }
}
