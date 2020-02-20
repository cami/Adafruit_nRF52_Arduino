// 検査される側の基板に書き込むスケッチ
// 検査される側の基板：検査後に出荷される基板
// Tools > Board > CAMI qibanca nectis series on nRF52840
// 14414101

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


void ExecuteAllChildTest() {
  Serial.println("### ExecuteAllChildTest() has started.");

  Serial.println("### Execute all the test for child board.");
  for (int i = 14; i <= 33; i++) {
    float Value = TestHardware.ExecuteArbitraryChildTestFloat(i);
    Serial.printf("The value is: %f\n\n", Value);
    delay(10);
  }

  TestHardware.ExecuteArbitraryChildTestUint32(34);
  delay(10);

  for (int i = 35; i <= 38; i++) {
    int Value = TestHardware.ExecuteArbitraryChildTestInt(i);
    Serial.printf("The value is: %d\n\n", Value);
    delay(10);
  }

  TestHardware.ExecuteArbitraryChildTestVoid(41);
  delay(10);

  Serial.println("\n### ExecuteAllChildTest() has ended.");
}


void setup() {
  Serial.begin(115200);

  Serial.println("");
  Serial.println("Child Board Test");
  Serial.println("--- START ---------------------------------------------------");

  Serial.println("### I/O Initialize.");
  Nectis.Init();
  delay(100);

  DEBUG_PRINTLN("### Analog/GPIO Pins Initialize.");
  TestHardware.InitGpioPins();
  TestHardware.InitAnalogPinsPullUp();

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
        if (input_uint == 5) {
          char imei[16];
          TestHardware.ExecuteArbitraryChildTestVoid(input_uint, imei, sizeof(imei));
          Serial.printf("The read value is: %s\n", &imei);
          Serial.println("\nPlease input the Test number.");
        } else if (14 <= input_uint && 33 >= input_uint) {
          float readValue = TestHardware.ExecuteArbitraryChildTestFloat(input_uint);
          Serial.printf("The read value is: %f\n", readValue);
          Serial.println("\nPlease input the Test number.");
        } else if (35 <= input_uint && 38 >= input_uint) {
          int readValue = TestHardware.ExecuteArbitraryChildTestInt(input_uint);
          Serial.printf("The read value is: %d\n", readValue);
          Serial.println("\nPlease input the Test number.");
        } else if (input_uint == 2 || input_uint == 41 || input_uint == 44) {
          TestHardware.ExecuteArbitraryChildTestVoid(input_uint);
          Serial.println("\nPlease input the Test number.");
        } else if (input_uint == 34) {
          uint32_t readValue = TestHardware.ExecuteArbitraryChildTestUint32(input_uint);
          Serial.printf("The read value is: %x\n", readValue);
          Serial.println("\nPlease input the Test number.");
        } else if (input_uint == 777) {
          ExecuteAllChildTest();
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