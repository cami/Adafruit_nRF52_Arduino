#pragma once
#include <stdint.h>

namespace utils {
  char *ConvertUint8DecimalToHex(uint8_t, int);
  char *ConvertUint16DecimalToHex(uint16_t, int);
  char *ConvertUint32DecimalToHex(uint32_t, int);
  char *ConvertIntDecimalToHex(int, int);
  char *ConvertFloatDecimalToHex(float const, int);

  unsigned int GetDataDigits(unsigned int);
  char *ConvertIntoBinary(char*, uint8_t, unsigned int);
  char *ConvertIntoBinary(char*, uint16_t, unsigned int);
  char *ConvertIntoBinary(char*, uint32_t, unsigned int);
  char *ConvertIntoBinary(char*, int, unsigned int);
  char *ConvertIntoBinary(char*, float const, unsigned int);
}
