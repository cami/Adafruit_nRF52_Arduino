#include "NectisPeripherals.h"
#include <Arduino.h>
#include "SPI.h"


namespace peripherals {

/*
 * External Flash Rom
 */
void PutFlashRomIntoDeepSleep(void) {
  Serial.println("### Put the external flash ROM into deep sleep mode.");

  SPI.begin();

  // SLAVE_SELECT_PIN == PIN_SPI_CS
  // set the slaveSelectPin as an output:
  pinMode(PIN_SPI_CS, OUTPUT);

  digitalWrite(PIN_SPI_CS, LOW);
  SPI.transfer(0xB9);
  digitalWrite(PIN_SPI_CS, HIGH);

  SPI.end();
}

void WakeUpFlashRomFromDeepSleep(void) {
  Serial.println("### Wake up the external flash ROM from deep sleep mode.");

  SPI.begin();

  // SLAVE_SELECT_PIN == PIN_SPI_CS
  // set the slaveSelectPin as an output:
  pinMode(PIN_SPI_CS, OUTPUT);

  digitalWrite(PIN_SPI_CS, LOW);
  SPI.transfer(0xAB);
  digitalWrite(PIN_SPI_CS, HIGH);

  SPI.end();
}

} // namespace peripherals