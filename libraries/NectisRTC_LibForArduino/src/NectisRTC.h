#pragma once

#include "Wire.h"

#include <NectisCellular.h>

class NectisRTC {
private:
  TwoWire _RtcWire;
  NectisCellular _Nectis;

  bool isCurrentTimeSet;
public:
  NectisRTC();

  uint16_t ConvertBcdToDecimal(uint16_t bcd);
  uint16_t ConvertDecimalToBcd(uint16_t decimal);

  void GetCurrentTime(struct tm *tim, bool jst);

  void BeginRtc();
  void EndRtc();
  void Init();
  void ConfigRtc24HourDisplay();

  void SetCurrentTimeToRtc();
  void ReadCalender();
  void SetAlarm(const char* table[], uint16_t tableSize);

  void EnableRtcTimer(uint8_t slaveAddress);
  void EnableRtcAlarm(uint8_t slaveAddress);

  void Write(uint8_t slaveAddress, const uint8_t* data, int dataSize);
  int Read(uint8_t slaveAddress, const uint8_t* slaveRegister, uint8_t* data, int dataSize);

  void WriteReg8(uint8_t slaveAddress, uint8_t reg, uint8_t data);
  int ReadReg8(uint8_t slaveAddress, uint8_t reg, uint8_t* data);
};

