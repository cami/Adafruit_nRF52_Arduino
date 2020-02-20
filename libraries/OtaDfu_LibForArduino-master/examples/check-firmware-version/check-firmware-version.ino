/*
 * Lte-M OTA-DFU
 *  Post firmware version to the AWS lambda and get whether the firmware update is needed.
 */

// If you HTTP post directly to AWS labmda, IMEI of BG96 module does not added to the HTTP header automatically.
// Therefore, please post the json consists of firmwareVersion and IMEI.

#include <NectisCellular.h>
#include <ArduinoJson.h>

#define CHK_FW_VER_URL          "https://3t7a0j8tu5.execute-api.us-east-1.amazonaws.com:443/dev/chk_fw_ver"
//#define CHK_FW_VER_URL          "http://beam.soracom.io:8888/ChkFwVer"
const char* firmwareVersion = "0.0.0";

NectisCellular Nectis;

char imei[32];
char postData[64];
int status;
char responseData[256];


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
  
  Nectis.Bg96Begin();
  Nectis.InitLteM();
  
  Serial.println("### Setup completed.");

  delay(1000);

  if(Nectis.GetIMEI(imei, sizeof(imei)) > 0){
    Serial.print("imei=");
    Serial.println(imei);
  }

  sprintf(postData, "{\"imei\":\"%s\",\"fw_ver\":\"%s\"}", imei,firmwareVersion);
  Serial.println("### Post.");
  Serial.print("Post:");
  Serial.print(postData);
  Serial.println("");
  
  if (!Nectis.HttpPost2(CHK_FW_VER_URL, postData, &status, responseData, sizeof(responseData))) {
    Serial.println("### ERROR! ###");
  }

  // ToDO: if the status is not 200, try to HttpPost2() again.
  Serial.print("Status:");
  Serial.println(status);

/* responseData format.
  responseboby = {
    "does_update":"yes",
    "newest_fw_ver":"0.0.2",
    "size":"34633"
  }
  responseboby = {
    "does_update":"no",
    "newest_fw_ver":"0.0.1",
  }
*/
  Serial.print("Response:");
  Serial.println(responseData);
  
  // StaticJsonDocument<RAM>: RAM should be longer than contentLength.
  StaticJsonDocument<128> doc;
  char responseJson[128];
  sprintf(responseJson, "%s\n", responseData);

  DeserializationError error = deserializeJson(doc, responseJson);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  
  const char* update = doc["does_update"];
  const char* newestFwVer = doc["newest_fw_ver"];

  Serial.printf("update:%s\n", update);
  Serial.printf("newestFwVer:%s\n", newestFwVer);
  Serial.println(update);

  if (!strcmp(update, "yes")) {
    const char* size = doc["size"];
    Serial.printf("size:%s\n", size);
  }

  // Enter BG96 into sleep mode with AT command
  Nectis.Bg96TurnOff();
  // End the Uart between nRF52840 and BG96
  Nectis.Bg96End();
}

void loop() {
}
