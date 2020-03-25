#include "NectisGroveUart.h"
#include "Uart.h"
#include "TinyGPS++.h"
#include "NectisDebug.h"

#include <Arduino.h>
#include <variant.h>
#include <wiring_digital.h>

constexpr uint32_t GROVE_HARDWARE_SERIAL_RX = GROVE_UART_RX;
constexpr uint32_t GROVE_HARDWARE_SERIAL_TX = GROVE_UART_TX;

TinyGPSPlus gps;


NectisGroveUart::NectisGroveUart() : _GroveUart() {
	_GroveUart = &Serial1;

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
gps_data_t* NectisGroveUart::GpsNewData() {
	_gps_data = new gps_data_t;
	return _gps_data;
}

void NectisGroveUart::GpsDeleteData() {
	delete _gps_data;
	_gps_data = nullptr;
}

const char* NectisGroveUart::ReadGps() {
	/*
	 * ReadGps()メソッドの呼び出し元では、delay()を入れないので、常にmemset()が実行されることになり、
	 * Serial.printf("gps=%s\n", gpsDataArray);
	 * というように、if (data == '\n') {} の中で、gpsDataArrayを操作しようとすると、
	 * memset()が実行された配列が対象となる。
	 * これを避けるために、memset()を実行するのではなく、配列の終端に'\0'を挿入することで対処する。
	 */
	// memset(gpsDataArray, '\0', GPS_DATA_SIZE);

	while (_GroveUart->available()) {
		char data = _GroveUart->read();
		gps.encode(data);
		
		// GPS のデータが表示できない
		if (data == '\r')	continue;
		if (data == '\n') {
			gpsDataArray[gpsDataLength] = '\0';

			delay(10);

			gpsDataLength = 0;
			return gpsDataArray;
		}
		
		if (gpsDataLength - 1 > GPS_DATA_SIZE) { // Overflow
			Serial.println("### OVERFLOW");

			gpsDataLength = 0;
			return "OVERFLOW";
		}

		gpsDataArray[gpsDataLength++] = data;
	}

	return NULL;
}

bool NectisGroveUart::GetGpsData() {
	// gpsDataArray をprivate変数として所有しているため、戻り値はない
	const char* gpsData = ReadGps();

	/* 
	 * 衛星捕捉前
	 * $GPGGA,030838.183,,,,,0,2,,,M,,M,,*40
	 * lat=-2689.000002 lng=-1823.000002 month=18 day=0 year=2073
	 * 衛星捕捉後
	 * 
	 * 
	 */
	// $GPGGA,025129.000,3537.6636,N,13943.5273,E,1,5,1.31,23.6,M,39.4,M,,*66
  if (gpsData != NULL && strncmp(gpsData, "$GPGGA,", 7) == 0) {
		NECTIS_DEBUG_PRINTLN(gpsData);

		numSatellites = gps.satellites.value();
		isLocationUpdated = gps.location.isUpdated();
		if (numSatellites >= 1) {
			if (gps.location.isValid() && isLocationUpdated) {
				lat = gps.location.lat();
				lng = gps.location.lng();
				_gps_data->lat = lat;
				_gps_data->lng = lng;
			}

			if (gps.date.isValid() && gps.date.isUpdated()) {
				year = gps.date.year();
				month = gps.date.month();
				day = gps.date.day();
				_gps_data->year = year;
				_gps_data->month = month;
				_gps_data->day = day;
			}

			if (gps.time.isValid() && gps.time.isUpdated()) {
				hour = gps.time.hour();
				minute = gps.time.minute();
				second = gps.time.second();
				centisecond = gps.time.centisecond();
				_gps_data->hour = hour;
				_gps_data->minute = minute;
				_gps_data->second = second;
				_gps_data->centisecond = centisecond;
			}

			if ((numSatellites >= 4) && isLocationUpdated) {
				_gps_data->numSatellites = numSatellites;
				return true;
			}
		}
	}
	return false;
}

void NectisGroveUart::PrintGpsData() {
	Serial.printf("lat=%.6f lng=%.6f, ", _gps_data->lat, _gps_data->lng);
	Serial.printf("%u/%u/%u(MM/DD/YY), ", _gps_data->month, _gps_data->day, _gps_data->year);
	Serial.printf("%02u:%u:%u:%03u(HH:MM:SS:centiSS) (UST)\n", _gps_data->hour, _gps_data->minute, _gps_data->second, _gps_data->centisecond);
}


/*
 * Grove CO2
 */
co2_data_t* NectisGroveUart::Co2NewData() {
	_co2_data = new co2_data_t;
	return _co2_data;
}

void NectisGroveUart::Co2DeleteData() {
	delete _co2_data;
	_co2_data = nullptr;
}

void NectisGroveUart::Co2Calibrate() {
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
	int temperature;
	int CO2PPM;

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
		CO2PPM = (int)data[2] * 256 + (int)data[3];
		temperature = (int)data[4] - 40;

		_co2_data->temperature = temperature;
		_co2_data->co2ppm = CO2PPM;

		return true;
	}
}

void NectisGroveUart::PrintCo2Data() {
    Serial.printf("temperature=%d\n", _co2_data->temperature);
    Serial.printf("co2[ppm]=%d\n", _co2_data->co2ppm);
}


/*
 * Grove RFID
 */
rfid_data_t* NectisGroveUart::RfidNewData() {
	_rfid_data = new rfid_data_t;
	return _rfid_data;
}

void NectisGroveUart::RfidDeleteData() {
	delete _rfid_data;
	_rfid_data = nullptr;
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