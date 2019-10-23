#include <NectisCellular.h>
#include <NectisMcu.h>
#include <NectisRTC.h>

NectisCellular Nectis;
NectisMcu Mcu;
NectisRTC Rtc;

const char* RtcAlarmTable[] = {
  "00:00", "01:00", "02:00", "03:00", "04:00", "05:00", "06:00", "07:00", "08:00", "09:00", "10:00", "11:00",
  "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00", "21:00", "22:00", "23:00"
};


void InitSketch() {
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

  Serial.println("### Wake up the external flash ROM from deep sleep mode.");
  Mcu.WakeUpFlashRomFromDeepSleepMode();
  delay(100);
}

void setup() {
  InitSketch();

  Rtc.BeginRtc();

  Rtc.Init();

  Rtc.SetAlarm(RtcAlarmTable, (sizeof(RtcAlarmTable) / sizeof(char*)));
}

void loop() {
  Rtc.ReadCalender();

//  Rtc.EndRtc();

  delay(10000);

}