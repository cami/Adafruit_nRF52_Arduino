#include "NectisFlashROM.h"
#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_SPIFlash.h"

Adafruit_FlashTransport_QSPI _flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
Adafruit_SPIFlash _flash(&_flashTransport);


NectisFlashROM::NectisFlashROM() {

}

/*
 * External Flash Rom
 */
void NectisFlashROM::FlashRomEnterDeepSleep(void) {
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

void NectisFlashROM::FlashRomExitDeepSleep(void) {
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


void NectisFlashROM::FlashRomBegin() {
  if (!_flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1) delay(10);
  }
}

void NectisFlashROM::FlashRomEraseChip() {
  if (!_flash.eraseChip()) {
    Serial.println("### Failed to erase chip!");
  }
}

void NectisFlashROM::FlashRomWaitUntilReady() {
  if (!_flash.eraseChip()) {
    Serial.println("### Failed to erase chip!");
  }
}

void NectisFlashROM::FlashRomWriteSector(uint16_t sector_no, const char* contents, uint16_t contents_size) {
  uint8_t buf[contents_size];

  for(uint32_t i = 0 ; i < sizeof(buf); i++) {
    buf[i] = contents[i];
  }

  _flash.writeBuffer(sector_no*SECTOR_SIZE, buf, contents_size);

  _flash.waitUntilReady();
}