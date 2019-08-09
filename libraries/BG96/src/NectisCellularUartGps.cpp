#include "NectisCellularUartGps.h"

#define GROVE_UART_OVERFLOW_STRING "OVERFLOW"

char GroveGpsData[64];
int GroveGpsDataLength;

NectisCellularUartGps::NectisCellularUartGps() {
}

const char *NectisCellularUartGps::GpsRead() {
    while (_GroveUartSerial->available()) {
        char data = _GroveUartSerial->read();
        
        _gps.encode(data);
        
        if (data == '\r')
            continue;
        if (data == '\n') {
            GroveGpsData[GroveGpsDataLength] = '\0';
            GroveGpsDataLength = 0;
            return GroveGpsData;
        }
        
        if (GroveGpsDataLength > (int) sizeof(GroveGpsData) - 1) { // Overflow
            GroveGpsDataLength = 0;
            return GROVE_UART_OVERFLOW_STRING;
        }
        GroveGpsData[GroveGpsDataLength++] = data;
    }
    
    return NULL;
}

bool NectisCellularUartGps::IsGpsLocationUpdate() {
    return _gps.location.isUpdated();
}

float NectisCellularUartGps::CalcGpsLatitude() {
    float lat = _gps.location.lat();
    Serial.print("LAT=");
    Serial.println(lat, 6);
    return lat;
}

float NectisCellularUartGps::CalcGpsLongitude() {
    float lng = _gps.location.lng();
    Serial.print("LONG=");
    Serial.println(lng, 6);
    return lng;
}
