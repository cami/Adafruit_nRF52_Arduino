#include "NectisRTC.h"

//INTERNAL_ADDRESS = INTERNAL_ADDRESS_SECOND_COUNTER_POS = 0b0000
// Write
// ROLE    : | SLAVE_ADDRESS | R/W | INTERNAL_ADDRESS | TRANSFER_FORMAT |            DATA              |
// SDA LINE: | 0 1 1 0 0 1 0 |  0  |     0 0 0 0      |     0 0 0 0     | — S40 S20 S10 S8  S4  S2  S1 |
// SDA LINE: | 7 6 5 4 3 2 1 |  0  |     7 6 5 4      |     3 2 1 0     | 7 6   5   4   3   2   1   0  |

// Read
// ROLE    : | SLAVE_ADDRESS | R/W | INTERNAL_ADDRESS | TRANSFER_FORMAT | SLAVE_ADDRESS | R/W |            DATA              |
// SDA LINE: | 0 1 1 0 0 1 0 |  0  |     0 0 0 0      |     0 0 0 0     | 0 1 1 0 0 1 0 |  1  | — S40 S20 S10 S8  S4  S2  S1 |
// SDA LINE: | 7 6 5 4 3 2 1 |  0  |     7 6 5 4      |     3 2 1 0     | 7 6 5 4 3 2 1 |  1  | 7 6   5   4   3   2   1   0  |


const uint8_t SLAVE_ADDRESS =                             0b00110010 << 1;   // 7bits
const uint8_t DATA_TRANSFER_BIT_HIGH =                    0b00000001;   // R/W bit
const uint8_t DATA_TRANSFER_BIT_LOW =                     0b00000000;   // R/W bit

// To write data(seconds) to INTERNAL_ADDRESS_SECOND_COUNTER, use (INTERNAL_ADDRESS_SECOND_COUNTER | WRITE_TRANSFER_FORMAT).
// When ALARM is enabled, INTRB pin is HIGH in every set counter.
const uint8_t TRANSFER_FORMAT =                           0x00;

const uint8_t INTERNAL_ADDRESS_SECOND_COUNTER_POS =       0x00;
const uint8_t INTERNAL_ADDRESS_MINUTE_COUNTER_POS =       0x10;
const uint8_t INTERNAL_ADDRESS_HOUR_COUNTER_POS =         0x20;
const uint8_t INTERNAL_ADDRESS_DAYOFWEEK_COUNTER_POS =    0x30;
const uint8_t INTERNAL_ADDRESS_DAY_COUNTER_POS =          0x40;
const uint8_t INTERNAL_ADDRESS_MONTH_COUNTER_POS =        0x50;
const uint8_t INTERNAL_ADDRESS_YEAR_COUNTER_POS =         0x60;

const uint8_t INTERNAL_ADDRESS_MINUTE_ALARM_POS =         0x80;
const uint8_t INTERNAL_ADDRESS_HOUR_ALARM_POS =           0x90;
const uint8_t INTERNAL_ADDRESS_DAYOFWEEK_ALARM_POS =      0xA0;

// 曜日レジスタのAW0からAW6は、曜日カウンタ (W4, W2, W1) = (0, 0, 0) ~ (1, 1, 0) に対応します。
// DATA_DAYOFWEEK_COUNTER: (SUN, MON, TUE, WED, THU, FRI, SAT) = (0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7)
// DATA_DAYOFWEEK_ALARM: (SUN, MON, TUE, WED, THU, FRI, SAT) = (1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6)
//
//const uint8_t DATA_SECOND_COUNTER                         (—   S40 S20 S10  S8  S4  S2  S1)
//const uint8_t DATA_MINUTE_COUNTER                         (—   M40 M20 M10  M8  M4  M2  M1)
//const uint8_t DATA_HOUR_COUNTER                           (—   —   H20 H10  H8  H4  H2  H1)
//const uint8_t DATA_DAYOFWEEK_COUNTER                      (—   —   —   —    —   W4  W2  W1)
//const uint8_t DATA_DAY_COUNTER                            (—   —   D20 D10  D8  D4  D2  D1)
//const uint8_t DATA_MONTH_COUNTER                          (—   —   —   MO10 MO8 MO4 MO2 MO1)
//const uint8_t DATA_YEAR_COUNTER                           (Y80 Y40 Y20 Y10  Y8  Y4  Y2  Y1)
//
//const uint8_t DATA_MINUTE_ALARM                           (— AM40 AM20 AM10 AM8 AM4 AM2 AM1)
//const uint8_t DATA_HOUR_ALARM                             (— -    AH20 AH10 AH8 AH4 AH2 AH1)
//const uint8_t DATA_DAYOFWEEK_ALARM                        (— AW6  AW5  AW4  AW3 AW2 AW1 AW0)

const uint8_t INTERNAL_ADDRESS_CONTROL_REGISTER1_POS =    0xE0;
// アラームを発生させたい時間を設定した後に、イネーブルをオンにします。
// Set the constant interrupt: in every one SECOND/MINUTE/HOUR/MONTH
const uint8_t DATA_REGISTER1_MASK =                       0b00000000;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_SECOND =  0b00000100;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_MINUTE =  0b00000101;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_HOUR =    0b00000110;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_MONTH =   0b00000111;
const uint8_t DATA_REGISTER1_ENABLE_ALARM =               0b10000000;

uint8_t DATA_ENABLE_INTERRUPT_OR_ALARM =                  DATA_REGISTER1_MASK | DATA_REGISTER1_ENABLE_ALARM;

const uint8_t INTERNAL_ADDRESS_CONTROL_REGISTER2_POS =    0xF0;
const uint8_t DATA_REGISTER2_MASK =                       0b00000000;
const uint8_t DATA_REGISTER2_24HOUR_CLOCK =               0b00100000;
const uint8_t DATA_REGISTER2_DISABLE_32KHZ_CLOCK_OUTPUT = 0b00001000;


NectisRTC::NectisRTC() : _RtcWire(NRF_TWIM0, NRF_TWIS0, SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn, RTC_I2C_SDA_PIN, RTC_I2C_SCL_PIN){
//NectisRTC::NectisRTC() : _RtcWire(NRF_TWIM0, NRF_TWIS0, SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn, RTC_I2C_SCL_PIN, RTC_I2C_SDA_PIN){

}

void NectisRTC::InitRtc() {
  _RtcWire.begin();
}

void NectisRTC::ReadCalender() {
  uint8_t internalAddress = INTERNAL_ADDRESS_SECOND_COUNTER_POS;
  uint8_t* data;

  WriteToRtcReg8(internalAddress, 0b00001111);

  ReadFromRtcReg8(internalAddress, data);
  Serial.printf("%x: %u", internalAddress, data);
}

//void NectisRTC::SetRtcTimerTime(unsigned int second, unsigned int minute, unsigned int hour) {
////  アラーム割り込み出力はINTRB端子から出力されます。割り込み出力時はINTRB=Lowです。
//// ToDO: internalAddress, dataをRTCのタイマーに合わせて計算。
//  uint8_t internalAddress = 0x00;
//  uint8_t data = 0x00;
//
//  WriteToRtcReg8(internalAddress, data);
//}
//
//void NectisRTC::SetRtcTimerDayofweek(unsigned int dayofweek) {
////  アラーム割り込み出力はINTRB端子から出力されます。割り込み出力時はINTRB=Lowです。
//// ToDO: internalAddress, dataをRTCのタイマーに合わせて計算。
//  uint8_t internalAddress = 0x00;
//  uint8_t data = 0x00;
//
//  WriteToRtcReg8(internalAddress, data);
//}
//
//void NectisRTC::SetRtcTimerDay(unsigned int day) {
////  アラーム割り込み出力はINTRB端子から出力されます。割り込み出力時はINTRB=Lowです。
//// ToDO: internalAddress, dataをRTCのタイマーに合わせて計算。
//  uint8_t internalAddress = 0x00;
//  uint8_t data = 0x00;
//
//  WriteToRtcReg8(internalAddress, data);
//}
//
//void NectisRTC::EnableRtcTimer() {
//  uint8_t internalAddress = INTERNAL_ADDRESS_CONTROL_REGISTER1_POS;
//  uint8_t data = DATA_ENABLE_INTERRUPT_OR_ALARM;
//
//  WriteToRtcReg8(internalAddress, data);
//}
//
//void NectisRTC::EnableRtcAlarm() {
//  uint8_t internalAddress = INTERNAL_ADDRESS_CONTROL_REGISTER1_POS;
//  uint8_t data = DATA_ENABLE_INTERRUPT_OR_ALARM;
//
//  WriteToRtcReg8(internalAddress, data);
//}
//
//void NectisRTC::ReadSetTimer() {
//  // ToDO: internalAddress, dataをRTCのタイマーに合わせて計算。
//  uint8_t internalAddress = 0x00;
//  uint8_t* data = 0x00;
//
//  ReadFromRtcReg8(internalAddress, data);
//  Serial.printf("The set alarm is: %u", data);
//
//  internalAddress = 0x00;
//  data = 0x00;
//
//  ReadFromRtcReg8(internalAddress, data);
//  Serial.printf("The set constant interrupt is: %u", data);
//}


void NectisRTC::WriteToRtcReg8(uint8_t internalAddress, uint8_t data) {
  uint8_t writeData[2];
  writeData[0] = internalAddress | TRANSFER_FORMAT;
  writeData[1] = data;

  WriteToRtc(writeData, sizeof(writeData));
}

void NectisRTC::ReadFromRtcReg8(uint8_t internalAddress, uint8_t* data) {
  ReadFromRtc(internalAddress, data, 1);
}

void NectisRTC::WriteToRtc(uint8_t* data, int dataSize) {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  Serial.printf("%u\n", data[0]);
  Serial.printf("%u\n", data[1]);

  _RtcWire.beginTransmission(slaveAddress);

  while (dataSize--) {
    _RtcWire.write(*data++);
  }

  _RtcWire.endTransmission();
}

void NectisRTC::ReadFromRtc(uint8_t internalAddress, uint8_t* data, int dataSize) {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;
  uint8_t writeData[2];
  writeData[0] = slaveAddress;
  writeData[1] = internalAddress | TRANSFER_FORMAT;
  WriteToRtc(writeData, sizeof(writeData));
  Serial.printf("%u, %u\n", writeData[0], writeData[1]);

  uint8_t internalRegister = SLAVE_ADDRESS | DATA_TRANSFER_BIT_HIGH;
  writeData[1];
  writeData[0] = internalRegister;
  WriteToRtc(writeData, sizeof(writeData));
  Serial.printf("%u\n", writeData[0]);

  Serial.println(dataSize);

  while (dataSize--) {
    *data++ = _RtcWire.read();
  }

  Serial.printf("%u\n", data);

}


//Wire.requestFrom(2, 6);    // request 6 bytes from slave device #2
//
//while(Wire.available())    // slave may send less than requested
//{
//char c = Wire.read(); // receive a byte as character
//Serial.print(c);         // print the character
//}
