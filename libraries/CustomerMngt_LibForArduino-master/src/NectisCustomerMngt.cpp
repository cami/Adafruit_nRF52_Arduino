#include <ArduinoJson.h>

#include "nrf_timer.h"
#include "nrf_power.h"

#include <Internal/Debug.h>
#include "NectisCustomerMngt.h"

// Status for Customer Management
const uint8_t STATUS_STOCK            = 0x00;
const uint8_t STATUS_CONTRACT         = 0x01;
const uint8_t STATUS_USE_BEGINNING    = 0x02;
const uint8_t STATUS_CANCEL           = 0x03;


NectisCustomerMngt::NectisCustomerMngt() {

}

void NectisCustomerMngt::Inspection() {
#ifdef NECTIS_DEBUG
  digitalWrite(LED_CONN, HIGH);
#endif

  const char* SKETCH_NAME = "Inspection";
  const char* SKETCH_VERSION = "0.0.1";

  uint8_t STATUS;     // Status for Customer Management
  STATUS = STATUS_STOCK;


  // Sketch
  Serial.printf("SKETCH_NAME    : %s\n", SKETCH_NAME);
  Serial.printf("SKETCH_VERSION : %s\n", SKETCH_VERSION);


  // nRF52840
  // Define the booteloader version here, in order not to get stuck.
#define BOOTLOADER_VERSION_REGISTER     NRF_TIMER2->CC[0]

  char bootloaderVersion[9];
  memset(bootloaderVersion, 0x00, sizeof(bootloaderVersion));
  uint32_t tmpBootloaderVersion = 0;
  tmpBootloaderVersion = BOOTLOADER_VERSION_REGISTER;

  uint8_t ver1 = ((tmpBootloaderVersion >> 16) & 0xff);
  uint8_t ver2 = ((tmpBootloaderVersion >> 8) & 0xff);
  uint8_t ver3 = tmpBootloaderVersion & 0xff;

  sprintf(bootloaderVersion, "%u.%u.%u", ver1, ver2, ver3);
  Serial.printf("Bootloader     : %s", bootloaderVersion);


  // BG96
  char imei[15];
  char imsi[15];

  if(_Nectis.GetIMEI(imei, sizeof(imei) + 1) > 0){
    Serial.printf("IMEI           : %s\n", imei);
  }

  if(_Nectis.GetIMSI(imsi, sizeof(imsi) + 1) > 0){
    Serial.printf("IMSI           : %s\n", imsi);
  }


  // Post data to DynamoDB
  char* postData = NULL;
  const uint32_t postDataSize = 256;

  if (postData == NULL) {
    postData = (char*)malloc((postDataSize * sizeof(char)));
    memset(postData, 0, (postDataSize * sizeof(char)));
  }
  if (postData == NULL) { Serial.println("malloc() error");}

  // Need to free postData.
  sprintf(postData,
          "{\"imsi\":\"%s\", \"imei\":\"%s\", \"bootloader\":\"%s\", \"sketch_name\":\"%s\", \"sketch_ver\":\"%s\", \"status\":\"%u\"}",
          imsi, imei, bootloaderVersion, SKETCH_NAME, SKETCH_VERSION, STATUS);

  // Need to free responseData.
  const char* AWS_MERGE_INFO_URL = "https://57n7s44jk8.execute-api.ap-northeast-1.amazonaws.com:443/prod/merge-customer-n-board-info";
  int status;

  Serial.println("### Post.");
  Serial.printf("URL : %s\n", AWS_MERGE_INFO_URL);
  Serial.printf("Post: %s\n", postData);

  // Post data to DynamoDB
  char responseData[256];
  if (!_Nectis.HttpPost2(AWS_MERGE_INFO_URL, postData, &status, responseData, sizeof(responseData))) {
    Serial.println("### ERROR! ###");
  }

  // ToDO: if the status is not 200, try to HttpPost2() again.
  Serial.print("Status:");
  Serial.println(status);

  Serial.print("Response:");
  Serial.println(responseData);

  char responseJson[256];
  sprintf(responseJson, "%s\n", responseData);

  // StaticJsonDocument<RAM>: RAM should be longer than contentLength.
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, responseJson);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  const char* isComplete = doc["is_complete"];

  if (strcmp(isComplete, "True") == 0) {
    Serial.println("### Prepared for shipping.");
  }

  if (postData != NULL) {
    free(postData);
    postData = NULL;
  }

#ifdef NECTIS_DEBUG
  digitalWrite(LED_CONN, LOW);
#endif
}

void NectisCustomerMngt::PostProductInfoToDynamodb(const char* SKETCH_NAME, const char* SKETCH_VERSION) {
#ifdef NECTIS_DEBUG
  digitalWrite(LED_CONN, HIGH);
#endif

  uint8_t STATUS;     // Status for Customer Management
  STATUS = STATUS_USE_BEGINNING;


  // Sketch
  Serial.print("SKETCH_NAME    : ");
  Serial.println(SKETCH_NAME);
  Serial.print("SKETCH_VERSION : ");
  Serial.println(SKETCH_VERSION);


  // nRF52840
  // Define the booteloader version here, in order not to get stuck.
#define BOOTLOADER_VERSION_REGISTER     NRF_TIMER2->CC[0]

  char bootloaderVersion[9];
  memset(bootloaderVersion, 0x00, sizeof(bootloaderVersion));
  uint32_t tmpBootloaderVersion = 0;
  tmpBootloaderVersion = BOOTLOADER_VERSION_REGISTER;

  uint8_t ver1 = ((tmpBootloaderVersion >> 16) & 0xff);
  uint8_t ver2 = ((tmpBootloaderVersion >> 8) & 0xff);
  uint8_t ver3 = tmpBootloaderVersion & 0xff;

  sprintf(bootloaderVersion, "%u.%u.%u", ver1, ver2, ver3);
  Serial.printf("Bootloader     : %s\n", bootloaderVersion);


  _Nectis.Bg96Begin();
  _Nectis.InitLteM();


  // BG96
  char imei[15];
  char imsi[15];

  if(_Nectis.GetIMEI(imei, sizeof(imei) + 1) > 0){
    Serial.printf("IMEI           : %s\n", imei);
  }

  if(_Nectis.GetIMSI(imsi, sizeof(imsi) + 1) > 0){
    Serial.printf("IMSI           : %s\n", imsi);
  }


  // Post data to DynamoDB
  char* postData = NULL;
  const uint32_t postDataSize = 256;

  if (postData == NULL) {
    postData = (char*)malloc((postDataSize * sizeof(char)));
    memset(postData, 0, (postDataSize * sizeof(char)));
  }
  if (postData == NULL) { Serial.println("malloc() error");}

  // Need to free postData.
  sprintf(postData,
          "{\"imsi\":\"%s\", \"imei\":\"%s\", \"bootloader\":\"%s\", \"sketch_name\":\"%s\", \"sketch_ver\":\"%s\", \"status\":\"%u\"}",
          imsi, imei, bootloaderVersion, SKETCH_NAME, SKETCH_VERSION, STATUS);

  // Need to free responseData.
  const char* AWS_MERGE_INFO_URL = "https://57n7s44jk8.execute-api.ap-northeast-1.amazonaws.com:443/prod/merge-customer-n-board-info";
  int status;

  Serial.println("### Post.");
  Serial.printf("URL : %s\n", AWS_MERGE_INFO_URL);
  Serial.printf("Post: %s\n", postData);

  char responseData[256];
  if (!_Nectis.HttpPost2(AWS_MERGE_INFO_URL, postData, &status, responseData, sizeof(responseData))) {
    Serial.println("### ERROR!: _Nectis.HttpPost2() ###");
  }


  // Enter BG96 into sleep mode with AT command
  _Nectis.Bg96TurnOff();
  // End the Uart between nRF52840 and BG96
  _Nectis.Bg96End();


  char responseJson[256];
  sprintf(responseJson, "%s\n", responseData);

  // StaticJsonDocument<RAM>: RAM should be longer than contentLength.
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, responseJson);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
#ifdef NECTIS_DEBUG
    digitalWrite(LED_CONN, LOW);
#endif
    return;
  }

  const char* isComplete = doc["is_complete"];

  if (strcmp(isComplete, "True") == 0) {
    Serial.println("### Prepared for shipping.");
  }

  if (postData != NULL) {
    free(postData);
    postData = NULL;
  }

#ifdef NECTIS_DEBUG
  digitalWrite(LED_CONN, LOW);
#endif

  Serial.println();
}