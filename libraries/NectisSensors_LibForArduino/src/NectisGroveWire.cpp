#include "NectisGroveWire.h"
#include "Wire.h"

#include <Arduino.h>
#include <wiring_digital.h>


NectisGroveWire::NectisGroveWire() : _GroveWire() {

}

NectisGroveWire::~NectisGroveWire() {

}

void NectisGroveWire::PowerSupplyGrove(bool on) {
	digitalWrite(GROVE_VCCB_PIN, on ? HIGH : LOW);
}

