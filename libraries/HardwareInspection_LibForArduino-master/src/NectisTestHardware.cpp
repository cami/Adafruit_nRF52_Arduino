#include "NectisTestHardware.h"

#include <NectisCellularConfig.h>
#include <Internal/Debug.h>

constexpr uint8_t relay_u9 = 14;     // GROVE_GPIO_5_2, GROVE_UART_TX_PIN
constexpr uint8_t relay_u2 = 13;     // GROVE_GPIO_5_1, GROVE_UART_RX_PIN
constexpr uint8_t relay_u3 = 4;      // GROVE_GPIO_1_1, GROVE_ANALOG_1_1
constexpr uint8_t relay_u4 = 5;      // GROVE_GPIO_1_2, GROVE_ANALOG_1_2
constexpr uint8_t relay_u5 = 28;     // GROVE_GPIO_2_1, GROVE_ANALOG_2_1
constexpr uint8_t relay_u6 = 30;     // GROVE_GPIO_3_1, GROVE_ANALOG_3_1
constexpr uint8_t relay_u7 = 31;     // GROVE_GPIO_3_2, GROVE_ANALOG_3_2
constexpr uint8_t relay_u8 = 29;     // GROVE_GPIO_2_2, GROVE_ANALOG_2_2

//Adafruit_FlashTransport_SPI flashTransport(SS, &SPI);
//flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3)

NectisTestHardware::NectisTestHardware(): flashTransport(SS, &SPI), _flash(&flashTransport) {

}

void NectisTestHardware::ExecuteArbitraryParentTest(unsigned int input) {
  uint16_t relayPinFlags;
  _Flags.ClearFlags(&relayPinFlags);
  InitRelayPins();

  switch (input) {
    case 2:
      Serial.println("02");
      _Mcu.SoftReset();
      break;

    case 6:
      Serial.println("06");
      relayPinFlags |= ACTIVATE_RELAY_PIN_5V0;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    case 7:
      Serial.println("07");
      relayPinFlags |= ACTIVATE_RELAY_PIN_4V5;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    case 8:
      Serial.println("08");
      relayPinFlags |= ACTIVATE_RELAY_PIN_4V2;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    case 9:
      Serial.println("09");
      relayPinFlags |= ACTIVATE_RELAY_PIN_3V8;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    case 10:
      Serial.println("10");
      relayPinFlags |= ACTIVATE_RELAY_PIN_G3V3;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    case 11:
      Serial.println("11");
      relayPinFlags |= ACTIVATE_RELAY_PIN_3V3;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    case 12:
      Serial.println("12");
      relayPinFlags |= ACTIVATE_RELAY_PIN_1V8;
      PowerSupplyRelayPins(POWER_SUPPLY_RELAY_PIN_5V0);
      ActivateRelayPins(relayPinFlags);
      break;

    // ToDO:
    case 35:
      Serial.println("35");
      Serial.println("### Get BLE RSSI.");
      break;

    // ToDO:
    case 36:
      Serial.println("36");
      Serial.println("### Get BLE RSSI.");
      break;

    case 40:
      Serial.println("40");
//      リレーを制御し電源供給をTP19に切り替える
      relayPinFlags |= POWER_SUPPLY_RELAY_PIN_3V7;
      PowerSupplyRelayPins(relayPinFlags);

      _Flags.ClearFlags(&relayPinFlags);

      relayPinFlags |= DEACTIVATE_USB_PIN;
      USBRelayPins(relayPinFlags);
      break;

    case 42:
      Serial.println("42");
      relayPinFlags |= POWER_SUPPLY_RELAY_PIN_5V0;
      PowerSupplyRelayPins(relayPinFlags);
      break;

    case 44:
      Serial.println("44");
      relayPinFlags |= POWER_SUPPLY_RELAY_PIN_5V0;
      PowerSupplyRelayPins(relayPinFlags);
      break;

    default:
      Serial.printf("This sketch is not required for Test number: %u.", input);
      break;
  }
}

void NectisTestHardware::ExecuteArbitraryChildTestVoid(unsigned int input, char *imei, int imei_size) {
  InitAnalogPinsPullUp();
  InitGpioPins();

  switch (input) {
    case 5:
      Serial.println("05");

      pinMode(LED_BLUE, OUTPUT);      digitalWrite(LED_BLUE, HIGH);

      // For the test number 6-12, BG96 must be powered on.
      _Nectis.Bg96Begin();
      _Nectis.InitLteM();

      if (_Nectis.GetIMEI(imei, imei_size) > 0) {
        Serial.printf("IMEI: %s\n", imei);
      }

      digitalWrite(LED_BLUE, LOW);

      break;
  }
}

float NectisTestHardware::ExecuteArbitraryChildTestFloat(unsigned int input) {
  uint16_t gpioPinFlags;
  _Flags.ClearFlags(&gpioPinFlags);
  InitAnalogPinsPullUp();
  InitGpioPins();

  float readValue = 0;

  switch (input) {
    case 14:
      Serial.println("14");
      gpioPinFlags |= A0_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 15:
      Serial.println("15");
      gpioPinFlags |= A1_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 16:
      Serial.println("16");
      gpioPinFlags |= A2_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 17:
      Serial.println("17");
      gpioPinFlags |= A3_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 18:
      Serial.println("18");
      gpioPinFlags |= A4_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 19:
      Serial.println("19");
      gpioPinFlags |= A5_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 20:
      Serial.println("20");
      gpioPinFlags |= A6_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 21:
      Serial.println("21");
      gpioPinFlags |= A7_INPUT;
      readValue = ReadAnalogPin(gpioPinFlags);
      break;

    case 22:
      Serial.println("22");
      gpioPinFlags |= (GPIO_4_2_HIGH | GPIO_4_1_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 23:
      Serial.println("23");
      gpioPinFlags |= (GPIO_4_1_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 24:
      Serial.println("24");
      gpioPinFlags |= (GPIO_4_1_HIGH | GPIO_4_2_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 25:
      Serial.println("25");
      gpioPinFlags |= (GPIO_4_2_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 26:
      Serial.println("26");
      gpioPinFlags |= (GPIO_5_2_HIGH | GPIO_5_1_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 27:
      Serial.println("27");
      gpioPinFlags |= (GPIO_5_1_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 28:
      Serial.println("28");
      gpioPinFlags |= (GPIO_5_1_HIGH | GPIO_5_2_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 29:
      Serial.println("29");
      gpioPinFlags |= (GPIO_5_2_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 30:
      Serial.println("30");
      gpioPinFlags |= (GPIO_6_2_HIGH | GPIO_6_1_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 31:
      Serial.println("31");
      gpioPinFlags |= (GPIO_6_1_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 32:
      Serial.println("32");
      gpioPinFlags |= (GPIO_6_1_HIGH | GPIO_6_2_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    case 33:
      Serial.println("33");
      gpioPinFlags |= (GPIO_6_2_INPUT);
      ActivateGpioPins(gpioPinFlags);
      readValue = ReadGpioPin(gpioPinFlags);
      break;

    default:
      Serial.printf("### This board is not required for Test number: %u.\n", input);
      break;
  }
  return readValue;
}

int NectisTestHardware::ExecuteArbitraryChildTestInt(unsigned int input) {
  uint16_t gpioPinFlags;
  _Flags.ClearFlags(&gpioPinFlags);
  InitAnalogPinsPullUp();
  InitGpioPins();

  int rssi = 0;

  switch (input) {
    // ToDO:
    case 35:
      Serial.println("35");
      Serial.println("### Get BLE RSSI.");
      break;

    // ToDO:
    case 36:
      Serial.println("36");
      Serial.println("### Get BLE RSSI.");
      break;

    // ToDO:
    case 37:
      Serial.println("37");
      Serial.println("### Get GPS RSSI.");
      break;

    case 38:
      Serial.println("38");
      Serial.println("### Get LTE-M RSSI.");

      pinMode(LED_BLUE, OUTPUT);      digitalWrite(LED_BLUE, HIGH);

      rssi = _Nectis.GetReceivedSignalStrengthIndicator();

      Serial.printf("LTE-M RSSI: %d\n", rssi);

      digitalWrite(LED_BLUE, LOW);
      break;

    default:
      Serial.printf("### This board is not required for Test number: %u.\n", input);
      break;
  }
  return rssi;
}

uint32_t NectisTestHardware::ExecuteArbitraryChildTestUint32(unsigned int input) {
  InitAnalogPinsPullUp();
  InitGpioPins();
  
  uint32_t jedecId = 0;
  
  switch (input) {
    case 34: {
      Serial.println("34");
      Serial.println("### Flash ROM.");
      
      if (!_flash.begin()) {
        Serial.println("### Error, failed to initialize flash chip!");
        while (1) delay(10);
      }
      
      jedecId = _flash.getJEDECID();
      Serial.printf("JEDEC ID: %x\n", jedecId);
      
      if (!_flash.eraseChip()) {
        Serial.println("### Failed to erase chip!");
      }
      
      _flash.waitUntilReady();
      Serial.println("### Successfully erased chip!");
      
      break;
    }
  }
  return jedecId;
}

void NectisTestHardware::ExecuteArbitraryChildTestVoid(unsigned int input) {
  InitAnalogPinsPullUp();
  InitGpioPins();

  switch (input) {
    case 2:
      Serial.println("02");
      _Mcu.SoftReset();
      break;

    case 41:
      Serial.println("41");
      Serial.println("### Deep Sleep Mode.");
      
      InitAnalogPinsPullDown();
      pinMode(LED_BLUE, OUTPUT);      digitalWrite(LED_BLUE, HIGH);
      pinMode(LED_RED, OUTPUT);      digitalWrite(LED_RED, HIGH);
      delay(100);
    
//      _Nectis.Bg96Begin();
//      _Nectis.InitLteM();

      Serial.println("### Bg96TurnOff().");
      Serial.println("### Bg96End().");

      _Nectis.Bg96TurnOff();
      _Nectis.Bg96End();

      // Put flash ROM into deep sleep mode.
      Serial.println("### Put the external flash ROM into deep sleep mode.");
      _Mcu.PutFlashRomIntoDeepSleepMode();
      delay(100);

      Serial.println("### Power supply OFF.");
      digitalWrite(GROVE_VCCB_PIN, LOW);
      delay(100);

      Serial.println("### Power supply cellular OFF.");
      digitalWrite(MODULE_PWRKEY_PIN, LOW);
      digitalWrite(MODULE_PWR_PIN, LOW);
      delay(100);

      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_RED, LOW);
      delay(100);
      
      // Disable the peripherals.
      _Mcu.DisableAllPeripherals();
      delay(100);

      // Enter System-Off deep sleep mode.
      _Mcu.EnterSystemOffDeepSleepMode();
      // CPU entered WFI/WFE sleep.
      _Mcu.EnterCpuWfiWfeSleep();

      break;

    case 44:
      Serial.println("44");

      pinMode(LED_BLUE, OUTPUT);      digitalWrite(LED_BLUE, HIGH);

      // For the test number 6-12, BG96 must be powered on.
      _Nectis.Bg96Begin();
      _Nectis.InitLteM();

      Serial.println("### Sending Board and SIM info to the database.");    // For Inspection
      _Mngt.Inspection();                                                   // For Inspection

      _Nectis.Bg96TurnOff();
      _Nectis.Bg96End();

      digitalWrite(LED_BLUE, LOW);

      break;

    default:
      Serial.printf("### This board is not required for Test number: %u.\n", input);
      break;
  }
}


void NectisTestHardware::InitRelayPins() {
  pinMode(relay_u9, OUTPUT);    digitalWrite(relay_u9, LOW);
  pinMode(relay_u2, OUTPUT);    digitalWrite(relay_u2, LOW);
  pinMode(relay_u3, OUTPUT);    digitalWrite(relay_u3, LOW);
  pinMode(relay_u4, OUTPUT);    digitalWrite(relay_u4, LOW);
  pinMode(relay_u5, OUTPUT);    digitalWrite(relay_u5, LOW);
  pinMode(relay_u6, OUTPUT);    digitalWrite(relay_u6, LOW);
  pinMode(relay_u7, OUTPUT);    digitalWrite(relay_u7, LOW);
  pinMode(relay_u8, OUTPUT);    digitalWrite(relay_u8, LOW);
}

void NectisTestHardware::InitAnalogPinsPullUp() {
  pinMode(GROVE_ANALOG_1_1, INPUT_PULLUP);
  pinMode(GROVE_ANALOG_1_2, INPUT_PULLUP);
  pinMode(GROVE_ANALOG_2_1, INPUT_PULLUP);
  pinMode(GROVE_ANALOG_2_2, INPUT_PULLUP);
  pinMode(GROVE_ANALOG_3_1, INPUT_PULLUP);
  pinMode(GROVE_ANALOG_3_2, INPUT_PULLUP);
}

void NectisTestHardware::InitAnalogPinsPullDown() {
  pinMode(GROVE_ANALOG_1_1, INPUT_PULLDOWN);
  pinMode(GROVE_ANALOG_1_2, INPUT_PULLDOWN);
  pinMode(GROVE_ANALOG_2_1, INPUT_PULLDOWN);
  pinMode(GROVE_ANALOG_2_2, INPUT_PULLDOWN);
  pinMode(GROVE_ANALOG_3_1, INPUT_PULLDOWN);
  pinMode(GROVE_ANALOG_3_2, INPUT_PULLDOWN);
}

void NectisTestHardware::InitGpioPins() {
  pinMode(GROVE_I2C_SCL_PIN, OUTPUT);     digitalWrite(GROVE_I2C_SCL_PIN, LOW);     // GPIO_4_1
  pinMode(GROVE_I2C_SDA_PIN, OUTPUT);     digitalWrite(GROVE_I2C_SDA_PIN, LOW);     // GPIO_4_2
  pinMode(GROVE_UART_RX_PIN, OUTPUT);     digitalWrite(GROVE_UART_RX_PIN, LOW);     // GPIO_5_1
  pinMode(GROVE_UART_TX_PIN, OUTPUT);     digitalWrite(GROVE_UART_TX_PIN, LOW);     // GPIO_5_2
  pinMode(GROVE_GPIO_6_1, OUTPUT);        digitalWrite(GROVE_GPIO_6_1, LOW);        // GPIO_6_1
  pinMode(GROVE_GPIO_6_2, OUTPUT);        digitalWrite(GROVE_GPIO_6_2, LOW);        // GPIO_6_2
}

void NectisTestHardware::ActivateRelayPins(uint16_t flags) {
  switch (flags & MASK_RELAY_HIGH_PIN) {
    case ACTIVATE_RELAY_PIN_5V0:
      Serial.println("### ACTIVATE_RELAY_PIN_5V0");
      digitalWrite(relay_u3, HIGH);
      digitalWrite(relay_u6, HIGH);
      digitalWrite(relay_u8, HIGH);
      break;

    case ACTIVATE_RELAY_PIN_4V5:
      Serial.println("### ACTIVATE_RELAY_PIN_4V5");
      digitalWrite(relay_u6, HIGH);
      digitalWrite(relay_u8, HIGH);
      break;

    case ACTIVATE_RELAY_PIN_4V2:
      Serial.println("### ACTIVATE_RELAY_PIN_4V2");
      digitalWrite(relay_u4, HIGH);
      digitalWrite(relay_u8, HIGH);
      break;

    case ACTIVATE_RELAY_PIN_3V8:
      Serial.println("### ACTIVATE_RELAY_PIN_3V8");
      digitalWrite(relay_u8, HIGH);
      break;

    case ACTIVATE_RELAY_PIN_G3V3:
      Serial.println("### ACTIVATE_RELAY_PIN_G3V3");
      digitalWrite(relay_u5, HIGH);
      digitalWrite(relay_u7, HIGH);
      break;

    case ACTIVATE_RELAY_PIN_3V3:
      Serial.println("### ACTIVATE_RELAY_PIN_3V3");
      digitalWrite(relay_u7, HIGH);
      break;

    case ACTIVATE_RELAY_PIN_1V8:
      Serial.println("### ACTIVATE_RELAY_PIN_1V8");
      break;
  }
}

void NectisTestHardware::PowerSupplyRelayPins(uint16_t flags) {
  switch (flags & MASK_RELAY_HIGH_PIN) {
    case POWER_SUPPLY_RELAY_PIN_3V7:
      Serial.println("### POWER_SUPPLY_RELAY_PIN_3V7");
      digitalWrite(relay_u2, HIGH);
      break;

    case POWER_SUPPLY_RELAY_PIN_5V0:
      Serial.println("### POWER_SUPPLY_RELAY_PIN_5V0");
      digitalWrite(relay_u2, LOW);
      break;
      
    default:
      Serial.println("### default");
      break;
  }
}

void NectisTestHardware::USBRelayPins(uint16_t flags) {
  switch (flags & MASK_RELAY_HIGH_PIN) {
    case DEACTIVATE_USB_PIN:
      Serial.println("### DEACTIVATE_USB_PIN");
      digitalWrite(relay_u9, HIGH);
      break;
  
    default:
      Serial.println("### default");
      break;
  }
}

void NectisTestHardware::ActivateGpioPins(uint16_t flags) {
  switch (flags & MASK_GPIO_PIN_READ) {
    case HIGH_4_2_N_READ_4_1:
      Serial.println("### HIGH_4_2_N_READ_4_1");
      pinMode(GROVE_I2C_SCL_PIN, INPUT);                                                 // GPIO_4_1
      pinMode(GROVE_I2C_SDA_PIN, OUTPUT);     digitalWrite(GROVE_I2C_SDA_PIN, HIGH);     // GPIO_4_2
      break;

    case LOW_4_2_N_READ_4_1:
      Serial.println("### LOW_4_2_N_READ_4_1");
      pinMode(GROVE_I2C_SCL_PIN, INPUT);                                                 // GPIO_4_1
      break;

    case HIGH_4_1_N_READ_4_2:
      Serial.println("### HIGH_4_1_N_READ_4_2");
      pinMode(GROVE_I2C_SDA_PIN, INPUT);                                                 // GPIO_4_2
      pinMode(GROVE_I2C_SCL_PIN, OUTPUT);     digitalWrite(GROVE_I2C_SCL_PIN, HIGH);     // GPIO_4_1
      break;

    case LOW_4_1_N_READ_4_2:
      Serial.println("### LOW_4_1_N_READ_4_2");
      pinMode(GROVE_I2C_SDA_PIN, INPUT);                                                 // GPIO_4_2
      break;

    case HIGH_5_2_N_READ_5_1:
      Serial.println("### HIGH_5_2_N_READ_5_1");
      pinMode(GROVE_UART_RX_PIN, INPUT);                                                 // GPIO_5_1
      pinMode(GROVE_UART_TX_PIN, OUTPUT);     digitalWrite(GROVE_UART_TX_PIN, HIGH);     // GPIO_5_2
      break;

    case LOW_5_2_N_READ_5_1:
      Serial.println("### LOW_5_2_N_READ_5_1");
      pinMode(GROVE_UART_RX_PIN, INPUT);                                                 // GPIO_5_1
      break;

    case HIGH_5_1_N_READ_5_2:
      Serial.println("### HIGH_5_1_N_READ_5_2");
      pinMode(GROVE_UART_TX_PIN, INPUT);                                                 // GPIO_5_2
      pinMode(GROVE_UART_RX_PIN, OUTPUT);     digitalWrite(GROVE_UART_RX_PIN, HIGH);     // GPIO_5_1
      break;

    case LOW_5_1_N_READ_5_2:
      Serial.println("### LOW_5_1_N_READ_5_2");
      pinMode(GROVE_UART_TX_PIN, INPUT);                                                 // GPIO_5_2
      break;

    case HIGH_6_2_N_READ_6_1:
      Serial.println("### HIGH_6_2_N_READ_6_1");
      pinMode(GROVE_GPIO_6_1, INPUT);                                                    // GPIO_6_1
      pinMode(GROVE_GPIO_6_2, OUTPUT);     digitalWrite(GROVE_GPIO_6_2, HIGH);           // GPIO_6_2
      break;

    case LOW_6_2_N_READ_6_1:
      Serial.println("### LOW_6_2_N_READ_6_1");
      pinMode(GROVE_GPIO_6_1, INPUT);                                                    // GPIO_6_1
      break;

    case HIGH_6_1_N_READ_6_2:
      Serial.println("### HIGH_6_1_N_READ_6_2");
      pinMode(GROVE_GPIO_6_2, INPUT);                                                    // GPIO_6_2
      pinMode(GROVE_GPIO_6_1, OUTPUT);     digitalWrite(GROVE_GPIO_6_1, HIGH);           // GPIO_6_1
      break;

    case LOW_6_1_N_READ_6_2:
      Serial.println("### LOW_6_1_N_READ_6_2");
      pinMode(GROVE_GPIO_6_2, INPUT);                                                    // GPIO_6_2
      break;

    default:
      Serial.println("### default");
      break;
  }
}

float NectisTestHardware::ReadADValue(uint8_t pin) {
  int adcValue = 0;
  float mvPerLsb = 3600.0F / 1024.0F; // 10-bit ADC with 3.6V input range
  float readValue = 0;

  // Set the analog reference to 3.6V (default = 3.6V)
  analogReference(AR_INTERNAL);
  // Set the resolution to 10-bit (0..1023)
  analogReadResolution(10); // Can be 8, 10, 12 or 14

  // Let the ADC settle
  delay(100);

  adcValue = analogRead(pin);
  readValue = (float)(adcValue * mvPerLsb);

  return readValue;
}

float NectisTestHardware::ReadVbat() {
#define VBAT_MV_PER_LSB   (1.171875F)       // 1.2V ADC range and 10-bit ADC resolution = 1200mV/1024
#define VBAT_DIVIDER      (0.25F)           // From IC: RP124N334E

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);

  int adcvalue = 0;

  // Set the analog reference to 1.2V (default = 3.6V)
  analogReference(AR_INTERNAL_1_2);

  // Set the resolution to 10-bit (0..1023)
  analogReadResolution(10); // Can be 8, 10, 12 or 14

  // Let the ADC settle
  delay(100);

  // Get the raw 10-bit, 0..1200mV ADC value
  adcvalue = analogRead(BATTERY_VOLTAGE_PIN);
  while ((adcvalue < 0) || (adcvalue > 1023)) {
    adcvalue = analogRead(BATTERY_VOLTAGE_PIN);
  }

  // Convert the raw value to compensated mv, taking the resistor-
  // divider into account (providing the actual LIPO voltage)
  float battery_voltage_mv = (float) adcvalue * VBAT_MV_PER_LSB * (1 / VBAT_DIVIDER);

  // Set the ADC back to the default settings
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);

  return battery_voltage_mv;
}

float NectisTestHardware::ReadVusb() {
  float mv_per_lsb = 3600.0F / 1024.0F; // 10-bit ADC with 3.6V input range

  int adcvalue = 0;
  float battery_level_mv = 0;

  // Get a fresh ADC value
  adcvalue = analogRead(USB_VOLTAGE_PIN);
  battery_level_mv = (float)adcvalue * mv_per_lsb;

  return battery_level_mv * 2;
}

float NectisTestHardware::ReadAnalogPin(uint16_t flags) {
  float readValue = 0;

  switch (flags & MASK_ANALOG_PIN_READ) {
    // 4.2V
    case A0_INPUT:
      Serial.println("### Read Value of A0");
      readValue = ReadVbat();
      break;

      // 2.5V
    case A1_INPUT:
      Serial.println("### Read Value of A1");
      readValue = ReadVusb();
      break;

    case A2_INPUT:
      Serial.println("### Read Value of A2");
      readValue = ReadADValue(GROVE_ANALOG_1_1);
      break;

    case A3_INPUT:
      Serial.println("### Read Value of A3");
      readValue = ReadADValue(GROVE_ANALOG_1_2);
      break;

    case A4_INPUT:
      Serial.println("### Read Value of A4");
      readValue = ReadADValue(GROVE_ANALOG_2_1);
      break;

    case A5_INPUT:
      Serial.println("### Read Value of A5");
      readValue = ReadADValue(GROVE_ANALOG_2_2);
      break;

    case A6_INPUT:
      Serial.println("### Read Value of A6");
      readValue = ReadADValue(GROVE_ANALOG_3_1);
      break;

    case A7_INPUT:
      Serial.println("### Read Value of A7");
      readValue = ReadADValue(GROVE_ANALOG_3_2);
      break;

    default:
      Serial.println("### This pin is not defined.");
      break;
  }
  return readValue;
}

float NectisTestHardware::ReadGpioPin(uint16_t flags) {
  float readValue = 0;

  switch (flags & MASK_GPIO_PIN_READ) {
    case HIGH_4_2_N_READ_4_1:
      Serial.println("### Read Value of GPIO_4_1, HIGH GPIO_4_2");
      readValue = (float)(digitalRead(GROVE_I2C_SCL_PIN));
      break;

    case LOW_4_2_N_READ_4_1:
      Serial.println("### Read Value of GPIO_4_1, LOW GPIO_4_2");
      readValue = (float)(digitalRead(GROVE_I2C_SCL_PIN));

      break;

    case HIGH_4_1_N_READ_4_2:
      Serial.println("### Read Value of GPIO_4_2, HIGH GPIO_4_1");
      readValue = (float)(digitalRead(GROVE_I2C_SDA_PIN));
      break;

    case LOW_4_1_N_READ_4_2:
      Serial.println("### Read Value of GPIO_4_2, LOW GPIO_4_1");
      readValue = (float)(digitalRead(GROVE_I2C_SDA_PIN));
      break;

    case HIGH_5_2_N_READ_5_1:
      Serial.println("### Read Value of GPIO_5_1, HIGH GPIO_5_2");
      readValue = (float)(digitalRead(GROVE_UART_RX_PIN));
      break;

    case LOW_5_2_N_READ_5_1:
      Serial.println("### Read Value of GPIO_5_1, LOW GPIO_5_2");
      readValue = (float)(digitalRead(GROVE_UART_RX_PIN));
      break;

    case HIGH_5_1_N_READ_5_2:
      Serial.println("### Read Value of GPIO_5_2, HIGH GPIO_5_1");
      readValue = (float)(digitalRead(GROVE_UART_TX_PIN));
      break;

    case LOW_5_1_N_READ_5_2:
      Serial.println("### Read Value of GPIO_5_2, LOW GPIO_5_1");
      readValue = (float)(digitalRead(GROVE_UART_TX_PIN));
      break;

    case HIGH_6_2_N_READ_6_1:
      Serial.println("### Read Value of GPIO_6_1, HIGH GPIO_6_2");
      readValue = (float)(digitalRead(GROVE_GPIO_6_1));
      break;

    case LOW_6_2_N_READ_6_1:
      Serial.println("### Read Value of GPIO_6_1, LOW GPIO_6_2");
      readValue = (float)(digitalRead(GROVE_GPIO_6_1));
      break;

    case HIGH_6_1_N_READ_6_2:
      Serial.println("### Read Value of GPIO_6_2, HIGH GPIO_6_1");
      readValue = (float)(digitalRead(GROVE_GPIO_6_2));
      break;

    case LOW_6_1_N_READ_6_2:
      Serial.println("### Read Value of GPIO_6_2, LOW GPIO_6_1");
      readValue = (float)(digitalRead(GROVE_GPIO_6_2));
      break;

    default:
      Serial.println("### This pin is not defined.");
      break;
  }
  return readValue;
}

