// For Board_Info
#include <NectisCellular.h>
#include "NectisCustomerMngt.h"   // For Customer Management

#include "NectisCellularOtaDfu.h"

NectisCellular Nectis;
NectisCustomerMngt Mngt;    // For Customer Management


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
  
/*
 * Your code here.
 */

/*
19:23:23.999 -> ### Post.
19:23:23.999 -> Post:{"imei":"866425033400534", "imsi":"440525060023515"}
19:23:23.999 -> Post https://57n7s44jk8.execute-api.ap-northeast-1.amazonaws.com:443/prod/merge-customer-n-board-info
19:23:27.372 -> contentLength=824
19:23:27.372 -> Status:200
19:23:27.372 -> Response:f
19:23:27.372 -> deserializeJson() failed: InvalidInput
 */

  const char* SKETCH_NAME = "Shipping";
  const char* SKETCH_VERSION = "0.0.1";

  Serial.println("### Shipping() Start.");    // For Shipping
  Mngt.PostProductInfoToDynamodb(SKETCH_NAME, SKETCH_VERSION);    // For Shipping
  Serial.println("### Shipping() End.");    // For Shipping

}

void loop() {
  __NOP();
}
