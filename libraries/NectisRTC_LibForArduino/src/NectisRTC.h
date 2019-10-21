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
  void Write(uint8_t slaveAddress, const uint8_t* data, int dataSize);
  int Read(uint8_t slaveAddress, uint8_t* data, int dataSize);

  void WriteReg8(uint8_t slaveAddress, uint8_t reg, uint8_t data);
  int ReadReg8(uint8_t slaveAddress, uint8_t reg, uint8_t* data);
};

