#include <NectisCellular.h>
#include <NectisMcu.h>

#define PIN_FEEDING_WDT     GROVE_ANALOG_1_1

bool isWatchdogFed = false;
const int wdtTimeoutSec = 5;

NectisCellular Nectis;
NectisMcu Mcu;


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
  
  Nectis.Bg96Begin();
  Nectis.InitLteM();
  delay(100);
  Serial.println("### Setup complete.");
  
  Serial.println("Watchdog timer Initialize.");
  pinMode(PIN_FEEDING_WDT, INPUT);
  pinMode(LED_BLUE, OUTPUT);
  delay(100);
  
  // Initialize the watchdog timer.
  Serial.printf("Watchdog timer has set to %d seconds.\n", wdtTimeoutSec);
  Serial.printf("Please feed the watchdog in every %d seconds.\n", wdtTimeoutSec);
  Mcu.WatchdogTimerInit(wdtTimeoutSec);
}

void loop() {
  digitalWrite(LED_BLUE, LOW);
  uint8_t buttonState = digitalRead(PIN_FEEDING_WDT);
  
  if (buttonState == 1) {
    Serial.println(buttonState);
    isWatchdogFed = true;
  }
  
  // Reload the watchdog timer.
  if (isWatchdogFed) {
    Serial.println("Reload the watchdog.");
    Mcu.ReloadWatchdogTimer();
    isWatchdogFed = false;
    
    digitalWrite(LED_BLUE, HIGH);
    delay(100);
    digitalWrite(LED_BLUE, LOW);
    delay(1000/60);
  }
}
