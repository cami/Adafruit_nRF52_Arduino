#pragma once

#include "FlashROM/NectisFlashROM.h"
#include "RTC/NectisRTC.h"
#include <stdint.h>


class NectisDriver : public NectisFlashROM, public NectisRTC {
public:
  NectisDriver();
  ~NectisDriver();
};
