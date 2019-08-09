#include "NectisCellularOtaDfu.h"
#include "nrf_power.h"

#define DFU_MAGIC_RESET               0UL
#define DFU_MAGIC_SERIAL_ONLY_RESET   0x4e
#define DFU_MAGIC_UF2_RESET           0x57
#define DFU_MAGIC_OTA_RESET           0xA8

NectisOtaDfu::NectisOtaDfu() {
}

void NectisOtaDfu::ResetRegistry() {
    nrf_power_gpregret_set(DFU_MAGIC_SERIAL_ONLY_RESET);
}

void NectisOtaDfu::EnableButtonlessDfu() {
}

void NectisOtaDfu::EnterOtaDfuMode() {
//  ToDO: bootloader settingsのバージョンによって、条件分岐させる。
//  ToDO: 1回目はOTA-DFUモードに入らず、2回目はOTA-DFUモードに入れるようにする。
    nrf_power_gpregret_set(DFU_MAGIC_OTA_RESET);
    nrf_power_gpregret2_set(0);
    
    NVIC_SystemReset();
}
