#pragma once
#include <stdint.h>

class Uart;


/*
 * Grove GPS から送られてくる生データ
 * data=$GPRMC,000001.799,V,,,,,0.00,0.00,060180,,,N*44
 * data=$GPGGA,000002.799,,,,,0,0,,,M,,M,,*4D
 * data=$GPGSA,A,1,,,,,,,,,,,,,,,*1E
 * data=$GPGSV,1,1,00*79
 */
typedef struct {
  uint8_t numSatellites;
  double lat;
  double lng;
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t centisecond;
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
    const char* ReadGps();

  private:
    static const uint16_t GPS_DATA_SIZE = 128;
    static const uint16_t CO2_DATA_SIZE = 9;
    static const uint16_t RFID_DATA_SIZE = 32;

		uint8_t numSatellites;
    bool isLocationUpdated = false;
		double lat;
		double lng;
		uint16_t year;
		uint8_t month;
		uint8_t day;
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
		uint8_t centisecond;

  	uint16_t gpsDataLength = 0;
  	char gpsDataArray[GPS_DATA_SIZE];
};
