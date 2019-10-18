#include "NectisRTC.h"

// ROLE    : | SLAVE_ADDRESS | DATA_BIT | INTERNAL_ADDRESS | TRANSFER_FORMAT |       DATA      |
// SDA LINE: | 7 6 5 4 3 2 1 |     0    |     7 6 5 4      |     3 2 1 0     | 7 6 5 4 3 2 1 0 |

#define SLAVE_ADDRESS                               (0b00110010 << 1)   // 7bits
#define DATA_WRITE_BIT                              (0b00000000)
#define DATA_READ_BIT                               (0b00000001)

// To write data(seconds) to INTERNAL_ADDRESS_SECOND_COUNTER, use (INTERNAL_ADDRESS_SECOND_COUNTER | WRITE_TRANSFER_FORMAT).
// When ALARM is enabled, INTRB pin is HIGH in every set counter.
#define TRANSFER_FORMAT                             (0x00)

#define INTERNAL_ADDRESS_SECOND_COUNTER_POS         (0x00)
#define INTERNAL_ADDRESS_MINUTE_COUNTER_POS         (0x10)
#define INTERNAL_ADDRESS_HOUR_COUNTER_POS           (0x20)
#define INTERNAL_ADDRESS_DAYOFWEEK_COUNTER_POS      (0x30)
#define INTERNAL_ADDRESS_DAY_COUNTER_POS            (0x40)
#define INTERNAL_ADDRESS_MONTH_COUNTER_POS          (0x50)
#define INTERNAL_ADDRESS_YEAR_COUNTER_POS           (0x60)

#define INTERNAL_ADDRESS_MINUTE_ALARM_POS           (0x80)
#define INTERNAL_ADDRESS_HOUR_ALARM_POS             (0x90)
#define INTERNAL_ADDRESS_DAYOFWEEK_ALARM_POS        (0xA0)

// 曜日レジスタのAW0からAW6は、曜日カウンタ (W4, W2, W1) = (0, 0, 0) ~ (1, 1, 0) に対応します。
// DATA_DAYOFWEEK_COUNTER: (SUN, MON, TUE, WED, THU, FRI, SAT) = (0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7)
// DATA_DAYOFWEEK_ALARM: (SUN, MON, TUE, WED, THU, FRI, SAT) = (1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6)
//
//#define DATA_SECOND_COUNTER                         (—   S40 S20 S10  S8  S4  S2  S1)
//#define DATA_MINUTE_COUNTER                         (—   M40 M20 M10  M8  M4  M2  M1)
//#define DATA_HOUR_COUNTER                           (—   —   H20 H10  H8  H4  H2  H1)
//#define DATA_DAYOFWEEK_COUNTER                      (—   —   —   —    —   W4  W2  W1)
//#define DATA_DAY_COUNTER                            (—   —   D20 D10  D8  D4  D2  D1)
//#define DATA_MONTH_COUNTER                          (—   —   —   MO10 MO8 MO4 MO2 MO1)
//#define DATA_YEAR_COUNTER                           (Y80 Y40 Y20 Y10  Y8  Y4  Y2  Y1)
//
//#define DATA_MINUTE_ALARM                           (— AM40 AM20 AM10 AM8 AM4 AM2 AM1)
//#define DATA_HOUR_ALARM                             (— -    AH20 AH10 AH8 AH4 AH2 AH1)
//#define DATA_DAYOFWEEK_ALARM                        (— AW6  AW5  AW4  AW3 AW2 AW1 AW0)

#define INTERNAL_ADDRESS_CONTROL_REGISTER1_POS      (0xE0)
// アラームを発生させたい時間を設定した後に、イネーブルをオンにします。
// Set the constant interrupt: in every one SECOND/MINUTE/HOUR/MONTH
#define DATA_REGISTER1_MASK                         (0b00000000)
#define DATA_REGISTER1_CONSTANT_INTERRUPT_SECOND    (0b00000100)
#define DATA_REGISTER1_CONSTANT_INTERRUPT_MINUTE    (0b00000101)
#define DATA_REGISTER1_CONSTANT_INTERRUPT_HOUR      (0b00000110)
#define DATA_REGISTER1_CONSTANT_INTERRUPT_MONTH     (0b00000111)
#define DATA_REGISTER1_ENABLE_ALARM                 (0b10000000)

#define DATA_ENABLE_INTERRUPT_OR_ALARM              DATA_REGISTER1_MASK | DATA_REGISTER1_ENABLE_ALARM

#define INTERNAL_ADDRESS_CONTROL_REGISTER2_POS      (0xF0)
#define DATA_REGISTER2_MASK                         (0b00000000)
#define DATA_REGISTER2_24HOUR_CLOCK                 (0b00100000)
#define DATA_REGISTER2_DISABLE_32KHZ_CLOCK_OUTPUT   (0b00001000)


NectisRTC::NectisRTC() : &_RtcWire(NRF_TWIM0, NRF_TWIS0, SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn, RTC_I2C_SDA_PIN, RTC_I2C_SCL_PIN) {

}

void NectisRTC::SetRtcTimer(unsigned int second) {
//  アラーム割り込み出力はINTRB端子から出力されます。割り込み出力時はINTRB=Lowです。
// ToDO: internalAddress, dataをRTCのタイマーに合わせて計算。
  uint8_t internalAddress = 0x00;
  uint8_t data = second;

  WriteToRtcReg8(internalAddress, data);
}

void NectisRTC::EnableRtcTimer() {
  uint8_t internalAddress = INTERNAL_ADDRESS_CONTROL_REGISTER1_POS;
  uint8_t data = DATA_ENABLE_INTERRUPT_OR_ALARM;

  WriteToRtcReg8(internalAddress, data);
}

void NectisRTC::ReadSetTimer() {
  // ToDO: internalAddress, dataをRTCのタイマーに合わせて計算。
  uint8_t internalAddress = 0x00;
  uint8_t data = 0x00;

  ReadFromRtcReg8(internalAddress, data);
  Serial.printf("The set alarm is: %u", data);

  uint8_t internalAddress = 0x00;
  uint8_t data = 0x00;

  ReadFromRtcReg8(internalAddress, data);
  Serial.printf("The set constant interrupt is: %u", data);
}


void NectisRTC::WriteToRtcReg8(uint8_t internalAddress, uint8_t data) {
  uint8_t writeData[2];
  writeData[0] = internalAddress | TRANSFER_FORMAT;
  writeData[1] = data;

  WriteToRtc(writeData, sizeof(writeData));
}

void NectisRTC::ReadFromRtcReg8(uint8_t internalAddress, uint8_t data) {
  uint8_t writeData[1];
  writeData[0] = internalAddress | TRANSFER_FORMAT;
  WriteToRtc(writeData, sizeof(writeData));

  uint8_t readData[1];
  readData[0] = internalAddress | TRANSFER_FORMAT;
  ReadFromRtc(readData, sizeof(readData));
}

void NectisRTC::WriteToRtc(uint8_t* data, int dataSize) {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_WRITE_BIT

  _RtcWire->beginTransmission(slaveAddress);

  while (dataSize--) {
    _RtcWire->write(*data++);
  }

  _RtcWire->endTransmission();
}

void NectisRTC::ReadFromRtc(uint8_t* data, int dataSize) {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_READ_BIT;
  uint8_t readSize = _RtcWire->requestFrom(slaveAddress, dataSize);

  dataSize = int(readSize);

  _RtcWire->beginTransmission(slaveAddress);

  while (dataSize--)
  {
    *data++ = _RtcWire->read();
  }

  _RtcWire->endTransmission();
}


//Wire.requestFrom(2, 6);    // request 6 bytes from slave device #2
//
//while(Wire.available())    // slave may send less than requested
//{
//char c = Wire.read(); // receive a byte as character
//Serial.print(c);         // print the character
//}
