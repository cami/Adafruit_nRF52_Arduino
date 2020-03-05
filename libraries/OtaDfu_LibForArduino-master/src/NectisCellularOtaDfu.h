#pragma once

#include <NectisCellular.h>
#include <NectisMcu.h>
#include <NectisCellularHttpHeader.h>


class NectisOtaDfu {
private:
  NectisCellular _Nectis;
  NectisMcu _Mcu;
  NectisCellularHttpHeader header;

public:
  NectisOtaDfu();
  void ResetRegister();
  void EnableButtonlessDfu();
  void EnterBleDfuMode();
  void EnterLtemDfuMode();

  void writeSector(uint16_t sector_no, const char* contents, uint16_t contents_size);
  void ExecuteOtaDfu(const char* sketchName, const char* sketchVersion);
};