#include "NectisCellularBG96.h"
#include "NectisMcu.h"
#include "NectisPeripherals.h"
#include "NectisRtc.h"

NectisCellularBG96 BG96;
NectisRtc Rtc;


void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.print("");
  Serial.println("--- START ---------------------------------------------------");

  mcu::InitMcu();
  peripherals::WakeUpFlashRomFromDeepSleep();

  BG96.Begin();
  BG96.InitLteM();

  delay(10);

  struct tm currentTime;
  char currentTimeStr[64];

  BG96.GetCurrentTime(&currentTime, true);
  strftime(currentTimeStr, sizeof(currentTimeStr), "%y/%m/%d %H:%M:%S %w", &currentTime);

  Serial.printf("\nNow=%s\n", currentTimeStr);
  delay(10);

  delay(100);
  BG96.TurnOff();
  BG96.End();
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