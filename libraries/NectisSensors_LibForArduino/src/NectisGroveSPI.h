#pragma once


class SPIClass;

class NectisGroveSPI {
  private:
    SPIClass* _GroveSpi;

  public:
    NectisGroveSPI();
    ~NectisGroveSPI();

    void PowerSupplyGrove(bool on);
};
