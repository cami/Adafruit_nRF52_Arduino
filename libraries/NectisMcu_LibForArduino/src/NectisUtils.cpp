#include "NectisUtils.h"
#include <Arduino.h>


namespace utils {

char hexConvertedFromDecimal[16];
char hexConvertedFromFloat[sizeof(float) + 1];


/*
 * Helper functions
 */
char *ConvertUint8DecimalToHex(uint8_t decimal, int byte_size) {
  // The last index of post_data is filled with 0x00 for print function.
  memset(&hexConvertedFromDecimal[0], 0x00, sizeof(hexConvertedFromDecimal));

  for (int i = 0; i < byte_size; i++) {
    // 16進数に変換し、1バイトずつ配列を埋めていく
    hexConvertedFromDecimal[i] = (decimal >> (8 * ((byte_size - 1) - i))) & 0xff;
  }
  return &hexConvertedFromDecimal[0];
}

char *ConvertUint16DecimalToHex(uint16_t decimal, int byte_size) {
  // The last index of post_data is filled with 0x00 for print function.
  memset(&hexConvertedFromDecimal[0], 0x00, sizeof(hexConvertedFromDecimal));

  for (int i = 0; i < byte_size; i++) {
    // 16進数に変換し、1バイトずつ配列を埋めていく
    hexConvertedFromDecimal[i] = (decimal >> (8 * ((byte_size - 1) - i))) & 0xff;
  }
  return &hexConvertedFromDecimal[0];
}

char *ConvertUint32DecimalToHex(uint32_t decimal, int byte_size) {
  // The last index of post_data is filled with 0x00 for print function.
  memset(&hexConvertedFromDecimal[0], 0x00, sizeof(hexConvertedFromDecimal));

  for (int i = 0; i < byte_size; i++) {
    // 16進数に変換し、1バイトずつ配列を埋めていく
    hexConvertedFromDecimal[i] = (decimal >> (8 * ((byte_size - 1) - i))) & 0xff;
  }
  return &hexConvertedFromDecimal[0];
}

char *ConvertIntDecimalToHex(int decimal, int byte_size) {
  // The last index of post_data is filled with 0x00 for print function.
  memset(&hexConvertedFromDecimal[0], 0x00, sizeof(hexConvertedFromDecimal));

  for (int i = 0; i < byte_size; i++) {
    // 16進数に変換し、1バイトずつ配列を埋めていく
    hexConvertedFromDecimal[i] = (decimal >> (8 * ((byte_size - 1) - i))) & 0xff;
  }
  return &hexConvertedFromDecimal[0];
}

char *ConvertFloatDecimalToHex(float const decimal, int byte_size) {
  // The last index of post_data is filled with 0x00 for print function.
  memset(&hexConvertedFromFloat[0], 0x00, sizeof(hexConvertedFromFloat));
  // Serial.printf("ConvertDecimalToHex decimal: %u\n", decimal);

  union {
    float decimalFloat;
    int decimalInt;
  } bit;
  bit.decimalFloat = decimal;

  /* float型(32ビット)の内部構造（IEEE754）
   * 符号(sign)       : 1ビット目
   * 指数部(exponent) : 2ビット目〜9ビット目
   * 仮数部(mantissa) : 10ビット目〜32ビット目
   */
  // uint8_t signSize = 1;
  // uint8_t exponentSize = 8;
  // uint8_t mantissaSize = 23;
  // uint8_t floatBitSize = signSize + exponentSize + mantissaSize;
  
  for (uint8_t i = 0; i < sizeof(float); i++) {
    // 16進数に変換し、1バイトずつ配列を埋めていく
    hexConvertedFromFloat[i] = (bit.decimalInt >> (8 * ((sizeof(float) - 1) - i))) & 0xff;
  }

  return &hexConvertedFromFloat[0];
}

unsigned int GetDataDigits(unsigned int data) {
  // Copy the original data to calculate digits in order not to affect the original value.
  unsigned int data_to_calc_digit = data;
  unsigned int data_digit_hex = 0;

  if (data_to_calc_digit == 0) {
    data_digit_hex = 1;
  }

  // Calculating the digits of data in hexadecimal.
  // 2 digits = 1 byte
  // Calculating the bytes of the post data
  while (data_to_calc_digit != 0) {
    data_to_calc_digit /= 16;
    data_digit_hex++;
  }
  unsigned int size_of_post_data = (int)(ceil((double) data_digit_hex / 2));

  return size_of_post_data;
}

char *ConvertIntoBinary(char *binary, uint8_t data, unsigned int size) {
  memset(&binary[0], 0x00, size);
  memcpy(&binary[0], ConvertUint8DecimalToHex(data, size), size);

  return binary;
}

char *ConvertIntoBinary(char *binary, uint16_t data, unsigned int size) {
  memset(&binary[0], 0x00, size);
  memcpy(&binary[0], ConvertUint16DecimalToHex(data, size), size);

  return binary;
}

char *ConvertIntoBinary(char *binary, uint32_t data, unsigned int size) {
  memset(&binary[0], 0x00, size);
  memcpy(&binary[0], ConvertUint32DecimalToHex(data, size), size);

  return binary;
}

char *ConvertIntoBinary(char *binary, int data, unsigned int size) {
  memset(&binary[0], 0x00, size);
  memcpy(&binary[0], ConvertIntDecimalToHex(data, size), size);

  return binary;
}

char *ConvertIntoBinary(char *PostDataBinary, float const data, unsigned int data_length) {
  memset(&PostDataBinary[0], 0x00, data_length);
  memcpy(&PostDataBinary[0], ConvertFloatDecimalToHex(data, data_length), data_length);

  return PostDataBinary;
}

} // namespace utils