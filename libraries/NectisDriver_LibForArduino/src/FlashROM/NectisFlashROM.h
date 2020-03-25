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

  void FlashRomPrintJedecId();
  uint32_t FlashRomGetSize();

  void FlashRomReadSector(uint16_t sector_no, uint8_t *buf, uint8_t contents_size);
  void FlashRomWriteSector(uint16_t sector_no, const char* contents, uint16_t contents_size);
  void FlashRomDumpSector(uint16_t sector_no);

public:
  static constexpr uint16_t SECTOR_SIZE = 512;
};

