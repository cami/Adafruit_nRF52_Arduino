#pragma once

#include <stdint.h>


class NectisFlashROM {
public:
  NectisFlashROM();

  void FlashRomEnterDeepSleep(void);
  void FlashRomExitDeepSleep(void);

  void FlashRomBegin();
  void FlashRomEraseChip();
  void FlashRomWaitUntilReady();
  void FlashRomWriteSector(uint16_t sector_no, const char* contents, uint16_t contents_size);

public:
  static constexpr uint16_t SECTOR_SIZE = 512;
};

