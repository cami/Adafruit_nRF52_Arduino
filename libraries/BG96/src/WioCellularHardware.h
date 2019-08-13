#pragma once

#include "NectisCellularConfig.h"

#include "Arduino.h"
#include "HardwareSerial.h"

#include <USBSerial.h>
#include <Uart.h>

// See hardware > cami > nrf52 > cores > nRF5 > Uart.h
#define SerialUSB Serial
// See hardware > cami > nrf52 > cores > nRF5 > usb > USBSerial.h
#define SerialUART Serial1

extern USBSerial SerialUSB;

extern Uart SerialUART;
