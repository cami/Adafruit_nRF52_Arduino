#include "NectisCellular.h"
#include "NectisMcu.h"
#include "NectisPeripherals.h"
#include "NectisRtc.h"

NectisCellular Nectis;
NectisRtc Rtc;


void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");

  mcu::InitMcu();
  peripherals::WakeUpFlashRomFromDeepSleep();

  Nectis.Begin();
  Nectis.InitLteM();

  delay(10);

  struct tm currentTime;
  char currentTimeStr[64];

  Nectis.GetCurrentTime(&currentTime, true);
  strftime(currentTimeStr, sizeof(currentTimeStr), "%y/%m/%d %H:%M:%S %w", &currentTime);

  Serial.printf("\nNow=%s\n", currentTimeStr);
  delay(10);

  delay(100);
  Nectis.TurnOff();
  Nectis.End();
  delay(100);

  Rtc.Begin();
  Rtc.Init();

  Rtc.ConfigRtc24HourDisplay(); 

  uint8_t calender[7];
  Rtc.ReadCalender(calender);

  uint8_t year = calender[0];
  uint8_t hour = calender[3];

  // year==0 の時は、RTCに時刻がセットされていないので、BG96から取得してセットする。
  if ( (year == 0) | (24 <= hour) ) {
    Rtc.SetCurrentTimeToRtc(&currentTime);
  }

  Rtc.End();
}

void loop() {
  Rtc.Begin();
  Rtc.PrintCalender();
  Rtc.End();

//  Rtc.EndRtc();

  delay(10000);
}