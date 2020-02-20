#include "Adafruit_SPIFlash.h"

//#define SECTOR_SIZE     512     // Just FYI
uint16_t WRITE_SIZE_ONE_TIME = 512;

Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);

Adafruit_SPIFlash flash(&flashTransport);


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  delay(4000);

  Serial.println("--- START ---");

  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while (1) delay(10);
  }

  Serial.println("Adafruit Serial Flash Sector Dump example");
  Serial.print("JEDEC ID: ");
  Serial.println(flash.getJEDECID(), HEX);
  Serial.print("Flash size: ");
  Serial.println(flash.size());

  // Need to erase chip only once.
//  if (!flash.eraseChip()) {
//    Serial.println("Failed to erase chip!");
//  } else {
//    Serial.println("Successfully erased chip!");
//  }


  flash.waitUntilReady();

  // Writing 1 to the given sector.
  write_sector(1, WRITE_SIZE_ONE_TIME);
}

void write_sector(uint32_t sector, uint16_t size) {
  uint8_t buf[size];

  for(int i = 0 ; i < sizeof(buf) ; i++) {
    buf[i] = 0x01;
  }

  int nRet = flash.writeBuffer(sector*size, buf, size);

  flash.waitUntilReady();

  Serial.print(nRet);
  Serial.print(" sector=");
  Serial.print(sector);
  Serial.println(" Write OK");
}

void dump_sector(uint32_t sector) {
  uint8_t buf[512];
  flash.readBuffer(sector*512, buf, 512);

  for(uint32_t row=0; row<32; row++) {
    if ( row == 0 ) Serial.print("0");
    if ( row < 16 ) Serial.print("0");
    Serial.print(row*16, HEX);
    Serial.print(" : ");

    for(uint32_t col=0; col<16; col++) {
      uint8_t val = buf[row*16 + col];

      if ( val < 16 ) Serial.print("0");
      Serial.print(val, HEX);

      Serial.print(" ");
    }

    Serial.println();
  }
}

void loop() {
  Serial.print("Enter the sector number to dump: ");
  while( !Serial.available() ) delay(10);

  int sector = Serial.parseInt();

    Serial.println(sector); // echo

    if ( sector < flash.size()/512 ) {
      dump_sector(sector);
    } else {
    Serial.println("Invalid sector number");
  }

  Serial.println();
  delay(10); // a bit of delay
}