#pragma once

#include "WioCellLibforArduino.h"

class NectisCellularUart {
    private:
    WioCellular _Wio;
    SerialAPI _SerialAPI;
    AtSerial _AtSerial;
    
    protected:
    Uart *_GroveUartSerial;
    
    public:
    NectisCellularUart();
    void GroveUartSetup();
    void GroveUartBegin();
    void GroveUartEnd();
    const char *RfidRead();
    bool IsCo2Read();
    uint16_t Co2Read();
    void Co2Calibration();
};