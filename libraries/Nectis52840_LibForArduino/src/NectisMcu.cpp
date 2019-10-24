#include "SPI.h"
#include "NectisMcu.h"

char hexConvertedFromDecimal[16];


NectisMcu::NectisMcu() {

}

float NectisMcu::ReadVusb() {
  float mv_per_lsb = 3600.0F / 1024.0F; // 10-bit ADC with 3.6V input range

  int adcvalue = 0;
  float battery_level_mv = 0;

  // Get a fresh ADC value
  adcvalue = analogRead(USB_VOLTAGE_PIN);
  battery_level_mv = (float) adcvalue * mv_per_lsb;

  return battery_level_mv;
}

float NectisMcu::ReadVbat(void) {
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

  Serial.printf("adc_value: %d\n", adcvalue);

  // Convert the raw value to compensated mv, taking the resistor-
  // divider into account (providing the actual LIPO voltage)
  float battery_voltage_mv = (float) adcvalue * VBAT_MV_PER_LSB * (1 / VBAT_DIVIDER);

  // Set the ADC back to the default settings
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);

  return battery_voltage_mv;
}

float NectisMcu::mvToPercent(float mvolts) {
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


void NectisMcu::PwmSetup(int pin, uint8_t flash_interval) {
  HwPWM0.addPin(pin);

  // Enable PWM modules with 15-bit resolutions(max) but different clock div
  HwPWM0.setResolution(15);
  HwPWM0.setClockDiv(flash_interval);
}

void NectisMcu::PwmBegin() {
  HwPWM0.begin();
}

void NectisMcu::PwmWritePin(int pin) {
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

void NectisMcu::PwmStop() {
  HwPWM0.stop();
}

void NectisMcu::PwmActivate(int pin, uint8_t flash_interval) {
  PwmSetup(pin, flash_interval);
  NectisMcu::PwmBegin();
  PwmWritePin(pin);
  PwmStop();
}


char *NectisMcu::ConvertDecimalToHex(unsigned long int const decimal, int byte_size) {
  // The last index of post_data is filled with 0x00 for print function.
  memset(&hexConvertedFromDecimal[0], 0x00, sizeof(hexConvertedFromDecimal));
  // Serial.printf("ConvertDecimalToHex decimal: %u\n", decimal);

  for (int i = 0; i < (int) byte_size; i++) {
    // 16進数に変換し、４ビットずつ post_data を埋めていく
    hexConvertedFromDecimal[i] = (decimal >> (8 * ((byte_size - 1) - i))) & 0xff;
    // Serial.printf("(decimal >> (8*((byte_size-1)-i))):%x\n", (decimal >> (8 * ((byte_size - 1) - i))));
    // Serial.printf("hexConvertedFromDecimal[i]:%02x\n", hexConvertedFromDecimal[i]);
  }
  return hexConvertedFromDecimal;
}

unsigned int NectisMcu::GetDataDigits(unsigned int data) {
  // Copy the original data to calculate digits in order not to affect the original value.
  unsigned int data_to_calc_digit = data;
  unsigned int data_digit_hex = 0;

  // Calculating the digits of lat, lng in hexadecimal.
  // 2 digits = 1 byte
  // Calculating the bytes of the post data
  while (data_to_calc_digit != 0) {
    data_to_calc_digit /= 16;
    data_digit_hex++;
  }
  unsigned int size_of_post_data = (int) (ceil((double) data_digit_hex / 2));

  return size_of_post_data;
}

char *NectisMcu::ConvertIntoBinary(char *PostDataBinary, uint8_t data, unsigned int data_length) {
  memset(&PostDataBinary[0], 0x00, data_length);
  memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);

  return PostDataBinary;
}

char *NectisMcu::ConvertIntoBinary(char *PostDataBinary, uint16_t data, unsigned int data_length) {
  memset(&PostDataBinary[0], 0x00, data_length);
  memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);

  return PostDataBinary;
}

char *NectisMcu::ConvertIntoBinary(char *PostDataBinary, uint32_t data, unsigned int data_length) {
  memset(&PostDataBinary[0], 0x00, data_length);
  memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);

  return PostDataBinary;
}

char *NectisMcu::ConvertIntoBinary(char *PostDataBinary, int data, unsigned int data_length) {
  memset(&PostDataBinary[0], 0x00, data_length);
  memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);

  return PostDataBinary;
}

void NectisMcu::PutFlashRomIntoDeepSleepMode() {
  SPI.begin();

  // SLAVE_SELECT_PIN == PIN_SPI_CS
  // set the slaveSelectPin as an output:
  pinMode(PIN_SPI_CS, OUTPUT);

  digitalWrite(PIN_SPI_CS, LOW);
  SPI.transfer(0xB9);
  digitalWrite(PIN_SPI_CS, HIGH);

  SPI.end();
}

void NectisMcu::WakeUpFlashRomFromDeepSleepMode() {
  SPI.begin();

  // SLAVE_SELECT_PIN == PIN_SPI_CS
  // set the slaveSelectPin as an output:
  pinMode(PIN_SPI_CS, OUTPUT);

  digitalWrite(PIN_SPI_CS, LOW);
  SPI.transfer(0xAB);
  digitalWrite(PIN_SPI_CS, HIGH);

  SPI.end();
}

void NectisMcu::SoftReset() {
  NVIC_SystemReset();
}

// In nRF52832, P0 is GPIO PORT 0, which implements pin 0-31.
// nRF52840 also implements P1, for the additional GPIO pins (P1.00 - P1.15).
// https://devzone.nordicsemi.com/f/nordic-q-a/19198/what-is-nrf_p0-in-the-sdk_path-components-drivers_nrf-hal-nrf_gpio-h/74367#74367
// RTC_INTRB pin is SIO09, which is also P0.09. Therefore we use RTC_INTRB pin as NRF_P0.
void NectisMcu::ConfigForWakingUpFromDeepSleep() {
//  NRF_GPIO_Type* rtcPort = RTC_INTRB;
  NRF_P0->PIN_CNF[RTC_INTRB] =
    (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos) |
    (GPIO_DETECTMODE_DETECTMODE_Default << GPIO_DETECTMODE_DETECTMODE_Pos) |
    (GPIO_PIN_CNF_PULL_Pullup << GPIO_PIN_CNF_PULL_Pos) |
    (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
    (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
}

void NectisMcu::DisableAllPeripherals() {
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

void NectisMcu::EnterSystemOffDeepSleepMode() {
  NRF_POWER->SYSTEMOFF = POWER_SYSTEMOFF_SYSTEMOFF_Enter << POWER_SYSTEMOFF_SYSTEMOFF_Pos;
}

void NectisMcu::EnterCpuWfiWfeSleep() {
  // CPU enters WFI/WFE sleep.
  // Dont call this method when you use RTC, because this prevents CPU to wake up by the RTC.
  NRF_POWER->EVENTS_SLEEPENTER = POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Generated << POWER_EVENTS_SLEEPENTER_EVENTS_SLEEPENTER_Pos;
}

void NectisMcu::ExitCpuWfiWfeSleep() {
  NRF_POWER->EVENTS_SLEEPEXIT = POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Generated << POWER_EVENTS_SLEEPEXIT_EVENTS_SLEEPEXIT_Pos;
}

void NectisMcu::WatchdogTimerInit(const int wdtTimeoutSec) {
  // Configure Watchdog. a) Pause watchdog while the CPU is halted by the debugger.  b) Keep the watchdog running while the CPU is sleeping.
  NRF_WDT->CONFIG = (WDT_CONFIG_HALT_Pause << WDT_CONFIG_HALT_Pos) | (WDT_CONFIG_SLEEP_Run << WDT_CONFIG_SLEEP_Pos);
  // timeout [s] = ( CRV + 1 ) / 32768
  NRF_WDT->CRV = wdtTimeoutSec * 32768;
  // Enable reload register 0
  NRF_WDT->RREN |= WDT_RREN_RR0_Msk;
  // Start the Watchdog timer
  NRF_WDT->TASKS_START = 1;
}

void NectisMcu::WatchdogTimerDelay(int delayMilliSeconds) {
  int startTime = millis();
  while ((millis() - startTime) <= delayMilliSeconds);
}

void NectisMcu::ReloadWatchdogTimer() {
  NRF_WDT->RR[0] = WDT_RR_RR_Reload;
  NRF_WDT->TASKS_START = 1;
}
