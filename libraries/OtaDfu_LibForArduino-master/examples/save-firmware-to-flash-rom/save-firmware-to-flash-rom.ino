/*
 * Lte-M OTA-DFU
 *  Download the firmware from SORACOM Harvest files.
 */
#include <NectisCellular.h>
#include <NectisMcu.h>
#include <firmware.h>

#include "Adafruit_SPIFlash.h"

const uint16_t SECTOR_SIZE = 512;
const uint16_t WRITE_MAX_SIZE_ONE_TIME = SECTOR_SIZE;

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

  Serial.println("### Setup completed.");

  delay(1000);

  if (!flash.begin()) {
    Serial.println("Error, failed to initialize flash chip!");
    while(1) delay(10);
  }

  Serial.print("JEDEC ID: ");
  Serial.println(flash.getJEDECID(), HEX);
  Serial.print("Flash size: ");
  Serial.println(flash.size());

  if (!flash.eraseChip()) {
    Serial.println("Failed to erase chip!");
  }

  flash.waitUntilReady();
  Serial.println("Successfully erased chip!");

  Serial.printf("FILE_NAME: %s\n", FILE_NAME);
  Serial.printf("FIRMWARE_SIZE: %u\n", FIRMWARE_SIZE);

  Serial.println(WRITE_MAX_SIZE_ONE_TIME);
  Serial.println(SECTOR_SIZE);

  // const uint32_t SECTOR_TOTAL_NUM = (int) (ceil((double) FIRMWARE_SIZE/512));
  // sector_number 0 is saved for the settings of the firmware.
  uint16_t sector_number = 0;

  // ToDO: Convert HEX to binary.
  char FIRMWARE_SIZE_HEX[9] = {0};
  sprintf(FIRMWARE_SIZE_HEX, "%d", FIRMWARE_SIZE);
  Serial.printf("FIRMWARE_SIZE_HEX: %s\n", FIRMWARE_SIZE_HEX);

  write_sector(sector_number, &FIRMWARE_SIZE_HEX[0], sizeof(FIRMWARE_SIZE_HEX));
  Serial.println("Have saved FIRMWARE_SIZE in the Flash ROM at Sector0");


  sector_number = 1;

  for (uint32_t i = 0; i < FIRMWARE_SIZE; i += WRITE_MAX_SIZE_ONE_TIME) {
    uint16_t write_length = WRITE_MAX_SIZE_ONE_TIME < (FIRMWARE_SIZE-i) ? WRITE_MAX_SIZE_ONE_TIME : (FIRMWARE_SIZE - i);
    Serial.printf("sector_number, write_length: %u, %u\n", sector_number, write_length);
//    uint16_t write_length = min(WRITE_MAX_SIZE_ONE_TIME, FIRMWARE_SIZE-i);
    write_sector(sector_number, &FIRMWARE[i], write_length);
    sector_number++;
  }


  Serial.println("\nDone");
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


void write_sector(uint16_t sector_no, const char* contents, uint16_t contents_size) {
  uint8_t buf[contents_size];

  for(int i = 0 ; i < sizeof(buf) ; i++) {
    buf[i] = contents[i];
  }

  int nRet = flash.writeBuffer(sector_no*SECTOR_SIZE, buf, contents_size);

  flash.waitUntilReady();

  Serial.print(nRet);
  Serial.print(" sector_no=");
  Serial.print(sector_no);
  Serial.println(" Write OK");
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
