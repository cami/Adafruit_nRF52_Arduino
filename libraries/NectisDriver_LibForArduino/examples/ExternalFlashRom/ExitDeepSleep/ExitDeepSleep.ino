#include "NectisMcu.h"
#include "NectisDriver.h"
#include "NectisUtils.h"
#include "NectisDebug.h"

NectisDriver Driver;

constexpr uint8_t INPUT_BUFFER_SIZE = 64;
char input[INPUT_BUFFER_SIZE];
uint8_t inputSize;


void setup() {
  Serial.begin(115200);
  delay(4000);

  mcu::InitMcu();
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");

  Driver.FlashRomExitDeepSleep();

  Driver.FlashRomBegin();

  while( !Serial.available() ) delay(10);
}

void loop() {
  Serial.print("Enter the sector number to dump: ");

  int sector = Serial.parseInt();

  Serial.println(sector); // echo

  if ( sector < int(Driver.FlashRomGetSize()/Driver.SECTOR_SIZE) ) {
    Driver.FlashRomDumpSector(sector);
  } else {
    Serial.println("### Invalid sector number");
  }

  Serial.println();
  delay(10); // a bit of delay
}
