#pragma once

#include "Arduino.h"

class NectisOtaDfu {
    public:
    NectisOtaDfu();
    void ResetRegistry();
    void EnableButtonlessDfu();
    void EnterOtaDfuMode();
};