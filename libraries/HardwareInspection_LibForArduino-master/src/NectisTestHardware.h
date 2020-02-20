#pragma once

#include <stdint.h>
#include <Arduino.h>

#include "Adafruit_SPIFlash.h"

#include <NectisMcu.h>
#include "NectisFlags.h"
#include "NectisCustomerMngt.h"   // For Customer Management


class NectisTestHardware {
public:
  NectisCellular _Nectis;
  NectisMcu _Mcu;
  NectisFlags _Flags;
  NectisCustomerMngt _Mngt;       // For Customer Management

  Adafruit_FlashTransport_SPI flashTransport;
//  Adafruit_FlashTransport_QSPI flashTransport;
  Adafruit_SPIFlash _flash;

public:
  NectisTestHardware();

  void ExecuteArbitraryParentTest(unsigned int input);

  void ExecuteArbitraryChildTestVoid(unsigned int input, char *imei, int imei_size);
  float ExecuteArbitraryChildTestFloat(unsigned int input);
  int ExecuteArbitraryChildTestInt(unsigned int input);
  uint32_t ExecuteArbitraryChildTestUint32(unsigned int input);
  void ExecuteArbitraryChildTestVoid(unsigned int input);

  void InitRelayPins();
  void InitAnalogPinsPullUp();
  void InitAnalogPinsPullDown();
  void InitGpioPins();

  void ActivateRelayPins(uint16_t flags);
  void PowerSupplyRelayPins(uint16_t flags);
  void USBRelayPins(uint16_t flags);
  void ActivateGpioPins(uint16_t flags);

  float ReadVbat();
  float ReadVusb();
  float ReadADValue(uint8_t pin);
  float ReadAnalogPin(uint16_t flags);
  float ReadGpioPin(uint16_t flags);
};

