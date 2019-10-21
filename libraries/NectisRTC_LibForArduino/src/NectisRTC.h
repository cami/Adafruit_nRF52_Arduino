#pragma once

#include "Wire.h"

#include <NectisCellular.h>

class NectisRTC {
private:
  TwoWire _RtcWire;
public:
  NectisRTC();
  void InitRtc();
  void ReadCalender();
//  void SetRtcTimerTime(unsigned int second, unsigned int minute, unsigned int hour);
//  void SetRtcTimerDayofweek(unsigned int dayofweek);
//  void SetRtcTimerDay(unsigned int day);
//  void EnableRtcTimer();
//  void EnableRtcAlarm();
//  void ReadSetTimer();
  void WriteToRtcReg8(uint8_t internalAddress, uint8_t data);
  void ReadFromRtcReg8(uint8_t internalAddress, uint8_t* data);
  void WriteToRtc(uint8_t* data, int dataSize);
  void ReadFromRtc(uint8_t internalAddress, uint8_t* data, int dataSize);
};

