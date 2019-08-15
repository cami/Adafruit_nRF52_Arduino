/*
 * Post battery level in every 1 minute.
 */

#include <NectisCellular.h>

#define GROVE_LED_PIN                 (GROVE_ANALOG_1_1)

NectisCellular Nectis;

// Uncomment following line to use Http
//#define HTTP
// Uncomment following line to use Udp
#define UDP

char postData[2];


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
//  Make sure that the MODULE_PWR_PIN is set to HIGH.
    Nectis.PowerSupplyGrove(true);
    delay(100);

    Nectis.Bg96Begin();
    Nectis.InitLteM();
    
    pinMode(GROVE_LED_PIN, OUTPUT);
    
    Serial.println("### Setup completed.");
}

void loop() {
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
    
    // Create post data in binary.
    memset(&postData[0], 0x00, sizeof(postData));
    memcpy(&postData[0], postDataBatteryLevel, sizeOfPostDataBatteryLevel);

#ifdef HTTP
    Nectis.PostDataViaHttp(postData);
#endif  // HTTP

#ifdef UDP
    Nectis.PwmActivate(GROVE_LED_PIN, PWM_PRESCALER_PRESCALER_DIV_128);
    Nectis.PostDataViaUdp(postData);
#endif  // UDP

    delay(60000);
}
