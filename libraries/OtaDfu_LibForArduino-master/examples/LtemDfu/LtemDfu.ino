/*
 * Lte-M OTA-DFU
 *  Post firmware version to the AWS lambda and get whether the firmware update is needed.
 *  If needed, download the newest firmware from SORACOM Harvest files.
 */

// If you HTTP post directly to AWS labmda, IMEI of BG96 module does not added to the HTTP header automatically.
// Therefore, please post the json consists of SKETCH_VERSION and IMEI.

#include <NectisCellular.h>
#include <NectisMcu.h>

#include <NectisCustomerMngt.h>
#include <NectisCellularOtaDfu.h>

// ToDO: 初回起動時、製品登録
// スケッチの初回書き込み時(動作確認時)は、製品情報をDynamoDB(Customer_Management)に登録する必要がるので、コメントを外す。
// お客様の元に出荷する場合は、コメントアウトする。
#define SHIPPING

// ToDO: OTA-DFU
// SKETCH_NAMEは、DynamoDB(Customer_Info)に登録されている tag_name_for_company とスケッチ名を連結させたものを使用する。
// 日本語は使用できないので、アルファベットに直し、必要に応じて整形する。("&"、","、"."は使用しない。)
// (SKETCH_NAMEでは、お客様とそのお客様が申し込んだプランが一意に特定できれば良いので、適宜修正してください。)
// 例) tag_name_for_company = "CAMI&Co._IoT事業部", plan = "室内環境測定", スケッチ名 = "Grove_Environment.ino"
// 例) SKETCH_NAME = "CAMIandCo_environment"
const char* SKETCH_NAME = "OTA-DFU_Test";
const char* SKETCH_VERSION = "0.0.1";

NectisCellular Nectis;
NectisMcu Mcu;
NectisOtaDfu OtaDfu;
NectisCustomerMngt Mngt;


// ToDO: 100kBまでのDFUに対応できる。
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

  Serial.println("### Wake up the external flash ROM from deep sleep mode.");
  Mcu.WakeUpFlashRomFromDeepSleepMode();
  delay(100);
  
  // ToDO: OTA-DFU (もし、BG96の初期化を行っていなければ、必要。)
  Nectis.Bg96Begin();
  Nectis.InitLteM();

  
  // ToDO: 初回起動時、製品登録
  // 製品情報（IMEI, IMSI, Sketch）をDynamoDBに登録する。
#ifdef SHIPPING
  Mngt.PostProductInfoToDynamodb(SKETCH_NAME, SKETCH_VERSION);
#endif  // SHIPPING

  Serial.println("### Setup completed.");

  delay(10000);

  Serial.println("### Start OTA-DFU.");
  
  // ToDO: OTA-DFU
  OtaDfu.ExecuteOtaDfu(SKETCH_NAME, SKETCH_VERSION);
}

void loop() {
}
