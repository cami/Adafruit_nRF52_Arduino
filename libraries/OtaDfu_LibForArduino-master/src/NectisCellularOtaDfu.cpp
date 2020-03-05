#include "nrf_power.h"

#include <ArduinoJson.h>
#include "Adafruit_SPIFlash.h"

#include <Internal/Debug.h>
#include "NectisCellularOtaDfu.h"

#define DFU_MAGIC_RESET                 0UL
#define DFU_MAGIC_SERIAL_ONLY_RESET     0x4e
#define DFU_MAGIC_UF2_RESET             0x57
#define DFU_MAGIC_OTA_RESET             0xA8
#define DFU_MAGIC_LTEM_RESET            0x64

#define HTTP_USER_AGENT                 "QUECTEL_MODULE"
#define HTTP_CONTENT_TYPE               "application/octet-stream"

const uint16_t SECTOR_SIZE = 512;
const uint16_t WRITE_MAX_SIZE_ONE_TIME = SECTOR_SIZE;

Adafruit_FlashTransport_QSPI _flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
Adafruit_SPIFlash _flash(&_flashTransport);


NectisOtaDfu::NectisOtaDfu()  {

}

void NectisOtaDfu::ResetRegister() {
  nrf_power_gpregret_set(DFU_MAGIC_SERIAL_ONLY_RESET);
}

void NectisOtaDfu::EnableButtonlessDfu() {
}

void NectisOtaDfu::EnterBleDfuMode() {
  nrf_power_gpregret_set(DFU_MAGIC_OTA_RESET);
//  nrf_power_gpregret2_set(0);

  NVIC_SystemReset();
}

void NectisOtaDfu::EnterLtemDfuMode() {
  nrf_power_gpregret_set(DFU_MAGIC_LTEM_RESET);
//  nrf_power_gpregret2_set(0);

  NVIC_SystemReset();
}

void NectisOtaDfu::writeSector(uint16_t sector_no, const char* contents, uint16_t contents_size) {
  uint8_t buf[contents_size];

  for(uint32_t i = 0 ; i < sizeof(buf) ; i++) {
    buf[i] = contents[i];
  }

  int nRet = _flash.writeBuffer(sector_no*SECTOR_SIZE, buf, contents_size);

  _flash.waitUntilReady();

  DEBUG_PRINT(nRet);
  DEBUG_PRINT(" sector_no=");
  DEBUG_PRINT(sector_no);
  DEBUG_PRINTLN(" Write OK");
}

void NectisOtaDfu::ExecuteOtaDfu(const char* sketchName, const char* sketchVersion) {
  // Begin LTE-M communication.
  _Nectis.Bg96Begin();
  _Nectis.InitLteM();

  // BG96
  char imei[15];
  if(_Nectis.GetIMEI(imei, sizeof(imei) + 1) > 0){
    DEBUG_PRINT("IMEI           : ");
    DEBUG_PRINTLN(imei);
  }

  char* postData = NULL;
  const uint32_t postDataSize = 64;

  if (postData == NULL) {
    postData = (char*)malloc((postDataSize * sizeof(char)));
    memset(postData, 0, (postDataSize * sizeof(char)));
  }
  if (postData == NULL) { Serial.println("malloc() error");}

  sprintf(postData, "{\"imei\":\"%s\",\"fw_ver\":\"%s\"}", imei, sketchVersion);

  const char* CHECK_FW_VER_URL = "https://nu2m6p6zqd.execute-api.ap-northeast-1.amazonaws.com:443/prod/ota_dfu";
  int status = 0;

  Serial.println("### Post.");
  Serial.printf("URL : %s\n", CHECK_FW_VER_URL);
  Serial.printf("Post: %s\n", postData);

  char responseData[256];
  if (!_Nectis.HttpPost2(CHECK_FW_VER_URL, postData, &status, responseData, sizeof(responseData))) {
    Serial.println("### ERROR! _Nectis.HttpPost2() ###");
  }

  if (postData != NULL) {
    free(postData);
    postData = NULL;
  }

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

  const char *does_update = doc["does_update"];

  // Enter LTE-M DFU
  if (strcmp(does_update, "yes") == 0) {
    Serial.println("### Start to download the new firmware");

    const int wdtTimeoutSecond = 30 * 60;
    _Mcu.WatchdogTimerInit(wdtTimeoutSecond);

    // Reload the watchdog timer.
    DEBUG_PRINTLN("### Reload the watchdog.");
    _Mcu.ReloadWatchdogTimer();

    const uint16_t FIRMWARE_DOWNLOAD_INTERVAL = 2500;

    DEBUG_PRINTLN("Wake up the external flash ROM from deep sleep mode.");
    _Mcu.WakeUpFlashRomFromDeepSleepMode();

    if (!_flash.begin()) {
      Serial.println("Error, failed to initialize flash chip!");
      while(1) delay(10);
    }

//    Serial.print("JEDEC ID: ");
//    Serial.println(_flash.getJEDECID(), HEX)

    if (!_flash.eraseChip()) {
      Serial.println("Failed to erase chip!");
    }

    _flash.waitUntilReady();
    DEBUG_PRINTLN("Successfully erased chip!");


    const char *doc_newest_fw_ver = doc["newest_fw_ver"];
    char newestFwVer[16];
    memcpy(&newestFwVer[0], doc_newest_fw_ver, sizeof(newestFwVer));
    DEBUG_PRINT("newest_fw_ver: ");
    DEBUG_PRINTLN(newestFwVer);

    uint32_t CONTENT_LENGTH_FW = doc["size"];
    DEBUG_PRINT("CONTENT_LENGTH_FW: ");
    DEBUG_PRINTLN(CONTENT_LENGTH_FW);

    uint32_t RANGE_BYTES = (uint32_t) SECTOR_SIZE;
    uint32_t startRangeByte = 0;
    //    int stopRangeByte = startRangeByte + RANGE_BYTES - 1;
    uint32_t stopRangeByte = 0;

    uint32_t firmwareSize = 0;
    uint16_t sector_number = 1;

    char downloadFwUrl[128];
    sprintf(downloadFwUrl, "http://harvest-files.soracom.io/ota/%s/fw_%s.bin", sketchName, newestFwVer);
    DEBUG_PRINTLN("### Get.");
    DEBUG_PRINT("URL: ");
    DEBUG_PRINTLN(downloadFwUrl);


    digitalWrite(LED_RED, HIGH);
    for (uint32_t i = 0; i < CONTENT_LENGTH_FW; i += RANGE_BYTES) {
      uint16_t writeLength = RANGE_BYTES < (CONTENT_LENGTH_FW - i) ? RANGE_BYTES : (CONTENT_LENGTH_FW - i);
      startRangeByte = i;
      stopRangeByte = startRangeByte + writeLength - 1;

      char range[32];
      sprintf(range, "bytes=%lu-%lu", startRangeByte, stopRangeByte);

      header["Accept"] = "*/*";
      header["User-Agent"] = HTTP_USER_AGENT;
      header["Connection"] = "Keep-Alive";
      header["Content-Type"] = HTTP_CONTENT_TYPE;
      header["Range"] = range;

      char firmwareFile[writeLength];
      memset(firmwareFile, 0x00, writeLength);

      int contentLength = 0;
      while (contentLength <= 0) {
        contentLength = _Nectis.HttpGet(downloadFwUrl, firmwareFile, RANGE_BYTES, header);
      }

      if(contentLength > 0) {
        DEBUG_PRINTLN(firmwareFile);
        delay(10);

        DEBUG_PRINTLN("Save the downloaded firmware to the flash ROM");
        DEBUG_PRINT("sector_number: ");
        DEBUG_PRINTLN(sector_number);
        DEBUG_PRINT("write_length : ");
        DEBUG_PRINTLN(writeLength);

        writeSector(sector_number, firmwareFile, writeLength);

        sector_number++;
        firmwareSize += contentLength;
\
        DEBUG_PRINT("writeLength   : ");
        DEBUG_PRINTLN(writeLength);
        DEBUG_PRINT("contentLength : ");
        DEBUG_PRINTLN(contentLength);
        DEBUG_PRINT("firmwareSize  : ");
        DEBUG_PRINTLN(firmwareSize);
      }

      // Without (Even with) this delay, there is a chance that the network between the MCU and SORACOM is disconeccted by SORACOM.
      delay(FIRMWARE_DOWNLOAD_INTERVAL);
    }

    sector_number = 0;
    char FIRMWARE_SIZE_BIN[9] = {0};

    sprintf(FIRMWARE_SIZE_BIN, "%lu", firmwareSize);
    DEBUG_PRINT("FIRMWARE_SIZE_BIN: ");
    DEBUG_PRINTLN(FIRMWARE_SIZE_BIN);

    writeSector(sector_number, &FIRMWARE_SIZE_BIN[0], sizeof(FIRMWARE_SIZE_BIN));
    DEBUG_PRINTLN("FIRMWARE_SIZE saved in the Flash ROM at Sector0");

    digitalWrite(LED_RED, LOW);


    DEBUG_PRINTLN("### New firmware has successfully written to the flash ROM");

    // Enter BG96 into sleep mode with AT command
    _Nectis.Bg96TurnOff();
    // End the Uart between nRF52840 and BG96
    _Nectis.Bg96End();


#ifdef NECTIS_DEBUG
    digitalWrite(LED_BLUE, LOW);   digitalWrite(LED_RED, LOW);

    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_RED, LOW);
      delay(500);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_RED, HIGH);
      delay(500);
    }

    digitalWrite(LED_BLUE, LOW);   digitalWrite(LED_RED, LOW);
#endif


    DEBUG_PRINTLN("### Successfully downloaded the new firmware.");
    Serial.println("### Enter LTE-M DFU mode.");
    delay(100);

    EnterLtemDfuMode();
  } else {
    // Enter BG96 into sleep mode with AT command
    _Nectis.Bg96TurnOff();
    // End the Uart between nRF52840 and BG96
    _Nectis.Bg96End();

    Serial.println("### No need to update the firmware.");
  }

  Serial.println();
}

