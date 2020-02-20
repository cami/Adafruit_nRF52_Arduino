// 検査する側の基板に書き込むスケッチ

#include <NectisCellular.h>
#include <NectisMcu.h>

#include <NectisCellularConfig.h>
#include <Internal/Debug.h>

#include "NectisFlags.h"
#include "NectisTestHardware.h"


NectisCellular Nectis;
NectisMcu Mcu;

NectisFlags Flags;
NectisTestHardware TestHardware;


void setup() {
  uint16_t relayPinFlags = 0x0000;
  
  Serial.begin(115200);
  delay(4000);
  
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");
  
  Serial.println("### I/O Initialize.");
  Nectis.Init();
  delay(100);
  
  DEBUG_PRINTLN("### Relay Pins Initialize.");
  TestHardware.InitRelayPins();
  
  DEBUG_PRINTLN("### Relay Flags Initialize.");
  Flags.ClearFlags(&relayPinFlags);
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_5V0;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_4V5;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_4V2;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_3V8;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_G3V3;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_3V3;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
  
  delay(1000);
  Flags.ClearFlags(&relayPinFlags);
  TestHardware.InitRelayPins();
  relayPinFlags |= ACTIVATE_RELAY_PIN_1V8;
  TestHardware.ActivateRelayPins(relayPinFlags);
  
}

void loop() {
  __NOP();
}