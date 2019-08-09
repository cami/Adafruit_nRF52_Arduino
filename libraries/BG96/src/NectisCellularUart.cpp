#include "NectisCellularUart.h"
#include "WioCellularHardware.h"

char GroveUartData[64];
int GroveUartDataLength;

NectisCellularUart::NectisCellularUart() : _SerialAPI(&SerialUART), _AtSerial(&_SerialAPI, &_Wio) {
}

void NectisCellularUart::GroveUartSetup() {
    _GroveUartSerial = &Serial1;
    GroveUartDataLength = 0;
    memset(&GroveUartData[0], 0x00, sizeof(GroveUartData));
}

void NectisCellularUart::GroveUartBegin() {
    _GroveUartSerial->setPins(GROVE_UART_RX_PIN, GROVE_UART_TX_PIN);
    _GroveUartSerial->begin(9600);
}

void NectisCellularUart::GroveUartEnd() {
    _GroveUartSerial->end();
}

const char *NectisCellularUart::RfidRead() {
    while (_GroveUartSerial->available()) {
        int read_data_int = _GroveUartSerial->read();
        char read_data_char = (char)read_data_int;
        
        //    Start to read RF tag data, if read_data_int == 2 (It means 'STX' in ASCII Chart.)
        if (read_data_int == 2)
            continue;
        
        //    End to read RF tag data, if read_data_int == 3 (It means 'ETX' in ASCII Chart.)
        if (read_data_int == 3) {
            GroveUartData[GroveUartDataLength] = '\0';
            GroveUartDataLength = 0;
            Serial.print("RfidData:");
            Serial.println(GroveUartData);
            return GroveUartData;
        }
        
        GroveUartData[GroveUartDataLength++] = read_data_char;
    }
    
    return NULL;
}

bool NectisCellularUart::IsCo2Read(void) {
    const unsigned char cmd_get_sensor[] = {
        0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
    };
    
    //    byte data[9];
    uint8_t data[9];
    memset(&data[0], 0x00, sizeof(data));
    unsigned int i = 0;
    int temperature;
    int CO2PPM;
    
    //transmit command data
    for(i=0; i<sizeof(cmd_get_sensor); i++) {
        _GroveUartSerial->write(cmd_get_sensor[i]);
    }
    delay(10);
    //begin reveiceing data
    if(_GroveUartSerial->available())
    {
        while(_GroveUartSerial->available())
        {
            //            for(int i=0;i<9; i++)
            //            0 0 0 50 255 134 2 252 73 0 255 255 255 255 255 255
            if (_GroveUartSerial->read() == 0xff) {
                data[0] = 0xff;
                for(int i=1; i<9; i++) {
                    data[i] = _GroveUartSerial->read();
                }
            }
        }
    }
    
    for(int j=0; j<9; j++) {
        Serial.print(data[j]);
        Serial.print(" ");
    }
    Serial.println("");
    
    //    Check value
    //    if((i != 9) || (1 + (0xFF ^ (byte)(data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7]))) != data[8]) {
    //        return false;
    //    }
    
    CO2PPM = (int)data[2] * 256 + (int)data[3];
    temperature = (int)data[4] - 40;
    
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("  CO2: ");
    Serial.print(CO2PPM);
    Serial.println("");
    
    return true;
}

uint16_t NectisCellularUart::Co2Read(void) {
    const unsigned char cmd_get_sensor[] = {
        0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79
    };
    
    //    byte data[9];
    uint8_t data[9];
    memset(&data[0], 0x00, sizeof(data));
    unsigned int i = 0;
    uint16_t CO2PPM;
    
    //transmit command data
    for(i=0; i<sizeof(cmd_get_sensor); i++) {
        _GroveUartSerial->write(cmd_get_sensor[i]);
    }
    delay(10);
    //begin reveiceing data
    if(_GroveUartSerial->available())
    {
        while(_GroveUartSerial->available())
        {
            //            big-endian, little-endian
            //            for(int i=0;i<9; i++)
            //            0 0 0 50 255 134 2 252 73 0 255 255 255 255 255 255
            if (_GroveUartSerial->read() == 0xff) {
                data[0] = 0xff;
                for(int i=1; i<9; i++) {
                    data[i] = _GroveUartSerial->read();
                }
            }
        }
    }
    
    for(int j=0; j<9; j++) {
        Serial.print(data[j]);
        Serial.print(" ");
    }
    Serial.println("");
    
    //    Check value
    //    if((i != 9) || (1 + (0xFF ^ (byte)(data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7]))) != data[8]) {
    //        return false;
    //    }
    
    CO2PPM = (int)data[2] * 256 + (int)data[3];
    
    return CO2PPM;
}

void NectisCellularUart::Co2Calibration() {
    const unsigned char cmd_calibrate[] = {
        0xff, 0x87, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2
    };
    
    Serial.println("begin to calibrate");
    
    for(unsigned int i=0; i<sizeof(cmd_calibrate); i++)
    {
        _GroveUartSerial->write(cmd_calibrate[i]);
    }
    
    Serial.println("calibrate done");
}