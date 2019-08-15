#include "NectisCellular.h"

#include <limits.h>

#include "WioCellular.h"
#include "Internal/Debug.h"
#include "Internal/ArgumentParser.h"

#define APN                             "soracom.io"
#define USERNAME                        "sora"
#define PASSWORD                        "sora"

#define ENDPOINT_URL                    "http://unified.soracom.io"

#define INTERVAL                        (10000)
#define RECEIVE_TIMEOUT                 (10000)

#define GROVE_UART_OVERFLOW_STRING      "OVERFLOW"

#if defined BINARY_PARSER_ENABLED
    #define HTTP_CONTENT_TYPE               "application/octet-stream"
#else
    #define HTTP_CONTENT_TYPE           "application/json"
#endif

#define HTTP_USER_AGENT                 "QUECTEL_MODULE"

#define RET_OK(val)                     (ReturnOk(val))
#define RET_ERR(val, err)               (ReturnError(__LINE__, val, err))
#define LINEAR_SCALE(val, inMin, inMax, outMin, outMax)    (((val) - (inMin)) / ((inMax) - (inMin)) * ((outMax) - (outMin)) + (outMin))

char hexConvertedFromDecimal[16];


NectisCellular::NectisCellular() : _SerialAPI(&SerialUART), _AtSerial(&_SerialAPI, &_Wio) {
}

NectisCellular::ErrorCodeType NectisCellular::GetLastError() const {
    return _LastErrorCode;
}

void NectisCellular::Init() {
    ////////////////////
    // Module
    
    // Power Supply
    pinMode(MODULE_PWR_PIN, OUTPUT);            digitalWrite(MODULE_PWR_PIN, LOW);
    // Turn On/Off
    pinMode(MODULE_PWRKEY_PIN, OUTPUT);         digitalWrite(MODULE_PWRKEY_PIN, LOW);
    pinMode(MODULE_RESET_PIN, OUTPUT);          digitalWrite(MODULE_RESET_PIN, LOW);
    // Status Indication
    pinMode(MODULE_STATUS_PIN, INPUT_PULLUP);
    // Main SerialUART Interface
    pinMode(MODULE_DTR_PIN, OUTPUT);            digitalWrite(MODULE_DTR_PIN, LOW);
    
    ////////////////////
    // Led
    pinMode(LED_RED, OUTPUT);                   digitalWrite(LED_RED, LOW);
    pinMode(LED_BLUE, OUTPUT);                  digitalWrite(LED_BLUE, LOW);
    ////////////////////
    
    // AD Converter
    pinMode(BATTERY_LEVEL_ENABLE_PIN, OUTPUT);
    
    // Grove
    pinMode(GROVE_VCCB_PIN, OUTPUT);            digitalWrite(GROVE_VCCB_PIN, LOW);
}

void NectisCellular::PowerSupplyCellular(bool on) {
    digitalWrite(MODULE_PWR_PIN, on ? HIGH : LOW);
    delay(200);
    digitalWrite(MODULE_PWRKEY_PIN, on ? HIGH : LOW);
    delay(600);
    digitalWrite(MODULE_PWRKEY_PIN, LOW);
}

void NectisCellular::PowerSupplyGrove(bool on) {
    digitalWrite(MODULE_PWR_PIN, on ? HIGH : LOW);
    delay(100);
    digitalWrite(GROVE_VCCB_PIN, on ? HIGH : LOW);
}

void NectisCellular::Bg96Begin() {
    //  Initialize Uart between BL654 and BG96.
    Serial1.setPins(MODULE_UART_RX_PIN, MODULE_UART_TX_PIN, MODULE_RTS_PIN, MODULE_CTS_PIN);
    Serial1.begin(115200);
    
    delay(200);
}

void NectisCellular::Bg96End() {
    Serial1.end();
}

bool NectisCellular::Bg96TurnOff() {
    if (!_AtSerial.WriteCommandAndReadResponse("AT+QPOWD", "^OK$", 500, NULL))
        return RET_ERR(false, E_UNKNOWN);
    if (!_AtSerial.ReadResponse("^POWERED DOWN$", 60000, NULL))
        return RET_ERR(false, E_UNKNOWN);
    
    return RET_OK(true);
}

void NectisCellular::InitLteM() {
    #ifdef NRF52840_XXAA
    _Wio.SetAccessTechnology(WioCellular::ACCESS_TECHNOLOGY_LTE_M1);
    _Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
    #endif
    
    Serial.println("### Turn on or reset.");
    if (!_Wio.TurnOnOrReset()) {
        Serial.println("### ERROR!; TurnOnOrReset ###");
        return;
    }
    
    delay(100);
    Serial.println("### Connecting to \"" APN "\".");
    if (!_Wio.Activate(APN, USERNAME, PASSWORD)) {
        Serial.println("### ERROR!; Activate ###");
        return;
    }
}

void NectisCellular::SoftReset() {
    NVIC_SystemReset();
}

bool NectisCellular::ReturnError(int lineNumber, bool value, NectisCellular::ErrorCodeType errorCode) {
    _LastErrorCode = errorCode;
    
    char str[100];
    sprintf(str, "%d", lineNumber);
    DEBUG_PRINT("ERROR! ");
    DEBUG_PRINTLN(str);
    
    return value;
}

int NectisCellular::ReturnError(int lineNumber, int value, NectisCellular::ErrorCodeType errorCode) {
    _LastErrorCode = errorCode;
    
    char str[100];
    sprintf(str, "%d", lineNumber);
    DEBUG_PRINT("ERROR! ");
    DEBUG_PRINTLN(str);
    
    return value;
}

int NectisCellular::GetReceivedSignalStrength() {
    std::string response;
    ArgumentParser parser;
    
    _AtSerial.WriteCommand("AT+CSQ");
    if (!_AtSerial.ReadResponse("^\\+CSQ: (.*)$", 500, &response))
        return RET_ERR(INT_MIN, E_UNKNOWN);
    
    parser.Parse(response.c_str());
    if (parser.Size() != 2)
        return RET_ERR(INT_MIN, E_UNKNOWN);
    int rssi = atoi(parser[0]);
    
    if (!_AtSerial.ReadResponse("^OK$", 500, NULL))
        return RET_ERR(INT_MIN, E_UNKNOWN);
    
    if (rssi == INT_MIN) {
        Serial.println("### ERROR! ###");
        delay(5000);
    }
    
    if (rssi == 0)
        return RET_OK(-113);
    else if (rssi == 1)
        return RET_OK(-111);
    else if (2 <= rssi && rssi <= 30)
        return RET_OK((int)LINEAR_SCALE((double)rssi, 2, 30, -109, -53));
    else if (rssi == 31)
        return RET_OK(-51);
    else if (rssi == 99)
        return RET_OK(-999);
    
    return RET_OK(-999);
}

int NectisCellular::GetReceivedSignalStrengthIndicator() {
    int rssi = GetReceivedSignalStrength();
    int rssi_count = 0;
    while (rssi == - 999) {
        rssi = GetReceivedSignalStrength();
        if (rssi_count == 10) {
            SoftReset();
        }
        rssi_count++;
        delay(1000);
    }
}

bool NectisCellular::IsTimeGot(struct tm *tim) {
    std::string response;
    
    // AT+QLTS=1 -> Acquire UTC
    // AT+QLTS=2 -> Acquire JST
    _AtSerial.WriteCommand("AT+QLTS=2");
    
    if (!_AtSerial.ReadResponse("^\\+QLTS: (.*)$", 500, &response)) return RET_ERR(false, E_UNKNOWN);
    if (!_AtSerial.ReadResponse("^OK$", 500, NULL)) return RET_ERR(false, E_UNKNOWN);
    
    if (strlen(response.c_str()) != 26) return RET_ERR(false, E_UNKNOWN);
    
    const char* parameter = response.c_str();
    
    if (parameter[0] != '"') return RET_ERR(false, E_UNKNOWN);
    if (parameter[5] != '/') return RET_ERR(false, E_UNKNOWN);
    if (parameter[8] != '/') return RET_ERR(false, E_UNKNOWN);
    if (parameter[11] != ',') return RET_ERR(false, E_UNKNOWN);
    if (parameter[14] != ':') return RET_ERR(false, E_UNKNOWN);
    if (parameter[17] != ':') return RET_ERR(false, E_UNKNOWN);
    if (parameter[23] != ',') return RET_ERR(false, E_UNKNOWN);
    if (parameter[25] != '"') return RET_ERR(false, E_UNKNOWN);
    
    tim->tm_year = atoi(&parameter[1]) - 1900;
    tim->tm_mon = atoi(&parameter[6]) - 1;
    tim->tm_mday = atoi(&parameter[9]);
    tim->tm_hour = atoi(&parameter[12]);
    tim->tm_min = atoi(&parameter[15]);
    tim->tm_sec = atoi(&parameter[18]);
    tim->tm_wday = 0;
    tim->tm_yday = 0;
    tim->tm_isdst = 0;
    
    // Update tm_wday and tm_yday
    mktime(tim);
    
    return RET_OK(true);
}

void NectisCellular::GetCurrentTime(struct tm *tim) {
    // Get time in JST.
    while (!IsTimeGot(tim)) {
        Serial.println("### ERROR! ###");
        delay(5000);
    }
}

float NectisCellular::ReadVusb() {
    float mv_per_lsb = 3600.0F/1024.0F; // 10-bit ADC with 3.6V input range
    
    int adcvalue = 0;
    float battery_level_mv = 0;
    
    // Get a fresh ADC value
    adcvalue = analogRead(USB_VOLTAGE_PIN);
    battery_level_mv = (float)adcvalue * mv_per_lsb;
    
    return battery_level_mv;
}

float NectisCellular::ReadVbat(void) {
    #define VBAT_MV_PER_LSB   (1.171875F)       // 1.2V ADC range and 10-bit ADC resolution = 1200mV/1024
    #define VBAT_DIVIDER      (0.25F)           // From IC: RP124N334E
    
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);
    
    int adcvalue = 0;
    
    // Set the analog reference to 1.2V (default = 3.6V)
    analogReference(AR_INTERNAL_1_2);
    
    // Set the resolution to 10-bit (0..1023)
    analogReadResolution(10); // Can be 8, 10, 12 or 14
    
    // Let the ADC settle
    delay(100);
    
    // Get the raw 10-bit, 0..1200mV ADC value
    adcvalue = analogRead(BATTERY_VOLTAGE_PIN);
    while ((adcvalue < 0) || (adcvalue > 1023)) {
        adcvalue = analogRead(BATTERY_VOLTAGE_PIN);
    }
    
    Serial.printf("adc_value: %d\n",adcvalue);
    
    // Convert the raw value to compensated mv, taking the resistor-
    // divider into account (providing the actual LIPO voltage)
    float battery_voltage_mv = (float) adcvalue * VBAT_MV_PER_LSB * (1/VBAT_DIVIDER);
    
    // Set the ADC back to the default settings
    analogReference(AR_DEFAULT);
    analogReadResolution(10);
    
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);
    
    return battery_voltage_mv;
}

float NectisCellular::mvToPercent(float mvolts) {
    float battery_level;
    
    //    When mvolts drops to (3200mA * 102%), the power supply from the battery shut down.
    //    Therefore, 0% of the battery level is set to 3250mA.
    if (mvolts >= 4150) {
        battery_level = 100;
    } else if (mvolts > 3750) {
        battery_level = 100.0 * (1.0 - (4150-mvolts)/900);
    } else if (mvolts > 3650) {
        battery_level = 50;
    } else if (mvolts > 3250) {
        battery_level = 100.0 * (1.0 - (4150-mvolts)/900);
    } else {
        battery_level = 0;
    }
    
    return battery_level;
}

void NectisCellular::PwmSetup(int pin, uint8_t flash_interval) {
    HwPWM0.addPin(pin);
    
    // Enable PWM modules with 15-bit resolutions(max) but different clock div
    HwPWM0.setResolution(15);
    HwPWM0.setClockDiv(flash_interval);
}

void NectisCellular::PwmBegin() {
    HwPWM0.begin();
}

void NectisCellular::PwmWritePin(int pin) {
    const int maxValue = bit(15) - 1;
    
    // fade in from min to max
    for (int fadeValue = 0; fadeValue <= maxValue; fadeValue += 1024) {
        // Write same value but inverted for Led Blue
        HwPWM0.writePin(pin, fadeValue, false);
        
        // wait for 30 milliseconds to see the dimming effect
        delay(30);
    }
    
    // fade out from max to min
    for (int fadeValue = maxValue; fadeValue >= 0; fadeValue -= 1024) {
        // Write same value but inverted for Led Blue
        HwPWM0.writePin(pin, fadeValue, false);
        
        // wait for 30 milliseconds to see the dimming effect
        delay(30);
    }
}

void NectisCellular::PwmStop() {
    HwPWM0.stop();
}

void NectisCellular::PwmActivate(int pin, uint8_t flash_interval) {
    PwmSetup(pin, flash_interval);
    NectisCellular::PwmBegin();
    PwmWritePin(pin);
    PwmStop();
}

char* NectisCellular::ConvertDecimalToHex(unsigned long int const decimal, int byte_size) {
    // The last index of post_data is filled with 0x00 for print function.
    memset(&hexConvertedFromDecimal[0], 0x00, sizeof(hexConvertedFromDecimal));
    // Serial.printf("ConvertDecimalToHex decimal: %u\n", decimal);
    
    for (int i = 0; i < (int) byte_size; i++) {
        // 16進数に変換し、４ビットずつ post_data を埋めていく
        hexConvertedFromDecimal[i] = (decimal >> (8 * ((byte_size - 1) - i))) & 0xff;
        // Serial.printf("(decimal >> (8*((byte_size-1)-i))):%x\n", (decimal >> (8 * ((byte_size - 1) - i))));
        // Serial.printf("hexConvertedFromDecimal[i]:%02x\n", hexConvertedFromDecimal[i]);
    }
    return hexConvertedFromDecimal;
}

unsigned int NectisCellular::GetDataDigits(unsigned int data) {
    // Copy the original data to calculate digits in order not to affect the original value.
    unsigned int data_to_calc_digit = data;
    unsigned int data_digit_hex = 0;
    
    // Calculating the digits of lat, lng in hexadecimal.
    // 2 digits = 1 byte
    // Calculating the bytes of the post data
    while (data_to_calc_digit != 0) {
        data_to_calc_digit /= 16;
        data_digit_hex++;
    }
    unsigned int size_of_post_data = (int)(ceil((double)data_digit_hex / 2));
    
    return size_of_post_data;
}

char* NectisCellular::ConvertIntoBinary(char* PostDataBinary, uint8_t data, unsigned int data_length) {
    memset(&PostDataBinary[0], 0x00, data_length);
    memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);
    
    return PostDataBinary;
}

char* NectisCellular::ConvertIntoBinary(char* PostDataBinary, uint16_t data, unsigned int data_length) {
    memset(&PostDataBinary[0], 0x00, data_length);
    memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);
    
    return PostDataBinary;
}

char* NectisCellular::ConvertIntoBinary(char* PostDataBinary, uint32_t data, unsigned int data_length) {
    memset(&PostDataBinary[0], 0x00, data_length);
    memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);
    
    return PostDataBinary;
}

char* NectisCellular::ConvertIntoBinary(char* PostDataBinary, int data, unsigned int data_length) {
    memset(&PostDataBinary[0], 0x00, data_length);
    memcpy(&PostDataBinary[0], ConvertDecimalToHex(data, data_length), data_length);
    
    return PostDataBinary;
}

int NectisCellular::GetIMEI(char *imei, int imeiSize){
  return _Wio.GetIMEI(imei,imeiSize);
}

int NectisCellular::GetIMSI(char *imsi, int imsiSize){
  return _Wio.GetIMSI(imsi,imsiSize);
}

int NectisCellular::GetICCID(char *iccid, int iccidSize){
  return _Wio.GetICCID(iccid, iccidSize);
}

int NectisCellular::GetPhoneNumber(char *number, int numberSize){
  return _Wio.GetPhoneNumber(number,numberSize);
}

int NectisCellular::SocketOpen(const char *host, int port, SocketType type){
  return _Wio.SocketOpen(host, port, (WioCellular::SocketType)type);
}

bool NectisCellular::SocketSend(int connectId, const byte *data, int dataSize){
  return _Wio.SocketSend(connectId, data, dataSize);
}

bool NectisCellular::SocketSend(int connectId, const char *data){
  return _Wio.SocketSend(connectId, data);
}

int NectisCellular::SocketReceive(int connectId, byte *data, int dataSize){
  return _Wio.SocketReceive(connectId, data, dataSize);
}

int NectisCellular::SocketReceive(int connectId, byte *data, int dataSize, long timeout){
  return _Wio.SocketReceive(connectId, data, dataSize, timeout);
}

int NectisCellular::SocketReceive(int connectId, char *data, int dataSize){
  return _Wio.SocketReceive(connectId, data, dataSize);
}

int NectisCellular::SocketReceive(int connectId, char *data, int dataSize, long timeout){
  return _Wio.SocketReceive(connectId, data, dataSize,timeout);
}

bool NectisCellular::SocketClose(int connectId){
  return _Wio.SocketClose(connectId);
}

int NectisCellular::HttpGet(const char *url, char *data, int dataSize) {
  return _Wio.HttpGet(url, data, dataSize);
}

int NectisCellular::HttpGet(const char *url, char *data, int dataSize, const WioCellularHttpHeader &header) {
  return _Wio.HttpGet(url,data,dataSize, header);
}

bool NectisCellular::HttpPost(const char *url, const char *data, int *responseCode) {
  return _Wio.HttpPost(url, data, responseCode);
}

bool NectisCellular::HttpPost(const char *url, const char *data, int *responseCode, const WioCellularHttpHeader &header) {
  return _Wio.HttpPost(url, data, responseCode, header);
}

bool NectisCellular::HttpPost2(const char *url, const char *data, int *responseCode , char *recv_data, int recv_dataSize) {
    return _Wio.HttpPost2(url, data, responseCode, recv_data, recv_dataSize);
}

bool NectisCellular::HttpPost2(const char *url, const char *data, int *responseCode, char *recv_data, int recv_dataSize , const WioCellularHttpHeader &header) {
    return _Wio.HttpPost2(url, data, responseCode, recv_data, recv_dataSize, header);
}

void NectisCellular::PostDataViaHttp(char *post_data) {
    Serial.println("### Post.");
    Serial.print("Post:");
    Serial.print(post_data);
    Serial.println("");
    
    WioCellularHttpHeader header;
    header["Accept"] = "*/*";
    header["User-Agent"] = HTTP_USER_AGENT;
    header["Connection"] = "Keep-Alive";
    header["Content-Type"] = HTTP_CONTENT_TYPE;
    
    int status;
    if (!_Wio.HttpPost(ENDPOINT_URL, post_data, &status, header)) {
        Serial.println("### ERROR! ###");
        goto err;
    }
    Serial.print("Status:");
    Serial.println(status);

err:
    Serial.println("### Wait.");
    delay(INTERVAL);
}

void NectisCellular::PostDataViaUdp(char *post_data) {
    Serial.println("### Open.");
    int connectId;
    connectId = _Wio.SocketOpen("uni.soracom.io", 23080, WIO_UDP);
    if (connectId < 0) {
        Serial.println("### ERROR! ###");
        goto err;
    }
    
    Serial.println("### Send.");
    Serial.print("Send:");
    Serial.print(post_data);
    Serial.println("");
    if (!_Wio.SocketSend(connectId, post_data)) {
        Serial.println("### ERROR! ###");
        goto err_close;
    }
    
    Serial.println("### Receive.");
    int length;
    length = _Wio.SocketReceive(connectId, post_data, sizeof(post_data), RECEIVE_TIMEOUT);
    if (length < 0) {
        Serial.println("### ERROR! ###");
        Serial.println(length);
        goto err_close;
    }
    if (length == 0) {
        Serial.println("### RECEIVE TIMEOUT! ###");
        goto err_close;
    }
    Serial.print("Receive:");
    Serial.print(post_data);
    Serial.println("");

err_close:
    Serial.println("### Close.");
    if (!_Wio.SocketClose(connectId)) {
        Serial.println("### ERROR! ###");
        goto err;
    }

err:
    delay(INTERVAL);
}

void NectisCellular::PostDataViaUdp(char *post_data, int data_length) {
    Serial.println("### Open.");
    int connectId;
    connectId = _Wio.SocketOpen("uni.soracom.io", 23080, WIO_UDP);
    if (connectId < 0) {
        Serial.println("### ERROR! ###");
        goto err;
    }
    
    Serial.println("### Send.");
    Serial.print("Send:");
    Serial.print(post_data);
    Serial.println("");
    if (!_Wio.SocketSend(connectId, (const byte *)post_data, data_length)) {
        Serial.println("### ERROR! ###");
        goto err_close;
    }
    
    Serial.println("### Receive.");
    int length;
    length = _Wio.SocketReceive(connectId, post_data, data_length, RECEIVE_TIMEOUT);
    if (length < 0) {
        Serial.println("### ERROR! ###");
        Serial.println(length);
        goto err_close;
    }
    if (length == 0) {
        Serial.println("### RECEIVE TIMEOUT! ###");
        goto err_close;
    }
    Serial.print("Receive:");
    Serial.print(post_data);
    Serial.println("");

err_close:
    Serial.println("### Close.");
    if (!_Wio.SocketClose(connectId)) {
        Serial.println("### ERROR! ###");
        goto err;
    }

err:
    delay(INTERVAL);
}
