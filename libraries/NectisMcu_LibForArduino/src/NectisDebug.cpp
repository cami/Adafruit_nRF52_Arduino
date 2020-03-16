#include "NectisDebug.h"
#include "Uart.h"

#ifdef NECTIS_DEBUG

void NectisDebug::Print(const char *str) {
  Serial.print(str);
}

void NectisDebug::Println(const char *str) {
  Print(str);
  Print("\r\n");
}

#endif  // NECTIS_DEBUG
