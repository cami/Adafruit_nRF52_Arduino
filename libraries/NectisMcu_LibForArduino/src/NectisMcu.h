#pragma once
#include <stdint.h>

namespace mcu {
  void InitPins(void);
  void PowerSupplyCellular(bool);
  void PowerSupplyGrove(bool);
  void InitMcu(void);
  void ClearSerialBuffer(void);

  void TurnOnOffRedLed(bool);
  void TurnOnOffGreenLed(bool);

  float ReadVusb(void);
  float ReadVbat(void);
  float mvToPercent(float);
  uint8_t GetBatteryLevel();

  void PwmSetup(int, uint8_t);
  void PwmBegin(void);
  void PwmStop(void);
  void PwmWritePin(int);

  void ResetGpregretRegister(void);
  void SoftReset(void);

  void DisableAllPeripherals(void);
  void ConfigForDeepSleepWakeup(void);
  void EnterSystemOffDeepSleep(void);
  void EnterCpuWfiWfeSleep(void);
  void ExitCpuWfiWfeSleep(void);

  void WatchdogTimerInit(const int);
  void ReloadWatchdogTimer(void);
}
