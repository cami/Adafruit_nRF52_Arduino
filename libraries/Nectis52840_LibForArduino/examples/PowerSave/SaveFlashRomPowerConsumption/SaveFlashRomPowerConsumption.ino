#include "NectisCellular.h"
#include <NectisMcu.h>

NectisCellular Nectis;
NectisMcu Mcu;
Stopwatch sw;


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
  
  // Get the current time.
  Nectis.Bg96Begin();
  Nectis.InitLteM();
  
  // initialize SPI:
  SPI.begin();
  
  Serial.println("Put the external flash ROM into deep sleep mode.");
  Mcu.PutFlashRomIntoDeepSleepMode();

  SPI.end();
}

void loop() {

}
