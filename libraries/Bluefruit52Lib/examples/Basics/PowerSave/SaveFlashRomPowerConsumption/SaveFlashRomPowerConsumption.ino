#include "SPI.h"

#include "NectisCellular.h"

NectisCellular Nectis;
Stopwatch sw;

#define SLAVE_SELECT_PIN      PIN_SPI_CS


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

  // set the slaveSelectPin as an output:
  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  // initialize SPI:
  SPI.begin();

  Serial.println("Put the external flash ROM into deep sleep mode.");
  // take the SS pin low to select the chip:
  digitalWrite(SLAVE_SELECT_PIN, LOW);
  //  send value via SPI:
  SPI.transfer(0xB9);
  // take the SS pin high to de-select the chip:
  digitalWrite(SLAVE_SELECT_PIN, HIGH);
}

void loop() {

}
