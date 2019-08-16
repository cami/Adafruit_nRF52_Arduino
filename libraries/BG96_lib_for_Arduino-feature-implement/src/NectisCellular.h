#pragma once

#include "WioCellLibforArduino.h"
#include <IPAddress.h>
#include <string>
#include <string>

#include "Internal/AtSerial.h"
#include "Internal/WioSK6812.h"
#include "WioCellularHttpHeader.h"

#define NECTIS_TCP        (NectisCellular::SOCKET_TCP)
#define NECTIS_UDP        (NectisCellular::SOCKET_UDP)

class NectisCellular {
public:
    enum ErrorCodeType {
        E_OK = 0,
        E_UNKNOWN,
    };

    enum SocketType {
        SOCKET_TCP,
        SOCKET_UDP,
    };

    enum AccessTechnologyType {
        ACCESS_TECHNOLOGY_NONE,
        ACCESS_TECHNOLOGY_LTE_M1,
        ACCESS_TECHNOLOGY_LTE_NB1,
    };

    enum SelectNetworkModeType {
        SELECT_NETWORK_MODE_NONE,
        SELECT_NETWORK_MODE_AUTOMATIC,
        SELECT_NETWORK_MODE_MANUAL_IMSI,
        SELECT_NETWORK_MODE_MANUAL,
    };

private:
    WioCellular _Wio;
    SerialAPI _SerialAPI;
    AtSerial _AtSerial;
    // WioSK6812 _Led;  //TODO
    ErrorCodeType _LastErrorCode;
//    AccessTechnologyType _AccessTechnology;   //TODO
//    SelectNetworkModeType _SelectNetworkMode;     //TODO
//    std::string _SelectNetworkPLMN;   //TODO

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

//    bool IsBusy() const;  //TODO
//    bool IsRespond();     //TODO
//    bool Reset();     //TODO
//    bool TurnOn();        //TODO
//
//    bool HttpSetUrl(const char *url);     //TODO

public:
    NectisCellular();
    ErrorCodeType GetLastError() const;
    void Init();
    void PowerSupplyCellular(bool on);
    void PowerSupplyGrove(bool on);
    // void LedSetRGB(uint8_t red, uint8_t green, uint8_t blue);   // TODO
    // bool TurnOnOrReset();   // TODO
    // bool TurnOff(); //TODO

    int GetIMEI(char *imei, int imeiSize);
    int GetIMSI(char *imsi, int imsiSize);
    int GetICCID(char *iccid, int iccidSize);
    int GetPhoneNumber(char *number, int numberSize);
    // bool GetTime(struct tm *tim);    // TODO

//#if defined NRF52840_XXAA     //TODO
//    void SetAccessTechnology(AccessTechnologyType technology);
//#endif // NRF52840_XXAA
//    void SetSelectNetwork(SelectNetworkModeType mode, const char *plmn = NULL);   //TODO

//    bool WaitForCSRegistration(long timeout = 120000);
//    bool WaitForPSRegistration(long timeout = 120000);
    // bool Activate(const char *accessPointName, const char *userName, const char *password, long waitForRegistTimeout = 120000);   //TODO
    // bool Deactivate();   //TODO

    //bool GetLocation(double* longitude, double* latitude);

//    bool GetDNSAddress(IPAddress *ip1, IPAddress *ip2);
//    bool SetDNSAddress(const IPAddress &ip1);
//    bool SetDNSAddress(const IPAddress &ip1, const IPAddress &ip2);

    int SocketOpen(const char *host, int port, SocketType type);
    bool SocketSend(int connectId, const byte *data, int dataSize);
    bool SocketSend(int connectId, const char *data);
    int SocketReceive(int connectId, byte *data, int dataSize);
    int SocketReceive(int connectId, char *data, int dataSize);
    int SocketReceive(int connectId, byte *data, int dataSize, long timeout);
    int SocketReceive(int connectId, char *data, int dataSize, long timeout);
    bool SocketClose(int connectId);

    int HttpGet(const char *url, char *data, int dataSize);
    int HttpGet(const char *url, char *data, int dataSize, const WioCellularHttpHeader &header);
    bool HttpPost(const char *url, const char *data, int *responseCode);
    bool HttpPost(const char *url, const char *data, int *responseCode, const WioCellularHttpHeader &header);

    // bool SendUSSD(const char *in, char *out, int outSize);   //TODO


    void Bg96Begin();
    void Bg96End();
    bool Bg96TurnOff();
    void InitLteM();
    void SoftReset();

    bool HttpPost2(const char *url, const char *data, int *responseCode, char *recv_data, int recv_dataSize);
    bool HttpPost2(const char *url, const char *data, int *responseCode, char *recv_data, int recv_dataSize , const WioCellularHttpHeader &header);


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