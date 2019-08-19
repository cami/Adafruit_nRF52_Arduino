#include <NectisCellular.h>

#define PIN_WDT GROVE_ANALOG_1_1

bool isWatchdogFed = false;

NectisCellular Nectis;


void setup() {
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

  Nectis.Bg96Begin();
  Nectis.InitLteM();
  delay(100);
  Serial.println("### Setup complete.");

  Serial.println("Watchdog timer Initialize.");
  pinMode(PIN_WDT, INPUT);
  pinMode(LED_BLUE, OUTPUT);
  delay(100);

//  // Initialize the watchdog timer.
  NRF_WDT->CONFIG = (WDT_CONFIG_HALT_Pause << WDT_CONFIG_HALT_Pos) | ( WDT_CONFIG_SLEEP_Pause << WDT_CONFIG_SLEEP_Pos);   //Configure Watchdog. a) Pause watchdog while the CPU is halted by the debugger.  b) Keep the watchdog running while the CPU is sleeping.
  NRF_WDT->CRV = 5*32768;             // timeout [s] = ( CRV + 1 ) / 32768
  NRF_WDT->RREN |= WDT_RREN_RR0_Msk;  //Enable reload register 0
  NRF_WDT->TASKS_START = 1;           //Start the Watchdog timer
}

void loop() {
  digitalWrite(LED_BLUE, LOW);
  uint8_t buttonState = digitalRead(PIN_WDT);

  if (buttonState == 1) {
    Serial.println(buttonState);
    isWatchdogFed = true;
  }

  if (isWatchdogFed) {
    NRF_WDT->RR[0] = WDT_RR_RR_Reload;
    NRF_WDT->TASKS_START = 1;

    digitalWrite(LED_BLUE, HIGH);
    delay(100);
    digitalWrite(LED_BLUE, LOW);
    isWatchdogFed = false;
    delay(1000/60);
  }
}
