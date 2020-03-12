#include "NectisGroveUart.h"
#include "Uart.h"
#include "TinyGPS++.h"

#include <Arduino.h>
#include <variant.h>
#include <wiring_digital.h>

constexpr uint32_t GROVE_HARDWARE_SERIAL_RX = GROVE_UART_RX;
constexpr uint32_t GROVE_HARDWARE_SERIAL_TX = GROVE_UART_TX;

constexpr uint16_t GPS_DATA_SIZE = 64;
constexpr uint16_t CO2_DATA_SIZE = 9;
constexpr uint16_t RFID_DATA_SIZE = 32;


NectisGroveUart::NectisGroveUart() : _GroveUart() {
	_GroveUart = &Serial1;
	_gps = nullptr;

	_gps_data = nullptr;
	_co2_data = nullptr;
	_rfid_data = nullptr;
}

NectisGroveUart::~NectisGroveUart() {

}


/*
 * Power on.
 */
void NectisGroveUart::PowerSupplyGrove(bool on) {
	digitalWrite(GROVE_VCCB_PIN, on ? HIGH : LOW);
}


/*
 * Begin/End.
 */
void NectisGroveUart::Begin(unsigned long baudRate) {
	_GroveUart->setPins(GROVE_HARDWARE_SERIAL_RX, GROVE_HARDWARE_SERIAL_TX);
	_GroveUart->begin(baudRate);
}

void NectisGroveUart::End() {
	_GroveUart->end();
}


/*
 * Grove GPS
 */
gps_data_t* NectisGroveUart::GpsSetup(gps_data_t* gps_data) {
	gps_data = new gps_data_t;
	_gps_data = gps_data;
	return _gps_data;
}

bool NectisGroveUart::IsGpsLocationUpdate() {
	return _gps->location.isUpdated();
}

bool NectisGroveUart::GetGpsData() {
	char gpsDataArray[GPS_DATA_SIZE];
	uint16_t gpsDataLength = 0;

	memset(gpsDataArray, 0x00, GPS_DATA_SIZE);

	while (_GroveUart->available()) {
		char data = _GroveUart->read();
		_gps->encode(data);
		
		if (data == '\r')	continue;
		if (data == '\n') {
			gpsDataArray[gpsDataLength] = '\0';
			gpsDataLength = 0;
			break;
		}
		
		gpsDataArray[gpsDataLength++] = data;

		if (gpsDataLength - 1 > GPS_DATA_SIZE) { // Overflow
			memset(gpsDataArray, 0x00, GPS_DATA_SIZE);
			Serial.println("### OVERFLOW");
			return false;
		}
	}

  if (gpsDataArray != NULL && strncmp(gpsDataArray, "$GPGGA,", 7) == 0) {
    Serial.printf("GPS=%s\n", gpsDataArray);
		_gps_data->lat = _gps->location.lat();
		_gps_data->lng = _gps->location.lng();
		return true;
  } else {
		return false;
	}
}

void NectisGroveUart::PrintGpsData() {
	Serial.printf("LAT=%.6f, LNG=%.6f\n", _gps_data->lat, _gps_data->lng);
}


/*
 * Grove CO2
 */
co2_data_t* NectisGroveUart::Co2Setup(co2_data_t* co2_data) {
	co2_data = new co2_data_t;
	_co2_data = co2_data;
	return _co2_data;
}

void NectisGroveUart::Co2Calibration() {
	const unsigned char cmd_calibrate[] = {
		0xff, 0x87, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2
	};
	
	Serial.println("### Calibration started.");
	
	for(unsigned int i = 0; i < sizeof(cmd_calibrate); i++) {
		_GroveUart->write(cmd_calibrate[i]);
	}
	
	Serial.println("### Calibration done");
}

bool NectisGroveUart::GetCo2Data() {
	const unsigned char cmd_get_sensor[] = {
		0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
	};

	unsigned int i = 0;
	byte data[CO2_DATA_SIZE];
	uint32_t CO2PPM;

	memset(&data[0], 0x00, CO2_DATA_SIZE);
	
	//transmit command data
	for(i = 0; i < sizeof(cmd_get_sensor); i++) {
		_GroveUart->write(cmd_get_sensor[i]);
	}
	delay(10);
	
	//begin reveiceing data
	if(_GroveUart->available()) {
		while(_GroveUart->available()) {
			for(i = 1; i < CO2_DATA_SIZE; i++) {
				data[i] = _GroveUart->read();
			}
		}
	}

	if((i != CO2_DATA_SIZE) || (1 + (0xFF ^ (byte)(data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7]))) != data[8]) {
		return false;
	} else {
		for(i = 0; i < CO2_DATA_SIZE; i++) {
			Serial.printf("0x%x ", data[i]);
		}
		Serial.println("");
	
		CO2PPM = (uint32_t)data[2] * 256 + (uint32_t)data[3];
		// temperature = (int)data[4] - 40;

		_co2_data->co2 = CO2PPM;
		return true;
	}
}

void NectisGroveUart::PrintCo2Data() {
	Serial.printf("CO2=%u\n", _co2_data->co2);
}


/*
 * Grove RFID
 */
rfid_data_t* NectisGroveUart::RfidSetup(rfid_data_t* rfid_data) {
	rfid_data = new rfid_data_t;
	_rfid_data = rfid_data;
	return _rfid_data;
}

bool NectisGroveUart::GetRfidData() {
	uint16_t rfidDataLength = 0;
	byte rfidDataArray[RFID_DATA_SIZE];

	while (_GroveUart->available()) {
		int read_data_int = _GroveUart->read();
		char read_data_char = (char)read_data_int;
		
		//    Start to read RF tag data, if read_data_int == 2 (It means 'STX' in ASCII Chart.)
		if (read_data_int == 2)
			continue;
		
		//    End to read RF tag data, if read_data_int == 3 (It means 'ETX' in ASCII Chart.)
		if (read_data_int == 3) {
			rfidDataArray[rfidDataLength] = '\0';
			rfidDataLength = 0;
			break;
		}
		
		rfidDataArray[rfidDataLength++] = read_data_char;
	}

	Serial.printf("RfidData=%s\n", rfidDataArray);

	memcpy(_rfid_data, rfidDataArray, RFID_DATA_SIZE);

	return true;
}

void NectisGroveUart::PrintRfidData() {
	Serial.printf("RFID=%s\n", _rfid_data->rfid);
}