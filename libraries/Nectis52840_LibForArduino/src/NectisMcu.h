#pragma once

#include "SPI.h"
#include <NectisCellular.h>


class NectisMcu {
public:
  NectisMcu();

  float ReadVusb();
  float ReadVbat(void);
  float mvToPercent(float mvolts);

  void PwmSetup(int pin, uint8_t flash_interval);
  void PwmBegin();
  void PwmWritePin(int pin);
  void PwmStop();
  void PwmActivate(int pin, uint8_t flash_interval);

  char *ConvertDecimalToHex(unsigned long int const decimal, int byte_size);
  unsigned int GetDataDigits(unsigned int data);
  char *ConvertIntoBinary(char *PostDataBinary, uint8_t data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, uint16_t data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, uint32_t data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, int data, unsigned int data_length);

  void PutFlashRomIntoDeepSleepMode();
  void WakeUpFlashRomFromDeepSleepMode();
  void SoftReset();
  void SetRtcTimer(unsigned int second);
  void WriteToRtcReg8(uint8_t slaveAddress, uint8_t format, uint8_t data);
  void WriteToRtc(uint8_t slaveAddress, uint8_t* data, int dataSize);
  void DisableAllPeripherals();
  void EnableAllPeripherals();
  void EnterSystemOffDeepSleepMode();
  void EnterCpuWfiWfeSleep();
  void WatchdogTimerInit(const int wdtTimeoutSec);
  void WatchdogTimerDelay(int delayMilliSeconds);
  void ReloadWatchdogTimer();
};