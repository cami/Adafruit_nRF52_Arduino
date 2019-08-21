//
// Created by NaotoFujihiro on 2019-08-08.
//

#ifndef NRF52840_LIBFORBG96_NECTISCELLULARCONFIG_H
#define NRF52840_LIBFORBG96_NECTISCELLULARCONFIG_H

#endif //NRF52840_LIBFORBG96_NECTISCELLULARCONFIG_H

#include <Arduino.h>

#undef max /* FIXME workaround: https://stackoverflow.com/questions/41093090/esp8266-error-macro-min-passed-3-arguments-but-takes-just-2 */
#undef min /* FIXME workaround: https://stackoverflow.com/questions/41093090/esp8266-error-macro-min-passed-3-arguments-but-takes-just-2 */

// CFG_DEBUG == 2 => (Full Debug)
// CFG_DEBUG == 3 => (Segger SystemView)
#if CFG_DEBUG >= 2
  #define NECTIS_DEBUG
#endif //CFG_DEBUG >= 2
