#include "NectisCellular.h"
#include "NectisMcu.h"
#include "NectisUtils.h"
#include "NectisPeripherals.h"
#include "NectisRtc.h"

NectisCellular Nectis;
NectisRtc Rtc;

const char* RtcAlarmTable[] = {
  "00:00", "01:00", "02:00", "03:00", "04:00", "05:00", "06:00", "07:00", "08:00", "09:00", "10:00", "11:00",
  "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00", "21:00", "22:00", "23:00"
};
const uint8_t tableDayofweek = 1;



void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");

  mcu::InitMcu();

  Rtc.Begin();
  Rtc.Init();

  Rtc.ConfigRtc24HourDisplay(); 

  Rtc.SetAlarm(&RtcAlarmTable[0], (uint16_t)(sizeof(RtcAlarmTable) / sizeof(char*)), tableDayofweek);
}

void loop() {
  Rtc.PrintCalender();

  delay(10000);
}