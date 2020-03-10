#pragma once


class TwoWire;

class NectisGroveWire {
  private:
    TwoWire* _GroveWire;

  public:
    NectisGroveWire(TwoWire* groveWire);
    ~NectisGroveWire();

    void PowerSupplyGrove(bool on);
};
