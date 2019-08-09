#pragma once

#include <Uart.h>
#include "Internal/AtSerial.h"
#include "WioCellular.h"
#include "NectisCellularConfig.h"
#include "NectisCellularCastAtCommands.h"
#include "NectisCellular.h"
#include <string.h>

class NectisCellularCastAtCommands {
    public:
    enum ErrorCodeType {
        E_OK = 0,
        E_UNKNOWN,
    };
    
    private:
    WioCellular _Wio;
    SerialAPI _SerialAPI;
    AtSerial _AtSerial;
    ErrorCodeType _LastErrorCode;
    
    private:
    bool ReturnOk(bool value) {
        _LastErrorCode = E_OK;
        return value;
    }
    int ReturnOk(int value) {
        _LastErrorCode = E_OK;
        return value;
    }
    bool ReturnError(int lineNumber, bool value, ErrorCodeType errorCode);
    int ReturnError(int lineNumber, int value, ErrorCodeType errorCode);
    
    public:
    NectisCellularCastAtCommands();
    ErrorCodeType GetLastError() const;
    void CastAllCommands();
    void TurnOnBg96Gps();
    void TurnOffBg96Gps();
    void AcquireBg96Gps();
};