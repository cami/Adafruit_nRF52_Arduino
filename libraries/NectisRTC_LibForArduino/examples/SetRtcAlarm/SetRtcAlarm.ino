#include <NectisCellular.h>
#include <NectisMcu.h>
#include <NectisRTC.h>

NectisCellular Nectis;
NectisMcu Mcu;
NectisRTC Rtc;


void InitSketch() {
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

  Serial.println("### Wake up the external flash ROM from deep sleep mode.");
  Mcu.WakeUpFlashRomFromDeepSleepMode();
  delay(100);
}

void setup() {
  InitSketch();

  Rtc.BeginRtc();
  Rtc.Init();

  Rtc.SetAlarm();
}

void loop() {
  Rtc.ReadCalender();

//  Rtc.EndRtc();

  delay(10000);

}