#pragma once

#include <NectisCellular.h>
#include "Wire.h"

class NectisRTC {
private:
  TwoWire _RtcWire;
public:
  NectisRTC();
  void SetRtcTimer(unsigned int second);
  void EnableRtcTimer();
  void WriteToRtcReg8(uint8_t internalAddress, uint8_t data);
  void WriteToRtc(uint8_t* data, int dataSize);

};

