#include "NectisCellular.h"
#include <NectisMcu.h>
#include "Adafruit_SPIFlash.h"

NectisCellular Nectis;
NectisMcu Mcu;

Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
Adafruit_SPIFlash flash(&flashTransport);


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
  
//  Serial.println("Put the external flash ROM into deep sleep mode.");
//  Mcu.PutFlashRomIntoDeepSleepMode();
//
//  Serial.println("Success");
//
//  flash.begin();

  Serial.println("Put the external flash ROM into deep sleep mode.");
  Mcu.PutFlashRomIntoDeepSleepMode();

  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1) delay(10);
  }

  Serial.print("JEDEC ID: ");
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

  if ( sector < flash.size()/512 )
  {
    dump_sector(sector);
  }else
  {
    Serial.println("Invalid sector number");
  }

  Serial.println();
  delay(10); // a bit of delay
}

void dump_sector(uint32_t sector) {
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