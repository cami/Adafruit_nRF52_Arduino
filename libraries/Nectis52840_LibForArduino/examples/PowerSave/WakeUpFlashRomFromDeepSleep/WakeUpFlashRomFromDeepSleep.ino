#include <NectisCellular.h>
#include <NectisMcu.h>

NectisCellular Nectis;
NectisMcu Mcu;

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


  // ToDO: Wake up the flash ROM from deep sleep mode, only when it is in deep sleep mode.
  // initialize SPI:
  SPI.begin();

  Serial.println("Wake up the external flash ROM from deep sleep mode.");
  Mcu.WakeUpFlashRomFromDeepSleepMode();

  SPI.end();
}

void loop() {
  __NOP();
}
