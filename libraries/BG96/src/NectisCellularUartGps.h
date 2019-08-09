#pragma once

#include "NectisCellularUart.h"
#include "TinyGPS++.h"


class NectisCellularUartGps : public NectisCellularUart {
    private:
    TinyGPSPlus _gps;

    public:
    NectisCellularUartGps();
    const char *GpsRead();
    bool IsGpsLocationUpdate();
    float CalcGpsLatitude();
    float CalcGpsLongitude();
};
