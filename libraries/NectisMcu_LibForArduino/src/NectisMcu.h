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

  char *ConvertDecimalToHex(uint8_t decimal, int byte_size);
  char *ConvertDecimalToHex(uint16_t decimal, int byte_size);
  char *ConvertDecimalToHex(uint32_t decimal, int byte_size);
  char *ConvertDecimalToHex(int decimal, int byte_size);
  char *ConvertDecimalToHex(float const decimal, int byte_size);
  unsigned int GetDataDigits(unsigned int data);
  char *ConvertIntoBinary(char *PostDataBinary, uint8_t data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, uint16_t data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, uint32_t data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, int data, unsigned int data_length);
  char *ConvertIntoBinary(char *PostDataBinary, float data, unsigned int data_length);

  void PutFlashRomIntoDeepSleepMode();
  void WakeUpFlashRomFromDeepSleepMode();

  void SoftReset();

  void ConfigForWakingUpFromDeepSleep();
  void DisableAllPeripherals();
  void EnterSystemOffDeepSleepMode();
  void EnterCpuWfiWfeSleep();
  void ExitCpuWfiWfeSleep();

  void WatchdogTimerInit(const int wdtTimeoutSec);
  void WatchdogTimerDelay(uint32_t delayMilliSeconds);
  void ReloadWatchdogTimer();
};