#pragma once

#include "WioCellLibforArduino.h"
#include "Internal/AtSerial.h"

class NectisCellular {
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
    NectisCellular();
    ErrorCodeType GetLastError() const;
    void Init();
    void PowerSupplyCellular(bool on);
    void PowerSupplyGrove(bool on);
    void Bg96Begin();
    void Bg96End();
    bool Bg96TurnOff();
    void InitLteM();
    void SoftReset();
    
    int GetReceivedSignalStrength();
    int GetReceivedSignalStrengthIndicator();
    bool IsTimeGot(struct tm *tim);
    void GetCurrentTime(struct tm *tim);
    
    float ReadVusb();
    float ReadVbat(void);
    float mvToPercent(float mvolts);
    
    void PwmSetup(int pin, uint8_t flash_interval);
    void PwmBegin();
    void PwmWritePin(int pin);
    void PwmStop();
    void PwmActivate(int pin, uint8_t flash_interval);
    
    char* ConvertDecimalToHex(unsigned long int const decimal, int byte_size);
    unsigned int GetDataDigits(unsigned int data);
    char* ConvertIntoBinary(char* PostDataBinary, uint8_t data, unsigned int data_length);
    char* ConvertIntoBinary(char* PostDataBinary, uint16_t data, unsigned int data_length);
    char* ConvertIntoBinary(char* PostDataBinary, uint32_t data, unsigned int data_length);
    char* ConvertIntoBinary(char* PostDataBinary, int data, unsigned int data_length);
    
    void PostDataViaHttp(char *post_data);
    void PostDataViaUdp(char *post_data);
    void PostDataViaUdp(char *post_data, int data_length);
};