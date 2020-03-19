#pragma once
#include <stdint.h>

class Uart;
class TinyGPSPlus;


typedef struct {
  float lat;
  float lng;
} gps_data_t;

typedef struct {
  int temperature;
  int co2ppm;
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
    gps_data_t* GpsNewData(gps_data_t* gps_data);
    void GpsDeleteData();
    bool GetGpsData();
    void PrintGpsData();

    /*
     * Grove CO2
     */
    co2_data_t* Co2NewData(co2_data_t* co2_data);
    void Co2DeleteData();
    void Co2Calibrate();
    bool GetCo2Data();
    void PrintCo2Data();

    /*
     * Grove RFID
     */
    rfid_data_t* RfidNewData(rfid_data_t* rfid_data);
    void RfidDeleteData();
    bool GetRfidData();
    void PrintRfidData();

  private:
  	uint16_t gpsDataLength = 0;

    static const uint16_t GPS_DATA_SIZE = 128;
    static const uint16_t CO2_DATA_SIZE = 9;
    static const uint16_t RFID_DATA_SIZE = 32;
  	char gpsDataArray[GPS_DATA_SIZE];

    bool IsGpsUpdate();
    const char* ReadGps();
};
