#pragma once


class TwoWire;

class NectisGroveWire {
  private:
    TwoWire* _GroveWire;

  public:
    NectisGroveWire();
    ~NectisGroveWire();

    void PowerSupplyGrove(bool on);
};
