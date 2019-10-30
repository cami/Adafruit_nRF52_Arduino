#include "NectisRTC.h"

//INTERNAL_ADDRESS = INTERNAL_ADDRESS_SECOND_COUNTER_POS = 0b0000
// Write
// ROLE    : | SLAVE_ADDRESS | R/W | INTERNAL_ADDRESS | TRANSFER_FORMAT |            DATA              |
// SDA BIT : | 0 1 1 0 0 1 0 |  0  |     0 0 0 0      |     0 0 0 0     | — S40 S20 S10 S8  S4  S2  S1 |
// SDA LINE: | 7 6 5 4 3 2 1 |  0  |     7 6 5 4      |     3 2 1 0     | 7 6   5   4   3   2   1   0  |

// Read
// ROLE    : | SLAVE_ADDRESS | R/W | INTERNAL_ADDRESS | TRANSFER_FORMAT | SLAVE_ADDRESS | R/W |            DATA              |
// SDA BIT : | 0 1 1 0 0 1 0 |  0  |     0 0 0 0      |     0 0 0 0     | 0 1 1 0 0 1 0 |  1  | — S40 S20 S10 S8  S4  S2  S1 |
// SDA LINE: | 7 6 5 4 3 2 1 |  0  |     7 6 5 4      |     3 2 1 0     | 7 6 5 4 3 2 1 |  1  | 7 6   5   4   3   2   1   0  |


const uint8_t SLAVE_ADDRESS =                             0b00110010;   // 7bits
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
const uint8_t DATA_REGISTER1_MASK =                       0xFF;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_SECOND =  0b00000100;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_MINUTE =  0b00000101;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_HOUR =    0b00000110;
const uint8_t DATA_REGISTER1_CONSTANT_INTERRUPT_MONTH =   0b00000111;
const uint8_t DATA_REGISTER1_ENABLE_ALARM =               0b10000000;
const uint8_t DATA_REGISTER1_DISABLE_ALARM_MASK =         0b10000000;

const uint8_t INTERNAL_ADDRESS_CONTROL_REGISTER2_POS =    0xF0;
const uint8_t DATA_REGISTER2_24HOUR_CLOCK =               0b00100000;


NectisRTC::NectisRTC() : _RtcWire(NRF_TWIM0, NRF_TWIS0, SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn, RTC_I2C_SDA_PIN, RTC_I2C_SCL_PIN){

}

uint16_t NectisRTC::ConvertBcdToDecimal(uint16_t bcd) {
  // 0 <= bcd <= 99
  // このRTCは、2019年を表したい場合、19をINTERNAL_ADDRESS_YEAR_COUNTER_POSにセットする。
  // Input : 0001 1001
  // Output:    1    9
  uint8_t DecimalOnesPlace = bcd & 0x0F;
  uint8_t DecimalTensPlace = (bcd >> 4) & 0x0F;

//  Serial.printf("DecimalTensPlace: %u\n", DecimalTensPlace);
//  Serial.printf("DecimalOnesPlace: %u\n", DecimalOnesPlace);

  uint16_t decimal = DecimalTensPlace * 10 + DecimalOnesPlace;

  return decimal;
}

uint16_t NectisRTC::ConvertDecimalToBcd(uint16_t decimal) {
  // 0 <= decimal <= 99
  // このRTCは、2019年を表したい場合、19をINTERNAL_ADDRESS_YEAR_COUNTER_POSにセットする。
  // Input :    1    9
  // Output: 0001 1001
  uint8_t BcdOnesPlace = (decimal % 10) & 0x0F;
  uint8_t BcdTensPlace = uint16_t(decimal / 10) & 0x0F;

//  Serial.printf("BcdTensPlace: %01x\n", BcdTensPlace);
//  Serial.printf("BcdOnesPlace: %01x\n", BcdOnesPlace);

  uint16_t bcd = (BcdTensPlace << 4) | BcdOnesPlace;

  return bcd;
}

void NectisRTC::GetCurrentTime(struct tm *tim, bool jst=true) {
  delay(2500);
// Get time in JST.
  while (!_Nectis.IsTimeGot(tim, jst)) {
    delay(2500);
  }
}

void NectisRTC::BeginRtc() {
  _RtcWire.begin();
}

void NectisRTC::EndRtc() {
  _RtcWire.end();
}

void NectisRTC::Init() {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;
  const uint8_t resetBits = 0x00;
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER1_POS | TRANSFER_FORMAT, resetBits);
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER2_POS | TRANSFER_FORMAT, resetBits);

  ConfigRtc24HourDisplay();

  uint8_t calender[7];
  ReadCalender(calender);

  uint8_t year = calender[0];
  uint8_t hour = calender[3];
  Serial.println(year);
  Serial.println(hour);

  // year==0 の時は、RTCに時刻がセットされていないので、BG96から取得してセットする。
  if (year == 0 | 24 <= hour) {
    SetCurrentTimeToRtc();
  }
}

void NectisRTC::ConfigRtc24HourDisplay() {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER2_POS | TRANSFER_FORMAT, DATA_REGISTER2_24HOUR_CLOCK);
}

void NectisRTC::SetCurrentTimeToRtc() {
  Serial.println("### Get the current time from BG96.");

  _Nectis.Bg96Begin();
  _Nectis.InitLteM();

  //    Get the current time.
  struct tm currentTime;
  char currentTimeStr[64];

  GetCurrentTime(&currentTime, true);
  strftime(currentTimeStr, sizeof(currentTimeStr), "%y/%m/%d %H:%M:%S %w", &currentTime);

//  Serial.printf("tm_year: %d\n", (currentTime.tm_year - 100));
//  Serial.printf("tm_mon: %d\n", (currentTime.tm_mon + 1));
//  Serial.printf("tm_mday: %d\n", currentTime.tm_mday);
//  Serial.printf("tm_hour: %d\n", currentTime.tm_hour);
//  Serial.printf("tm_min: %d\n", currentTime.tm_min);
//  Serial.printf("tm_sec: %d\n", currentTime.tm_sec);
//  Serial.printf("tm_wday: %d\n", currentTime.tm_wday);

  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  // tim->tm_year = atoi(&parameter[1]) - 1900
  // tim->tm_mon = atoi(&parameter[6]) - 1
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_SECOND_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_sec));
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_MINUTE_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_min));
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_HOUR_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_hour));
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_DAY_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_mday));
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_MONTH_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_mon + 1));
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_YEAR_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_year - 100));

  // const uint8_t DATA_DAYOFWEEK_COUNTER                      (—   —   —   —    —   W4  W2  W1)
  // DATA_DAYOFWEEK_COUNTER: SUN=0, MON=1, TUE=2, WED=3, THU=4, FRI=5, SAT=6
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_DAYOFWEEK_COUNTER_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(currentTime.tm_wday));

  _Nectis.Bg96TurnOff();
  _Nectis.Bg96End();

  Serial.print("JST:");
  Serial.println(currentTimeStr);

  Serial.println("### Set the current time to RTC.");
}

void NectisRTC::ReadCalender() {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  // calender = [year, month, day, hour, minute, second, dayofweek]
  uint8_t calender[8];
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_YEAR_COUNTER_POS | TRANSFER_FORMAT, &calender[0]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_MONTH_COUNTER_POS | TRANSFER_FORMAT, &calender[1]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_DAY_COUNTER_POS | TRANSFER_FORMAT, &calender[2]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_HOUR_COUNTER_POS | TRANSFER_FORMAT, &calender[3]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_MINUTE_COUNTER_POS | TRANSFER_FORMAT, &calender[4]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_SECOND_COUNTER_POS | TRANSFER_FORMAT, &calender[5]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_DAYOFWEEK_COUNTER_POS | TRANSFER_FORMAT, &calender[6]);

  Serial.printf("Set Calender: 20%02d/%02d/%02d %02d:%02d:%02d %02d\n",
                ConvertBcdToDecimal(calender[0]), ConvertBcdToDecimal(calender[1]), ConvertBcdToDecimal(calender[2]),
                ConvertBcdToDecimal(calender[3]), ConvertBcdToDecimal(calender[4]), ConvertBcdToDecimal(calender[5]),
                ConvertBcdToDecimal(calender[6])
  );
  Serial.flush();
}

void NectisRTC::ReadCalender(uint8_t calenderDecimal[7]) {
  uint8_t calender[7];

  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  // calender = [year, month, day, hour, minute, second, dayofweek]
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_YEAR_COUNTER_POS | TRANSFER_FORMAT, &calender[0]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_MONTH_COUNTER_POS | TRANSFER_FORMAT, &calender[1]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_DAY_COUNTER_POS | TRANSFER_FORMAT, &calender[2]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_HOUR_COUNTER_POS | TRANSFER_FORMAT, &calender[3]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_MINUTE_COUNTER_POS | TRANSFER_FORMAT, &calender[4]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_SECOND_COUNTER_POS | TRANSFER_FORMAT, &calender[5]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_DAYOFWEEK_COUNTER_POS | TRANSFER_FORMAT, &calender[6]);

  for (uint8_t i = 0; i < sizeof(calender); i++) {
    calenderDecimal[i] = ConvertBcdToDecimal(calender[i]);
  }
}

void NectisRTC::SetAlarm(const char* tableTime[], uint16_t tableTimeSize, const uint8_t tableDayofweek, uint16_t tableDayofweekSize) {
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  for (int i = 0; i < tableTimeSize; i++) {
    uint16_t alarmHour = uint16_t(((tableTime[i])[0] - 0x30) * 10 + ((tableTime[i])[1] - 0x30));
    uint16_t alarmMinute = uint16_t(((tableTime[i])[3] - 0x30) * 10 + ((tableTime[i])[4] - 0x30));

    WriteReg8(slaveAddress, INTERNAL_ADDRESS_HOUR_ALARM_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(alarmHour));
    WriteReg8(slaveAddress, INTERNAL_ADDRESS_MINUTE_ALARM_POS | TRANSFER_FORMAT, ConvertDecimalToBcd(alarmMinute));
    WriteReg8(slaveAddress, INTERNAL_ADDRESS_DAYOFWEEK_ALARM_POS | TRANSFER_FORMAT, tableDayofweek);
  }
  EnableRtcAlarm(slaveAddress);

  delay(100);
  uint8_t setAlarm[3];
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_HOUR_ALARM_POS | TRANSFER_FORMAT, &setAlarm[0]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_MINUTE_ALARM_POS | TRANSFER_FORMAT, &setAlarm[1]);
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_DAYOFWEEK_ALARM_POS | TRANSFER_FORMAT, &setAlarm[2]);
  Serial.printf("Set alarm: %02u:%02u %01x\n", ConvertBcdToDecimal(setAlarm[0]), ConvertBcdToDecimal(setAlarm[1]), ConvertBcdToDecimal(setAlarm[2]));
}

void NectisRTC::SetConstantInterruptByEveryMinute() {
  Serial.println("Set the constant interrupt by every one minute.");
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  uint8_t controlRegister1[1];
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER1_POS | TRANSFER_FORMAT, &controlRegister1[0]);
  uint8_t controlRegister1DisableAlarm = controlRegister1[0] ^ DATA_REGISTER1_DISABLE_ALARM_MASK;

  uint8_t constantInterruptByEveryMinute = DATA_REGISTER1_CONSTANT_INTERRUPT_MINUTE | controlRegister1DisableAlarm;
  WriteReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER1_POS | TRANSFER_FORMAT, constantInterruptByEveryMinute);
}

void NectisRTC::SetConstantInterruptByEveryHour() {
  Serial.println("Set the constant interrupt by every one hour.");
  uint8_t slaveAddress = SLAVE_ADDRESS | DATA_TRANSFER_BIT_LOW;

  uint8_t controlRegister1[1];
  ReadReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER1_POS | TRANSFER_FORMAT, &controlRegister1[0]);
  uint8_t controlRegister1DisableAlarm = controlRegister1[0] ^ DATA_REGISTER1_DISABLE_ALARM_MASK;

  uint8_t constantInterruptByEveryMinute = DATA_REGISTER1_CONSTANT_INTERRUPT_HOUR | controlRegister1DisableAlarm;

  WriteReg8(slaveAddress, INTERNAL_ADDRESS_CONTROL_REGISTER1_POS | TRANSFER_FORMAT, constantInterruptByEveryMinute);
}

void NectisRTC::EnableRtcAlarm(uint8_t slaveAddress) {
  uint8_t slaveRegister = INTERNAL_ADDRESS_CONTROL_REGISTER1_POS | TRANSFER_FORMAT;
  uint8_t data = DATA_REGISTER1_ENABLE_ALARM;

  WriteReg8(slaveAddress, slaveRegister, data);
}

void NectisRTC::Write(uint8_t slaveAddress, const uint8_t* data, int dataSize) {
  BeginRtc();

  _RtcWire.beginTransmission(slaveAddress);
  while (dataSize > 0) {
    _RtcWire.write(*data++);
    dataSize--;
  }
  _RtcWire.endTransmission(true);

  EndRtc();
}

int NectisRTC::Read(uint8_t slaveAddress, const uint8_t* slaveRegister, uint8_t* data, int dataSize) {
  int tmpReadSize = dataSize;

  BeginRtc();

  _RtcWire.beginTransmission(slaveAddress);
  while (dataSize > 0) {
    _RtcWire.write(*slaveRegister);
    dataSize--;
  }
  _RtcWire.endTransmission(false);

  auto readSize = _RtcWire.requestFrom(slaveAddress, tmpReadSize);

  while (readSize > 0) {
    *data++ = _RtcWire.read();
    readSize--;
  }
  _RtcWire.endTransmission(true);

  EndRtc();

  return readSize;
}

void NectisRTC::WriteReg8(uint8_t slaveAddress, uint8_t reg, uint8_t data) {
  uint8_t writeData[2];
  writeData[0] = reg;
  writeData[1] = data;

  Write(slaveAddress, writeData, sizeof(writeData));
}

int NectisRTC::ReadReg8(uint8_t slaveAddress, uint8_t reg, uint8_t* data) {
  uint8_t writeData[1];
  writeData[0] = reg;

  return Read(slaveAddress, writeData, data, 1);
}

