#include <NectisCellular.h>
#include <NectisCellularOtaDfu.h>

#define DFU_INTERVAL        60000

NectisCellular Nectis;
NectisOtaDfu OtaDfu;
Stopwatch sw;


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

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);
  sw.Restart();

  Serial.println("### Setup completed.");
}

void loop() {
  if (sw.ElapsedMilliseconds() >= DFU_INTERVAL) {
    digitalWrite(LED_BLUE, LOW);
    delay(1000);

    OtaDfu.EnterBleDfuMode();
  }
}