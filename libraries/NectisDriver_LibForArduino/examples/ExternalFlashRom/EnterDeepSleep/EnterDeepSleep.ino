#include "NectisMcu.h"
#include "NectisDriver.h"
#include "NectisUtils.h"
#include "NectisDebug.h"

NectisDriver Driver;


void setup() {
  Serial.begin(115200);
  delay(4000);

  mcu::InitMcu();
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");


  // もしFlashROMをディープスリープモードに入れると、FlashRomBegin()でエラーが返ってくる。
  Driver.FlashRomEnterDeepSleep();


  Driver.FlashRomBegin();

  while( !Serial.available() ) delay(10);
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

void loop() {
}
