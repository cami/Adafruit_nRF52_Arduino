#include <SPI.h>
#include "nrf_power.h"
#include <NectisCellular.h>
#include <NectisMcu.h>
#include <NectisRTC.h>

NectisCellular Nectis;
NectisMcu Mcu;
NectisRTC Rtc;

// cf. nRF52840 product specification p.69
// Note: Watchdog reset is not available in System OFF.
const char* RtcAlarmTableTime[] = {
  "17:22"
};

// RtcAlarmTableDayofweek stands for the day of week.
// If you wake up MCU on Saturdays,  RtcAlarmTableDayofweek = 0b00111111
// If you wake up MCU on Sundays,  RtcAlarmTableDayofweek = 0b01111110
// If you only wake up MCU on weekdays, RtcAlarmTableDayofweek = 0b00111110
const uint8_t RtcAlarmTableDayofweek = 0b00111110;


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

  Serial.println("### Power supply ON.");
  // Make sure that the MODULE_PWR_PIN is set to HIGH.
  Nectis.PowerSupplyGrove(true);
  delay(100);

  Serial.println("### Wake up the external flash ROM from deep sleep mode.");
  Mcu.WakeUpFlashRomFromDeepSleepMode();
  delay(100);

  Serial.println("### RTC Initialize.");
  Rtc.Init();
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


  Rtc.SetCurrentTimeToRtc();

  Rtc.SetConstantInterruptByEveryMinute();

  // Put flash ROM into deep sleep mode.
  Serial.println("Put flash ROM into deep sleep mode");
  Mcu.PutFlashRomIntoDeepSleepMode();

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

  Serial.flush();
  delay(1000);

// Set the constant interrupt by every one minute to RTC.
//  Rtc.SetConstantInterruptByEveryMinute();
  Rtc.SetAlarm(RtcAlarmTableTime, (sizeof(RtcAlarmTableTime) / sizeof(char*)), RtcAlarmTableDayofweek, sizeof(uint8_t));

  Rtc.ReadCalender();

  delay(10000);

  Mcu.ConfigForWakingUpFromDeepSleep();
  delay(10);

  // Disable the peripherals.
  Mcu.DisableAllPeripherals();

  // Enter System-Off deep sleep mode.
  Mcu.EnterSystemOffDeepSleepMode();
}

void loop() {

}
