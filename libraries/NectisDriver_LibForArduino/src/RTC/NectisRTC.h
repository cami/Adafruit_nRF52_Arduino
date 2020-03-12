#pragma once

#include <stdint.h>


class TwoWire;

class NectisRTC {
private:
  TwoWire* _RtcWire;

private:
  bool isCurrentTimeSet;

  void Write(uint8_t slaveAddress, const uint8_t* data, int dataSize);
  int Read(uint8_t slaveAddress, const uint8_t* slaveRegister, uint8_t* data, int dataSize);
  void WriteReg8(uint8_t slaveAddress, uint8_t reg, uint8_t data);
  int ReadReg8(uint8_t slaveAddress, uint8_t reg, uint8_t* data);

  uint16_t ConvertBcdToDecimal(uint16_t bcd);
  uint16_t ConvertDecimalToBcd(uint16_t decimal);

public:
  NectisRTC();

  void RtcBegin();
  void RtcEnd();
  void RtcInit();

  void Rtc24HourDisplay();
  void RtcSetCurrentTime(struct tm *currentTime);
  void RtcPrintCalender();
  void RtcReadCalender(uint8_t calender[7]);

  void RtcSetAlarm(const char* tableTime[], uint16_t tableTimeSize, const uint8_t tableDayofweek);
  void RtcEnableAlarm(uint8_t slaveAddress);
  void RtcSetConstantInterruptByEveryMinute();
  void RtcSetConstantInterruptByEveryHour();
};

