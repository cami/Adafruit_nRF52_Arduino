#pragma once
#include <stdint.h>

class Uart;
class TinyGPSPlus;


typedef struct {
  float lat;
  float lng;
} gps_data_t;

typedef struct {
  uint32_t co2;
} co2_data_t;

typedef struct {
  char* rfid;
} rfid_data_t;


class NectisGroveUart {
  private:
    Uart* _GroveUart;
    TinyGPSPlus* _gps;

  private:
    gps_data_t* _gps_data;
    co2_data_t* _co2_data;
    rfid_data_t* _rfid_data;

  public:
    NectisGroveUart();
    ~NectisGroveUart();

    /*
     * Power on.
     */
    void PowerSupplyGrove(bool on);

    void Begin(unsigned long baudRate);
    void End();

    /*
     * Grove GPS
     */
    gps_data_t* GpsSetup(gps_data_t* gps_data);
    bool IsGpsLocationUpdate();
    bool GetGpsData();
    void PrintGpsData();

    /*
     * Grove CO2
     */
    co2_data_t* Co2Setup(co2_data_t* co2_data);
    void Co2Calibration();
    bool GetCo2Data();
    void PrintCo2Data();

    /*
     * Grove RFID
     */
    rfid_data_t* RfidSetup(rfid_data_t* rfid_data);
    bool GetRfidData();
    void PrintRfidData();
};
