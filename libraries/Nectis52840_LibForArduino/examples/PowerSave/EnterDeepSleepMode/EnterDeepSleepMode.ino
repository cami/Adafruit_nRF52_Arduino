#include <SPI.h>
#include "nrf_power.h"
#include <NectisCellular.h>
#include <NectisMcu.h>

NectisCellular Nectis;
NectisMcu Mcu;

// cf. nRF52840 product specification p.69
// Note: Watchdog reset is not available in System OFF.


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
  Mcu.PutFlashRomIntoDeepSleepMode();
  
  // Turn off BG96 casting AT commands.
  Serial.println("Turn off BG96 casting AT commands.");
  Nectis.Bg96TurnOff();
  delay(100);
  // Disable Uart between nRF52840 and BG96.
  Serial.println("Disable Uart between nRF52840 and BG96.");
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
  Mcu.DisableAllPeripherals();
  
  delay(1000);
  
// ToDO: EnterSystemOffDeepSleepMode(), EnterCpuWfiWfeSleep() どちらを先に実行するべきか確認。
// ToDO: RTC_INTRB が LOWになった時に、DeepSleepモードから目覚めるようにする。
// ToDO: GPIO_PIN_CNF_SENSE_Low
  // Enter System-Off deep sleep mode.
  Mcu.EnterSystemOffDeepSleepMode();
  
  // CPU entered WFI/WFE sleep.
  Mcu.EnterCpuWfiWfeSleep();
}

void loop() {

}
