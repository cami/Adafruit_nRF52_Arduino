#pragma once
#include "Wire.h"


class NectisRtc {
private:
  TwoWire _RtcWire;
  bool isCurrentTimeSet;

  void Write(uint8_t slaveAddress, const uint8_t* data, int dataSize);
  int Read(uint8_t slaveAddress, const uint8_t* slaveRegister, uint8_t* data, int dataSize);
  void WriteReg8(uint8_t slaveAddress, uint8_t reg, uint8_t data);
  int ReadReg8(uint8_t slaveAddress, uint8_t reg, uint8_t* data);

  uint16_t ConvertBcdToDecimal(uint16_t bcd);
  uint16_t ConvertDecimalToBcd(uint16_t decimal);

public:
  NectisRtc();

  void Begin();
  void End();
  void Init();

  void ConfigRtc24HourDisplay();
  void SetCurrentTimeToRtc(struct tm *currentTime);
  void PrintCalender();
  void ReadCalender(uint8_t calender[7]);

  void SetAlarm(const char* tableTime[], uint16_t tableTimeSize, const uint8_t tableDayofweek);
  void SetConstantInterruptByEveryMinute();
  void SetConstantInterruptByEveryHour();
  void EnableRtcAlarm(uint8_t slaveAddress);
};

