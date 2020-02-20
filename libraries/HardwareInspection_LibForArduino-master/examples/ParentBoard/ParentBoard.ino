// 検査する側の基板に書き込むスケッチ
// Tools > Board > PARENT BOARD CAMI qibanca nectis
// 14414301

#include <string.h>

#include <NectisCellular.h>
#include <NectisMcu.h>

#include <NectisCellularConfig.h>
#include <Internal/Debug.h>

#include "NectisFlags.h"
#include "NectisTestHardware.h"

#define CLI_TEST


NectisCellular Nectis;
NectisMcu Mcu;

NectisFlags Flags;
NectisTestHardware TestHardware;


void ExecuteAllParentTest() {
  Serial.println("### ExecuteAllParentTest() has started.");

  Serial.println("### Execute all the test for parent board.");
  for (int i = 6; i <= 12; i++) {
    TestHardware.ExecuteArbitraryParentTest(i);
    delay(2500);
  }
  TestHardware.ExecuteArbitraryParentTest(35);
  delay(1000);
  TestHardware.ExecuteArbitraryParentTest(36);
  delay(1000);
  TestHardware.ExecuteArbitraryParentTest(40);

  Serial.println("\n### ExecuteAllParentTest() has ended.");
}


void setup() {
  Serial.begin(115200);

  Serial.println("");
  Serial.println("Parent Board Test");
  Serial.println("--- START ---------------------------------------------------");

  Serial.println("### I/O Initialize.");
  Nectis.Init();
  delay(100);

  DEBUG_PRINTLN("### Relay Pins Initialize.");
  TestHardware.InitRelayPins();

  Serial.println("### Power supply cellular ON.");
  Nectis.PowerSupplyCellular(true);
  delay(100);

  Serial.println("### Power supply ON.");
//  Make sure that the MODULE_PWR_PIN is set to HIGH.
  Nectis.PowerSupplyGrove(true);
  delay(100);

  Serial.println("### Wake up the external flash ROM from deep sleep mode.");
  Mcu.WakeUpFlashRomFromDeepSleepMode();
  delay(100);

#ifdef CLI_TEST
  Serial.println("Please input the Test number.\n");

  while (1) {
    const uint16_t INPUT_BUFFER_SIZE = 64;
    char input[INPUT_BUFFER_SIZE];
    memset(&input[0], 0x00, sizeof(input));

    unsigned int INPUT_SIZE = 0;

    while (Serial.available() > 0) {
      // After Serial.read(), Serial.available() is subtracted by 1.
      int inputOneByte = Serial.read();
  //    Serial.print(inputOneByte);
  //    Serial.print(" ");
  //    Serial.println(inputOneByte, HEX);

      input[INPUT_SIZE++] = inputOneByte;

      // If the input string size is bigger than (INPUT_BUFFER_SIZE-1), the new line is started.
      if (INPUT_SIZE == INPUT_BUFFER_SIZE-1) {
        input[INPUT_SIZE] = 0x00;
//        Serial.println(input);
        delay(10);

        memset(&input[0], 0x00, sizeof(input));
        INPUT_SIZE = 0;
      }

      // Please select "CR and LF" on the serial monitor of ArduinoIDE
      // if (Serial.available() == 1) then Serial.read() = CR
      // if (Serial.available() == 0) then Serial.read() = LF
      if (Serial.available() == 2) {
        input[INPUT_SIZE] = 0x00;
//        Serial.println(input);

        unsigned int input_uint = atoi(input);

        // Hardware Test here.
        if ((input_uint == 2) || (6 <= input_uint && 12 >= input_uint) || (input_uint == 35) || (input_uint == 36) || (input_uint == 40) || (input_uint == 42) || (input_uint == 44)) {
          TestHardware.ExecuteArbitraryParentTest(input_uint);
          Serial.println("\nPlease input the Test number.");
        } else if (input_uint == 777) {
          ExecuteAllParentTest();
        } else {
          Serial.println("\nPlease input the valid Test number.");
        }

        Serial.read();
        Serial.read();

        memset(&input[0], 0x00, sizeof(input));
      }
      delay(1);
    }
  }
#endif  // CLI_TEST
}

void loop() {
  __NOP();
}