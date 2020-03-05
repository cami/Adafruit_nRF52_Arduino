// For Board_Info and Customer_Info
// Execute Inspections(), Shipping()


#include <NectisCellular.h>
#include "NectisCustomerMngt.h"   // For Customer Management

#define HTTP_CONTENT_TYPE               "application/json"
#define HTTP_USER_AGENT                 "QUECTEL_MODULE"

NectisCellular Nectis;
CustomerManagement Mngt;    // For Customer Management


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

#ifdef NECTIS_DEBUG
  pinMode(LED_CONN, OUTPUT);      // Blue
  pinMode(LED_BUILTIN, OUTPUT);   // Red
#endif
  
  Nectis.Bg96Begin();
  Nectis.InitLteM();
  
  Serial.println("### Setup completed.");
  
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_CONN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_CONN, HIGH);
    delay(500);
  }
  
  digitalWrite(LED_CONN, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Inspection()");    // For Inspection
  Mngt.Inspection();    // For Inspection
  
  
  Serial.println("Shipping()");     // For Shipping
  Mngt.Shiping();     // For Shipping
  
  
  delay(1000);
  
  // Enter BG96 into sleep mode with AT command
  Nectis.Bg96TurnOff();
  // End the Uart between nRF52840 and BG96
  Nectis.Bg96End();
}

void loop() {
  __NOP();
}
