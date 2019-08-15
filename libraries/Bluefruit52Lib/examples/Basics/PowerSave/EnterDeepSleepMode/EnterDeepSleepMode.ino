#include <SPI.h>
#include "nrf_power.h"
#include <NectisCellular.h>

////////////////////////////////////////////////////////////////////////////////
// Defines

#define BOOT_INTERVAL_SECOND   (30)  // [sec.]
#define SLAVE_SELECT_PIN      PIN_SPI_CS

////////////////////////////////////////////////////////////////////////////////
// Global variables

NectisCellular Nectis;

////////////////////////////////////////////////////////////////////////////////
// setup and loop


// Using the power-fail comparator (POF) is optional. When enabled, it can provide the CPU an early warning
// of an impending power supply failure.
// p.65



void setup() {
  // Wake up from System_Off sleep mode.
  NRF_UART0->ENABLE = 1;  //disable all UART instance
  NRF_UARTE0->ENABLE = 1;
  NRF_UARTE1->ENABLE = 1;
  NRF_SAADC->ENABLE = 1; //disable ADC
  NRF_PWM0->ENABLE = 1; //disable all pwm instance
  NRF_PWM1->ENABLE = 1;
  NRF_PWM2->ENABLE = 1;
  NRF_TWIM1->ENABLE = 1; //disable TWI Master
  NRF_TWIS1->ENABLE = 1; //disable TWI Slave

  NRF_SPI0->ENABLE = 1; //disable SPI
  NRF_SPI1->ENABLE = 1; //disable SPI
  NRF_SPI2->ENABLE = 1; //disable SPI
  NRF_QSPI->ENABLE = 1; //disable QSPI

//  NRF_POWER->SYSTEMOFF = (0UL);
//  NRF_POWER->EVENTS_SLEEPEXIT = (1UL);

//  NRF_POWER->RAM[0].POWER = (1UL);





  delay(4000);

  Serial.begin(115200);
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");

  ////////////////////////////////////////
  // Low-level initialize

  Serial.println("### I/O Initialize.");
  Nectis.Init();
  delay(100);

  Serial.println("### Power supply cellular ON.");
  Nectis.PowerSupplyCellular(true);
  delay(100);

  Serial.println("### Power supply ON.");
  //  Make sure that the MODULE_PWR_PIN is set to HIGH.
  Nectis.PowerSupplyGrove(true);

  // set the slaveSelectPin as an output:
  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  // initialize SPI:
  SPI.begin();

  Nectis.Bg96Begin();
  Nectis.InitLteM();
  delay(100);


  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
    delay(1000);

    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, HIGH);
    delay(1000);
  }

  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);






//  for (int i = 0; i < 16; i++) {
//    Serial.print("NRF_POWER->RAM ");
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.println(NRF_POWER->RAM[i].POWER);
//    delay(100);
//  }





//  for (int i = 0; i < 9;  i++) {
//    NRF_POWER->RAM[i].POWER = 0;
//  }

  Serial.println("Enter deep power-down mode");
  // take the SS pin low to select the chip:
  digitalWrite(SLAVE_SELECT_PIN, LOW);
  //  send value via SPI:
  SPI.transfer(0xB9);
  // take the SS pin high to de-select the chip:
  digitalWrite(SLAVE_SELECT_PIN, HIGH);

  // Turn off BG96 casting AT commands.
  Serial.println("BG96TurnOff");
  Nectis.Bg96TurnOff();
  delay(100);
  // End Uart between nRF52840 and BG96.
  Serial.println("Bg96End");
  Nectis.Bg96End();
  delay(100);

//  Serial.println("### Power supply OFF.");
//  digitalWrite(GROVE_VCCB_PIN, LOW);
//  delay(100);
//
//  Serial.println("### Power supply cellular OFF.");
//  digitalWrite(MODULE_PWRKEY_PIN, LOW);
//  digitalWrite(MODULE_PWR_PIN, LOW);
//  delay(100);

  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);




  // nrf_power_task_trigger(NRF_POWER_TASK_LOWPWR);
  // nrf_power_system_off();

  // Disable the pins.
  NRF_UART0->ENABLE = 0;  //disable all UART instance
  NRF_UARTE0->ENABLE = 0;
  NRF_UARTE1->ENABLE = 0;
  NRF_SAADC->ENABLE = 0; //disable ADC
  NRF_PWM0->ENABLE = 0; //disable all pwm instance
  NRF_PWM1->ENABLE = 0;
  NRF_PWM2->ENABLE = 0;
  NRF_TWIM1->ENABLE = 0; //disable TWI Master
  NRF_TWIS1->ENABLE = 0; //disable TWI Slave

  NRF_SPI0->ENABLE = 0; //disable SPI
  NRF_SPI1->ENABLE = 0; //disable SPI
  NRF_SPI2->ENABLE = 0; //disable SPI

  NRF_QSPI->ENABLE = 0; //disable QSPI
  NRF_QSPI->DPMDUR = 0; //enter deep sleep mode

  NRF_NFCT->TASKS_DISABLE = 1; //disable NFC, confirm this is the right way

  delay(1000);

  NRF_POWER->RAM[4].POWER = (0UL);

  // Enter System_Off sleep mode.
  NRF_POWER->SYSTEMOFF = (1UL);

  NRF_POWER->EVENTS_SLEEPENTER = (1UL);
}

void loop() {
//  uint8_t val;
//  Rtc.EepromRead(0, &val, sizeof(val));
//  Serial.print("EEPROM value is ");
//  Serial.println(val);
//
//  val++;
//  Rtc.EepromWrite(0, &val, sizeof(val));
//
//  Rtc.SetWakeupPeriod(BOOT_INTERVAL_SECOND);
//
//  Serial.println("Shutdown.");
//  Rtc.Shutdown();
//  delay(1000);
//
//  NRF_POWER->RAM[0].POWER = (0UL);
//  NRF_POWER->SYSTEMOFF = (1UL);
//  NRF_POWER->EVENTS_SLEEPENTER = (1UL);
//
//  while (1) {
//    Serial.println("RTC sleep");
//    delay(1000);
//  }
}

////////////////////////////////////////////////////////////////////////////////
