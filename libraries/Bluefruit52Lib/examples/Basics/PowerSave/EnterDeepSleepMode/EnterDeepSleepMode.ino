#include <SPI.h>
#include "nrf_power.h"
#include <NectisCellular.h>

#define SLAVE_SELECT_PIN      PIN_SPI_CS

NectisCellular Nectis;

// cf. nRF52840 product specification p.69
// Note: Watchdog reset is not available in System OFF.


void setup() {
  // Wake up from System_Off sleep mode.
//  NRF_UART0->ENABLE = 1;  //disable all UART instance
//  NRF_UARTE0->ENABLE = 1;
//  NRF_UARTE1->ENABLE = 1;
//  NRF_SAADC->ENABLE = 1; //disable ADC
//  NRF_PWM0->ENABLE = 1; //disable all pwm instance
//  NRF_PWM1->ENABLE = 1;
//  NRF_PWM2->ENABLE = 1;
//  NRF_TWIM1->ENABLE = 1; //disable TWI Master
//  NRF_TWIS1->ENABLE = 1; //disable TWI Slave
//
//  NRF_SPI0->ENABLE = 1; //disable SPI
//  NRF_SPI1->ENABLE = 1; //disable SPI
//  NRF_SPI2->ENABLE = 1; //disable SPI
//  NRF_QSPI->ENABLE = 1; //disable QSPI

//  NRF_POWER->SYSTEMOFF = (0UL);
//  NRF_POWER->EVENTS_SLEEPEXIT = (1UL);

//  NRF_POWER->RAM[0].POWER = (1UL);

  delay(4000);

  Serial.begin(115200);
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

  // Use SPI between flash ROM in order to put it into deep sleep mode.
  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  SPI.begin();

  Nectis.Bg96Begin();
  Nectis.InitLteM();
  delay(100);


  // When the MCU is in deep sleep mode, LEDs are turned off.
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


  // Put flash ROM into deep sleep mode.
  Serial.println("Put flash ROM into deep sleep mode");
  digitalWrite(SLAVE_SELECT_PIN, LOW);
  SPI.transfer(0xB9);
  digitalWrite(SLAVE_SELECT_PIN, HIGH);

  // Turn off BG96 casting AT commands.
  Serial.println("Turn off BG96 casting AT commands.");
  Nectis.Bg96TurnOff();
  delay(100);
  // Disable Uart between nRF52840 and BG96.
  Serial.println("End Uart between nRF52840 and BG96.");
  Nectis.Bg96End();
  delay(100);

  Serial.println("### Power supply OFF.");
  digitalWrite(GROVE_VCCB_PIN, LOW);
  delay(100);

  Serial.println("### Power supply cellular OFF.");
  digitalWrite(MODULE_PWRKEY_PIN, LOW);
  digitalWrite(MODULE_PWR_PIN, LOW);
  delay(100);

  Serial.println("Enter deep sleep mode.");

  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);

  // Disable the peripherals.
//  NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;
//  NRF_UARTE0->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;
//  NRF_UARTE1->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;
//
//  NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos;
//
//  NRF_PWM0->ENABLE = PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos;
//  NRF_PWM1->ENABLE = PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos;
//  NRF_PWM2->ENABLE = PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos;
//
//  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
//  NRF_TWI1->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
//
//  NRF_SPI0->ENABLE = SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos;
//  NRF_SPI1->ENABLE = SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos;
//  NRF_SPI2->ENABLE = SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos;
//
//  NRF_QSPI->ENABLE = QSPI_ENABLE_ENABLE_Disabled << QSPI_ENABLE_ENABLE_Pos;
//
//  NRF_NFCT->TASKS_DISABLE = 0x1UL << NFCT_TASKS_DISABLE_TASKS_DISABLE_Pos;


  NRF_UART0->ENABLE = 0;  //disable all UART instance
  NRF_UARTE0->ENABLE = 0;
  NRF_UARTE1->ENABLE = 0;

  NRF_SAADC->ENABLE = 0; //disable ADC

  NRF_PWM0->ENABLE = 0; //disable all pwm instance
  NRF_PWM1->ENABLE = 0;
  NRF_PWM2->ENABLE = 0;

  NRF_TWI0->ENABLE = 0; //disable TWI
  NRF_TWI1->ENABLE = 0;

  NRF_SPI0->ENABLE = 0; //disable all SPI
  NRF_SPI1->ENABLE = 0;
  NRF_SPI2->ENABLE = 0;

  NRF_QSPI->ENABLE = 0; //disable QSPI

  NRF_NFCT->TASKS_DISABLE = 1; //disable NFC, confirm this is the right way

  delay(1000);



//  NRF_POWER->RAM[4].POWER = (0UL);

  // Enter System-Off deep sleep mode.
  NRF_POWER->SYSTEMOFF = POWER_SYSTEMOFF_SYSTEMOFF_Enter << POWER_SYSTEMOFF_SYSTEMOFF_Pos;
  // nrf_power_system_off();

  // CPU entered WFI/WFE sleep.
  NRF_POWER->EVENTS_SLEEPENTER = 0x1UL << POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Pos;

//  NRF_POWER->SYSTEMOFF = (1UL);
//
//  NRF_POWER->EVENTS_SLEEPENTER = (1UL);
}

void loop() {

}
