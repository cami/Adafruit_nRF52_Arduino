#include <NectisCellular.h>
#include <NectisMcu.h>
#include <NectisRTC.h>

NectisCellular Nectis;
NectisMcu Mcu;
NectisRTC Rtc;

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

  delay(1000);

  Rtc.SetRtcTimer(60);
  delay(1000);

  Rtc.EnableRtcTimer();
  delay(1000);

  Rtc.ReadSetTimer();
}

void loop() {
  __NOP();
}
