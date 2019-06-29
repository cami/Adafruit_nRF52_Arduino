#include "Arduino.h"
#include "HardwareSerial.h"


HardwareSerial::HardwareSerial(int port, uint8_t txPin, uint8_t rxPin, int ctsPin, int rtsPin) {}

HardwareSerial::HardwareSerial(NRF_UART_Type *_nrfUart, IRQn_Type _IRQn, uint8_t _pinRX, uint8_t _pinTX,
                               uint8_t _pinCTS, uint8_t _pinRTS) {}

HardwareSerial::HardwareSerial() {}

HardwareSerial::~HardwareSerial() {}
