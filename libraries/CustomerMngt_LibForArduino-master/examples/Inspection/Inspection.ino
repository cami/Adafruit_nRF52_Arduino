// For Board_Info
#include <NectisCellular.h>
#include "NectisCustomerMngt.h"   // For Customer Management

NectisCellular Nectis;
NectisCustomerMngt Mngt;          // For Customer Management


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
  
  // Begin LTE-M communication, if needed.
  Nectis.Bg96Begin();
  Nectis.InitLteM();

/*
 * Your code here.
 */

  Serial.println("Inspection()");     // For Inspection
  Mngt.Inspection();                  // For Inspection

  // Enter BG96 into sleep mode with AT command
  Nectis.Bg96TurnOff();
  // End the Uart between nRF52840 and BG96
  Nectis.Bg96End();
}

void loop() {
  __NOP();
}
