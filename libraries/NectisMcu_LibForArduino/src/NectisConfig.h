#pragma once


// CFG_DEBUG == 0 => (Release)
// CFG_DEBUG == 1 => (Error Message)
// CFG_DEBUG == 2 => (Full Debug)
// CFG_DEBUG == 3 => (Segger SystemView)

#if CFG_DEBUG >= 2
  #define NECTIS_DEBUG
#endif //CFG_DEBUG
