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

  unsigned int GetDataDigits(unsigned int data);
  char *ConvertIntoBinary(char *binary, uint8_t data, unsigned int size);
  char *ConvertIntoBinary(char *binary, uint16_t data, unsigned int size);
  char *ConvertIntoBinary(char *binary, uint32_t data, unsigned int size);
  char *ConvertIntoBinary(char *binary, int data, unsigned int size);

  void PutFlashRomIntoDeepSleepMode();
  void WakeUpFlashRomFromDeepSleepMode();

  void SoftReset();

  void ConfigForWakingUpFromDeepSleep();
  void DisableAllPeripherals();
  void EnterSystemOffDeepSleepMode();
  void EnterCpuWfiWfeSleep();
  void ExitCpuWfiWfeSleep();

  void WatchdogTimerInit(const int wdtTimeoutSec);
  void WatchdogTimerDelay(int delayMilliSeconds);
  void ReloadWatchdogTimer();

private:
  char *ConvertDecimalToHex(unsigned long int const decimal, int size);
};