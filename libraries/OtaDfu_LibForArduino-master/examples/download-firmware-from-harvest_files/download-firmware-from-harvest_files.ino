/*
 * Lte-M OTA-DFU
 *  Download the firmware from SORACOM Harvest files.
 */

#include <NectisCellular.h>
#include <NectisCellularHttpHeader.h>

#define HTTP_USER_AGENT         "QUECTEL_MODULE"

#define DOWNLOAD_FW_HOST        "http://harvest-files.soracom.io"
#define HARVEST_FILES_PATH      "ota-dfu"
#define CONTENT_LENGTH          34633
#define HTTP_CONTENT_TYPE       "application/zip"

// The following values are got when you send HTTP post to AWS lambda and a firmware update is available.
char* firmwareVersion = "0.0.1";
char* filenameExtension = "zip";

NectisCellular Nectis;
NectisCellularHttpHeader header;


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


  char downloadFwUrl[256];
  const int RANGE_BYTES = 256;
  int requestTimes = (int)(ceil(((double)CONTENT_LENGTH / (double)RANGE_BYTES)));
  int startByte = 0;
  int stopByte = startByte + RANGE_BYTES - 1;

//  if (!strcmp(update, "y")) {
    uint8_t sizeOfFirmwareFile = RANGE_BYTES + 1;
    char firmwareFile[sizeOfFirmwareFile];

    Serial.println(requestTimes);

    for (int i = 0; i < requestTimes; i++) {
      sprintf(downloadFwUrl, "%s/%s/fw_ver_%s.%s", DOWNLOAD_FW_HOST, HARVEST_FILES_PATH, firmwareVersion, filenameExtension);

      char range[32];
      sprintf(range, "bytes=%d-%d", startByte, stopByte);

      header["Accept"] = "*/*";
      header["User-Agent"] = HTTP_USER_AGENT;
      header["Connection"] = "Keep-Alive";
      header["Content-Type"] = HTTP_CONTENT_TYPE;
      header["Range"] = range;

      Serial.printf("GET %s\n", downloadFwUrl);

      int contentLength = Nectis.HttpGet(downloadFwUrl, firmwareFile, RANGE_BYTES, header);

      Serial.printf("contentLength: %d\n", contentLength);

      if(contentLength > 0) {
        firmwareFile[RANGE_BYTES] = 0x00;
        Serial.println(firmwareFile);
        delay(10);
      }

      startByte += RANGE_BYTES;
      stopByte += RANGE_BYTES;

      delay(10);
    }
//  }

  // Enter BG96 into sleep mode with AT command
  Nectis.Bg96TurnOff();
  // End the Uart between nRF52840 and BG96
  Nectis.Bg96End();
}

void loop() {
}
