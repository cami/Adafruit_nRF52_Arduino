#pragma once


class SPIClass;

class NectisGroveSPI {
  private:
    SPIClass* _GroveSpi;

  public:
    NectisGroveSPI(SPIClass* groveSpi);
    ~NectisGroveSPI();

    void PowerSupplyGrove(bool on);
};
