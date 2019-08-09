/*
 * http://wiki.seeedstudio.com/Grove-GPS/
 * This sketch enables to get GPS data and post it to SORACOM unified endpoint.
 */

#include <NectisCellular.h>
#include "NectisCellularUartGps.h"

// Uncomment following line to use Http
//#define HTTP
// Uncomment following line to use Udp
#define UDP

NectisCellular Nectis;
NectisCellularUartGps NectisGps;

bool isGroveUartEnabled;

// Settings for SORACOM binary parser
// lat:0:uint:32:/1000000 lng:4:uint:32:/1000000 rssi:8:int:8 battery:9:uint:8
// Reserve 11 bytes for latitude (4 bytes), longitude (4 bytes), RSSI (1 byte), battery (1 byte) and '\0'
char postData[11];


void setup() {
    delay(4000);
    
    Serial.begin(115200);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Serial.println("### I/O Initialize.");
    Nectis.Init();
    delay(100);
    Serial.println("### Power supply cellular ON.");
    Nectis.PowerSupplyCellular(true);
    delay(100);
    
    Serial.println("### Power supply ON.");
    // Make sure that the MODULE_PWR_PIN is set to HIGH.
    Nectis.PowerSupplyGrove(true);
    delay(100);
    
    isGroveUartEnabled = false;
    
    Serial.println("### Setup completed.");
}

void loop() {
    // Enable Uart between BL654 and GroveSensor sensor in order to get data from the GroveSensor uart sensor again and again.
    if (!isGroveUartEnabled) {
        // Initialize Uart between BL654 and GroveSensor sensor (Grove_GPIO_5_1, Grove_GPIO_5_2)
        NectisGps.GroveUartSetup();
        NectisGps.GroveUartBegin();
        isGroveUartEnabled = true;
        delay(1000);
    }
    
    const char *data = NectisGps.GpsRead();
    
    if (NectisGps.IsGpsLocationUpdate()) {
        // End Uart for GroveSensor sensor in order to switch Uart from GroveSensor sensor to BG96
        NectisGps.GroveUartEnd();
        //        Nectis.PowerSupplyGrove(false);
        isGroveUartEnabled = false;
    }
    
    if (data != NULL && strncmp(data, "$GPGGA,", 7) == 0) {
        Serial.println(data);
    }
    
    if (NectisGps.IsGpsLocationUpdate()) {
        // GPS Data
        float lat = NectisGps.CalcGpsLatitude();
        float lng = NectisGps.CalcGpsLongitude();
        Serial.printf("latitude: %f\n", lat);
        Serial.printf("longitude: %f\n", lng);
        
        uint32_t const latDecimal = (uint32_t)(lat * 1000000);
        uint32_t const lngDecimal = (uint32_t)(lng * 1000000);
        
        unsigned int sizeOfPostDataLat = Nectis.GetDataDigits((unsigned int)latDecimal);
        unsigned int sizeOfPostDataLng = Nectis.GetDataDigits((unsigned int)lngDecimal);
        
        char *postDataLat;
        char *postDataLng;
        char tmpPostDataLat[sizeOfPostDataLat];
        char tmpPostDataLng[sizeOfPostDataLng];
        
        postDataLat = Nectis.ConvertIntoBinary(tmpPostDataLat, latDecimal, sizeOfPostDataLat);
        postDataLng = Nectis.ConvertIntoBinary(tmpPostDataLng, lngDecimal, sizeOfPostDataLng);
        
        
        // Battery Level
        float LipoVoltageLevelMv = Nectis.ReadVbat();
        float LipoVoltageLevelPercentageFloat = Nectis.mvToPercent(LipoVoltageLevelMv);
        uint8_t LipoVoltageLevelPercentageInt = (unsigned int)(LipoVoltageLevelPercentageFloat + 0.5F);
        Serial.printf("Lipo battery: %u[%%}\n", LipoVoltageLevelPercentageInt);
        
        unsigned int sizeOfPostDataBatteryLevel = Nectis.GetDataDigits(LipoVoltageLevelPercentageInt);
        char *postDataBatteryLevel;
        char tmpPostDataBatteryLevel[sizeOfPostDataBatteryLevel];
        postDataBatteryLevel = Nectis.ConvertIntoBinary(tmpPostDataBatteryLevel, LipoVoltageLevelPercentageInt,
                                                        sizeOfPostDataBatteryLevel);
        
        
        // ToDo: Need to enter PSM mode
        // Switch Uart from GroveSensor sensor to BG96
        Nectis.Bg96Begin();
        Nectis.InitLteM();
        // Stabilize LTE-M communication.
        delay(5000);
        
        // RSSI
        int rssi = Nectis.GetReceivedSignalStrength();
        while (rssi == -999) {
            rssi = Nectis.GetReceivedSignalStrength();
            delay(1000);
        }
        Serial.printf("rssi: %d\n", rssi);
        
        unsigned int sizeOfPostDataRssi = Nectis.GetDataDigits((unsigned int)abs(rssi));
        char *postDataRssi;
        char tmpPostDataRssi[sizeOfPostDataRssi];
        postDataRssi = Nectis.ConvertIntoBinary(tmpPostDataRssi, rssi, sizeOfPostDataRssi);
        
        
        // Create post data in binary.
        memset(&postData[0], 0x00, sizeof(postData));
        memcpy(&postData[0], postDataLat, sizeOfPostDataLat);
        memcpy(&postData[0] + sizeOfPostDataLat, postDataLng, sizeOfPostDataLng);
        memcpy(&postData[0] + sizeOfPostDataLat + sizeOfPostDataLng, postDataRssi, sizeOfPostDataRssi);
        memcpy(&postData[0] + sizeOfPostDataLat + sizeOfPostDataLng + sizeOfPostDataRssi, postDataBatteryLevel,
               sizeOfPostDataBatteryLevel);
        
        
        #ifdef HTTP
        Nectis.PostDataViaHttp(postData);
        #endif  // HTTP
        
        #ifdef UDP
        // Substract 1 from the sizeof(postData) because of the last character of postData is '0x00' for print function etc.
        Nectis.PostDataViaUdp(postData, sizeof(postData)-1);
        #endif  // UDP
        
        // Enter BG96 into sleep mode with AT command
        Nectis.BG96TurnOff();
        // End the Uart between nRF52840 and BG96
        Nectis.Bg96End();
    }
}
