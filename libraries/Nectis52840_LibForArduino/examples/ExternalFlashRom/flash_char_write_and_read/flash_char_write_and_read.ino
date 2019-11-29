#include "Adafruit_SPIFlash.h"

#define SECTOR_SIZE     512     // Just FYI

Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
Adafruit_SPIFlash flash(&flashTransport);


void WriteSector(uint16_t sector_no, const char* contents, uint16_t contents_size) {
  uint8_t buf[contents_size + 1];

  for(uint32_t i = 0 ; i < sizeof(buf) ; i++) {
    buf[i] = contents[i];
  }
  buf[sizeof(buf)] = '\0';

  int nRet = flash.writeBuffer(sector_no*SECTOR_SIZE, buf, contents_size);

  Serial.printf("write data: %s\n", buf);

  flash.waitUntilReady();

//  Serial.print(nRet);
//  Serial.print(" sector_no=");
//  Serial.print(sector_no);
//  Serial.println(" Write OK");
}

void ReadSector(uint16_t sector_no, uint16_t contents_size) {
  uint8_t buf[contents_size];
  flash.readBuffer(sector_no*SECTOR_SIZE, buf, contents_size);

  Serial.printf("read data: %s\n", buf);

  flash.waitUntilReady();
//  for(uint32_t row=0; row<32; row++) {
//    if ( row == 0 ) Serial.print("0");
//    if ( row < 16 ) Serial.print("0");
//    Serial.print(row*16, HEX);
//    Serial.print(" : ");
//
//    for(uint32_t col=0; col<16; col++) {
//      uint8_t val = buf[row*16 + col];
//
//      if ( val < 16 ) Serial.print("0");
//      Serial.print(val, HEX);
//
//      Serial.print(" ");
//    }
//
//    Serial.println();
//  }
}

void DumpSector(uint32_t sector_no, uint16_t contents_size) {
  uint8_t buf[SECTOR_SIZE];
  flash.readBuffer(sector_no*SECTOR_SIZE, buf, contents_size);

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


void setup() {
  Serial.begin(115200);
  delay(4000);

  Serial.println("--- START ---");

  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while (1) delay(10);
  }
  flash.waitUntilReady();

  Serial.println("Adafruit Serial Flash Sector Dump example");
  Serial.print("JEDEC ID: ");
  Serial.println(flash.getJEDECID(), HEX);
  Serial.print("Flash size: ");
  Serial.println(flash.size());

  int totalSectorNum = flash.numPages();
  Serial.printf("totalSectorNum: %d\n", totalSectorNum);


//  Need to erase chip only once.
  if (!flash.eraseChip()) {
    Serial.println("Failed to erase chip!");
  } else {
    Serial.println("Successfully erased chip!");
  }


  char saveWords[64] = "Hello World";
  uint16_t sizeOfSaveWords = strlen(saveWords);

  Serial.println();
  Serial.printf("saveWords: %s\n", saveWords);
  Serial.printf("sizeOfSaveWords: %u\n", sizeOfSaveWords);
  Serial.println();


  // Writing 1 to the given sector.
  WriteSector(1, &saveWords[0], sizeOfSaveWords + 3);

  ReadSector(1, sizeOfSaveWords + 3);

  Serial.print("Enter the sector number to dump: ");
}

void loop() {
  while( Serial.available() > 2 ) {
    // Integer 0 is 48 in ASCII decimal.
    int sector = Serial.read();
    // 13 is CR, 10 is LF.
    if (sector == 13 || sector == 10) { break; }

    int sectorDecimal = sector - 48;

    Serial.println(sectorDecimal); // echo

    if ( sectorDecimal < flash.size()/512 ) {
      DumpSector(sectorDecimal, 512);
    } else {
      Serial.println("Invalid sector number");
    }

    Serial.println();
    Serial.flush();

    Serial.print("Enter the sector number to dump: ");

    delay(10); // a bit of delay
  }
}
