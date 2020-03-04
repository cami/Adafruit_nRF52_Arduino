#include "NectisMcu.h"
#include <Arduino.h>


namespace mcu {

/*
 * GPIO pins on board
 */
void InitPins(void) {
  ////////////////////
  // Module
  
  // Power Supply
  pinMode(MODULE_PWR_PIN, OUTPUT);            digitalWrite(MODULE_PWR_PIN, LOW);
  // Turn On/Off
  pinMode(MODULE_PWRKEY_PIN, OUTPUT);         digitalWrite(MODULE_PWRKEY_PIN, LOW);
  pinMode(MODULE_RESET_PIN, OUTPUT);          digitalWrite(MODULE_RESET_PIN, LOW);
  // Status Indication
  pinMode(MODULE_STATUS_PIN, INPUT_PULLUP);
  // Main SerialUART Interface
  pinMode(MODULE_DTR_PIN, OUTPUT);            digitalWrite(MODULE_DTR_PIN, LOW);
  
  ////////////////////
  // Led
  pinMode(LED_RED, OUTPUT);                   digitalWrite(LED_RED, LOW);
  pinMode(LED_BLUE, OUTPUT);                  digitalWrite(LED_BLUE, LOW);
  ////////////////////
  
  // AD Converter
  pinMode(BATTERY_LEVEL_ENABLE_PIN, OUTPUT);
  
  // Grove
  pinMode(GROVE_VCCB_PIN, OUTPUT);            digitalWrite(GROVE_VCCB_PIN, LOW);

  // RTC
  pinMode(RTC_INTRB, INPUT_PULLUP);           digitalWrite(RTC_INTRB, HIGH);
  pinMode(RTC_I2C_SDA, OUTPUT);               digitalWrite(RTC_I2C_SDA, HIGH);
}

void PowerSupplyCellular(bool on) {
  digitalWrite(MODULE_PWR_PIN, on ? HIGH : LOW);
  delay(200);
  digitalWrite(MODULE_PWRKEY_PIN, on ? HIGH : LOW);
  delay(600);
  digitalWrite(MODULE_PWRKEY_PIN, LOW);
}

void PowerSupplyGrove(bool on) {
  digitalWrite(MODULE_PWR_PIN, on ? HIGH : LOW);
  delay(100);
  digitalWrite(GROVE_VCCB_PIN, on ? HIGH : LOW);
}

void InitBoard(void) {
  Serial.println("### I/O Initialize.");
  InitPins();
  delay(100);

  Serial.println("### Power supply cellular ON.");
  PowerSupplyCellular(true);
  delay(100);

  Serial.println("### Power supply ON.");
  // Make sure that the MODULE_PWR_PIN is set to HIGH.
  PowerSupplyGrove(true);
  delay(100);
}

/*
 * USB to UART Serial
 */
void ClearSerialBuffer(void) {
  Serial.flush();
  delay(10);
}

/*
 * Onboard LEDs
 */
void TurnOnOffRedLed(bool on) {
  digitalWrite(LED_RED, on ? HIGH : LOW);
}

void TurnOnOffGreenLed(bool on) {
  digitalWrite(LED_BLUE, on ? HIGH : LOW);
}


/*
 * AD Converter
 */
float ReadVusb(void) {
  float mv_per_lsb = 3600.0F / 1024.0F; // 10-bit ADC with 3.6V input range

  int adcvalue = 0;
  float battery_level_mv = 0;

  // Get a fresh ADC value
  adcvalue = analogRead(USB_VOLTAGE_PIN);
  battery_level_mv = (float) adcvalue * mv_per_lsb;

  return battery_level_mv;
}

float ReadVbat(void) {
  constexpr float VBAT_MV_PER_LSB = 1.171875F;    // 1.2V ADC range and 10-bit ADC resolution = 1200mV/1024
  constexpr float VBAT_DIVIDER = 0.25F;           // From IC: RP124N334E

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);

  int adcvalue = 0;

  // Set the analog reference to 1.2V (default = 3.6V)
  analogReference(AR_INTERNAL_1_2);

  // Set the resolution to 10-bit (0..1023)
  analogReadResolution(10); // Can be 8, 10, 12 or 14

  // Let the ADC settle
  delay(100);

  // Get the raw 10-bit, 0..1200mV ADC value
  adcvalue = analogRead(PIN_BATTERY_VOLTAGE);
  while ((adcvalue < 0) || (adcvalue > 1023)) {
    adcvalue = analogRead(PIN_BATTERY_VOLTAGE);
  }

  Serial.printf("adc_value=%d\n", adcvalue);

  // Convert the raw value to compensated mv, taking the resistor-
  // divider into account (providing the actual LIPO voltage)
  float battery_voltage_mv = (float) adcvalue * VBAT_MV_PER_LSB * (1 / VBAT_DIVIDER);

  // Set the ADC back to the default settings
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);

  return battery_voltage_mv;
}

float mvToPercent(float mvolts) {
  float battery_level;

  // When mvolts drops to (3200mA * 102%), the power supply from the battery shut down.
  // Therefore, 0% of the battery level is set to 3250mA.
  if (mvolts >= 4150) {
    battery_level = 100;
  } else if (mvolts > 3750) {
    battery_level = 100.0 * (1.0 - (4150 - mvolts) / 900);
  } else if (mvolts > 3650) {
    battery_level = 50;
  } else if (mvolts > 3250) {
    battery_level = 100.0 * (1.0 - (4150 - mvolts) / 900);
  } else {
    battery_level = 0;
  }

  return battery_level;
}


/*
 * PWM
 */
void PwmSetup(int pin, uint8_t flash_interval) {
  HwPWM0.addPin(pin);

  // Enable PWM modules with 15-bit resolutions(max) but different clock div
  HwPWM0.setResolution(15);
  HwPWM0.setClockDiv(flash_interval);
}

void PwmBegin(void) {
  HwPWM0.begin();
}

void PwmStop(void) {
  HwPWM0.stop();
}

void PwmWritePin(int pin) {
  const int maxValue = bit(15) - 1;

  // fade in from min to max
  for (int fadeValue = 0; fadeValue <= maxValue; fadeValue += 1024) {
    // Write same value but inverted for Led Blue
    HwPWM0.writePin(pin, fadeValue, false);

    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min
  for (int fadeValue = maxValue; fadeValue >= 0; fadeValue -= 1024) {
    // Write same value but inverted for Led Blue
    HwPWM0.writePin(pin, fadeValue, false);

    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}


/*
 * Software register
 */
void SoftReset(void) {
  NVIC_SystemReset();
}


/*
 * Deep Sleep Mode
 */
void DisableAllPeripherals(void) {
  // Disable the peripherals.
  NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;
  NRF_UARTE0->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;
  NRF_UARTE1->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;

  NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos;

  NRF_PWM0->ENABLE = PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos;
  NRF_PWM1->ENABLE = PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos;
  NRF_PWM2->ENABLE = PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos;

  NRF_TWI0->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
  NRF_TWI1->ENABLE = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;

  NRF_SPI0->ENABLE = SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos;
  NRF_SPI1->ENABLE = SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos;
  NRF_SPI2->ENABLE = SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos;

  NRF_QSPI->ENABLE = QSPI_ENABLE_ENABLE_Disabled << QSPI_ENABLE_ENABLE_Pos;

  NRF_NFCT->TASKS_DISABLE = 0x1UL << NFCT_TASKS_DISABLE_TASKS_DISABLE_Pos;
  NRF_RADIO->TASKS_DISABLE = 0x1UL << RADIO_TASKS_DISABLE_TASKS_DISABLE_Pos;
}

// In nRF52832, P0 is GPIO PORT 0, which implements pin 0-31.
// nRF52840 also implements P1, for the additional GPIO pins (P1.00 - P1.15).
// https://devzone.nordicsemi.com/f/nordic-q-a/19198/what-is-nrf_p0-in-the-sdk_path-components-drivers_nrf-hal-nrf_gpio-h/74367#74367
// RTC_INTRB pin is SIO09, which is also P0.09. Therefore we use RTC_INTRB pin as NRF_P0.
void ConfigForDeepSleepWakeup(void) {
//  NRF_GPIO_Type* rtcPort = RTC_INTRB;
  NRF_P0->PIN_CNF[RTC_INTRB] =
    (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos) |
    (GPIO_DETECTMODE_DETECTMODE_Default << GPIO_DETECTMODE_DETECTMODE_Pos) |
    (GPIO_PIN_CNF_PULL_Pullup << GPIO_PIN_CNF_PULL_Pos) |
    (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
    (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
}

void EnterSystemOffDeepSleep(void) {
  NRF_POWER->SYSTEMOFF = POWER_SYSTEMOFF_SYSTEMOFF_Enter << POWER_SYSTEMOFF_SYSTEMOFF_Pos;
}

void EnterCpuWfiWfeSleep(void) {
  // CPU enters WFI/WFE sleep.
  // Dont call this method when you use RTC, because this prevents CPU to wake up by the RTC.
  NRF_POWER->EVENTS_SLEEPENTER = POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Generated << POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Pos;
}

void ExitCpuWfiWfeSleep(void) {
  NRF_POWER->EVENTS_SLEEPEXIT = POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Generated << POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Pos;
}


/*
 * WathcDog
 */
void WatchdogTimerInit(const int wdtTimeoutSec) {
  // Configure Watchdog. a) Pause watchdog while the CPU is halted by the debugger.  b) Keep the watchdog running while the CPU is sleeping.
  NRF_WDT->CONFIG = (WDT_CONFIG_HALT_Pause << WDT_CONFIG_HALT_Pos) | (WDT_CONFIG_SLEEP_Run << WDT_CONFIG_SLEEP_Pos);
  // timeout [s] = ( CRV + 1 ) / 32768
  NRF_WDT->CRV = wdtTimeoutSec * 32768;
  // Enable reload register 0
  NRF_WDT->RREN |= WDT_RREN_RR0_Msk;
  // Start the Watchdog timer
  NRF_WDT->TASKS_START = 1;
}

void ReloadWatchdogTimer(void) {
  NRF_WDT->RR[0] = WDT_RR_RR_Reload;
  NRF_WDT->TASKS_START = 1;
}

} // namespace mcu