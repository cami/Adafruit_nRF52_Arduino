#include "NectisMcu.h"
#include "NectisPeripherals.h"
#include "NectisUtils.h"
#include "Adafruit_SPIFlash.h"

Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
Adafruit_SPIFlash flash(&flashTransport);


void DumpSector(uint32_t sector) {
  uint8_t buf[512];
  flash.readBuffer(sector*512, buf, 512);

  for(uint32_t row=0; row<32; row++)
  {
    if ( row == 0 ) Serial.print("0");
    if ( row < 16 ) Serial.print("0");
    Serial.print(row*16, HEX);
    Serial.print(" : ");

    for(uint32_t col=0; col<16; col++)
    {
      uint8_t val = buf[row*16 + col];

      if ( val < 16 ) Serial.print("0");
      Serial.print(val, HEX);

      Serial.print(" ");
    }

    Serial.println();
  }
}


void setup() {
  mcu::InitMcu();

  peripherals::WakeUpFlashRomFromDeepSleep();

  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1) delay(10);
  }

  Serial.print("JEDEC ID=");
  Serial.println(flash.getJEDECID(), HEX);

  if (!flash.eraseChip()) {
    Serial.println("Failed to erase chip!");
  }

  flash.waitUntilReady();
  Serial.println("Successfully erased chip!");
}

void loop() {
  Serial.print("Enter the sector number to dump: ");
  while( !Serial.available() ) delay(10);

  int sector = Serial.parseInt();

  Serial.println(sector); // echo

  if ( sector < int(flash.size()/512) )
  {
    DumpSector(sector);
  }else
  {
    Serial.println("Invalid sector number");
  }

  Serial.println();
  delay(10); // a bit of delay
}
