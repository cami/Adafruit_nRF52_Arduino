#pragma once

#include <NectisCellular.h>


class NectisCustomerMngt {
private:
  NectisCellular _Nectis;

public:
  NectisCustomerMngt();
  void Inspection();
  void PostProductInfoToDynamodb(const char* SKETCH_NAME, const char* SKETCH_VERSION);
};


