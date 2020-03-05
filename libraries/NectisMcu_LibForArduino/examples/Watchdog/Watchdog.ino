#include "NectisMcu.h"
#include "Stopwatch.h"

#define PIN_FEEDING_WDT     GROVE_ANALOG_1_1

Stopwatch sw;
constexpr uint32_t wdtTimeoutSec = 30;
uint16_t elapsedSeconds;


void InitPins() {
  pinMode(PIN_FEEDING_WDT, INPUT);
}

void InitTimer() {
  sw.Restart();
  elapsedSeconds = 0;
}

void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");

  mcu::InitMcu();
  InitPins();

  // Initialize the watchdog timer.
  mcu::WatchdogTimerInit(wdtTimeoutSec);
  
  InitTimer();

  Serial.println("### Setup complete.");
}

void loop() {
  mcu::TurnOnOffGreenLed(false);

  if ( (uint16_t)(sw.ElapsedMilliseconds() / 1000) - elapsedSeconds == 1 ) {
    elapsedSeconds++;
    Serial.printf("Elapsedtime[s]=%u\n", elapsedSeconds);
  }

  uint8_t buttonState = digitalRead(PIN_FEEDING_WDT);
  bool isRequestedToFeed = (buttonState == 1);

  // Reload the watchdog timer.
  if (isRequestedToFeed) {
    mcu::TurnOnOffGreenLed(true);

    // 連続でボタンが押下されたと認識されないようにするため
    delay(250);

    mcu::ReloadWatchdogTimer();
    
    mcu::TurnOnOffGreenLed(false);

    InitTimer();
  }
}
