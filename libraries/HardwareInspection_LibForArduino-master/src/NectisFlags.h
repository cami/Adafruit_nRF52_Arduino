#pragma once

#include <stdint.h>

// Set Relay-Pin HIGH for U1, U2,..., U8
// For POWER_SUPPLY_RELAY_PIN
const uint16_t POWER_SUPPLY_NONE_HIGH =  (0);
const uint16_t U9_HIGH =    (1 << 0);
const uint16_t U3_HIGH =    (1 << 1);
const uint16_t U4_HIGH =    (1 << 2);
const uint16_t U5_HIGH =    (1 << 3);
const uint16_t U6_HIGH =    (1 << 4);
const uint16_t U7_HIGH =    (1 << 5);
const uint16_t U8_HIGH =    (1 << 6);
// For ACTIVATE_RELAY_PIN
const uint16_t ACTIVATE_NONE_HIGH =  (1 << 7);
const uint16_t U2_HIGH =    (1 << 8);


const uint16_t POWER_SUPPLY_RELAY_PIN_5V0 =     POWER_SUPPLY_NONE_HIGH;         // HIGH => None,        LOW => U2
const uint16_t POWER_SUPPLY_RELAY_PIN_3V7 =     U2_HIGH;                        // HIGH => U2,          LOW => None

const uint16_t DEACTIVATE_USB_PIN =             U9_HIGH;                        // HIGH => U9,          LOW => None

const uint16_t ACTIVATE_RELAY_PIN_5V0 =         U3_HIGH | U6_HIGH | U8_HIGH;    // HIGH => U3, U6, U8,  LOW => None
const uint16_t ACTIVATE_RELAY_PIN_4V5 =         U6_HIGH | U8_HIGH;              // HIGH => U6, U8,      LOW => U3
const uint16_t ACTIVATE_RELAY_PIN_4V2 =         U4_HIGH | U8_HIGH;              // HIGH => U4, U8,      LOW => U6
const uint16_t ACTIVATE_RELAY_PIN_3V8 =         U8_HIGH;                        // HIGH => U8,          LOW => U4, U6
const uint16_t ACTIVATE_RELAY_PIN_G3V3 =        U5_HIGH | U7_HIGH;              // HIGH => U5, U7,      LOW => U8
const uint16_t ACTIVATE_RELAY_PIN_3V3 =         U7_HIGH;                        // HIGH => U7,          LOW => U5, U8
const uint16_t ACTIVATE_RELAY_PIN_1V8 =         ACTIVATE_NONE_HIGH;             // HIGH => None,        LOW => U7, U8
//const uint16_t ACTIVATE_RELAY_PIN_DFU_SW =     (1 << 1);
//const uint16_t ACTIVATE_RELAY_PIN_SWD_RESET =  (1 << 1);

const uint16_t MASK_RELAY_HIGH_PIN = 0xffff;


const uint16_t A0_INPUT =        (1 << 0);
const uint16_t A1_INPUT =        (1 << 1);
const uint16_t A2_INPUT =        (1 << 2);
const uint16_t A3_INPUT =        (1 << 3);
const uint16_t A4_INPUT =        (1 << 4);
const uint16_t A5_INPUT =        (1 << 5);
const uint16_t A6_INPUT =        (1 << 6);
const uint16_t A7_INPUT =        (1 << 7);

const uint16_t GPIO_4_1_INPUT =  (1 << 0);
const uint16_t GPIO_4_2_INPUT =  (1 << 1);
const uint16_t GPIO_5_1_INPUT =  (1 << 2);
const uint16_t GPIO_5_2_INPUT =  (1 << 3);
const uint16_t GPIO_6_1_INPUT =  (1 << 4);
const uint16_t GPIO_6_2_INPUT =  (1 << 5);

const uint16_t GPIO_4_1_HIGH =   (1 << 6);
const uint16_t GPIO_4_2_HIGH =   (1 << 7);
const uint16_t GPIO_5_1_HIGH =   (1 << 8);
const uint16_t GPIO_5_2_HIGH =   (1 << 9);
const uint16_t GPIO_6_1_HIGH =   (1 << 10);
const uint16_t GPIO_6_2_HIGH =   (1 << 11);

const uint16_t HIGH_4_2_N_READ_4_1 =    GPIO_4_2_HIGH | GPIO_4_1_INPUT;
const uint16_t HIGH_4_1_N_READ_4_2 =    GPIO_4_1_HIGH | GPIO_4_2_INPUT;
const uint16_t HIGH_5_2_N_READ_5_1 =    GPIO_5_2_HIGH | GPIO_5_1_INPUT;
const uint16_t HIGH_5_1_N_READ_5_2 =    GPIO_5_1_HIGH | GPIO_5_2_INPUT;
const uint16_t HIGH_6_2_N_READ_6_1 =    GPIO_6_2_HIGH | GPIO_6_1_INPUT;
const uint16_t HIGH_6_1_N_READ_6_2 =    GPIO_6_1_HIGH | GPIO_6_2_INPUT;

const uint16_t LOW_4_2_N_READ_4_1 =     GPIO_4_1_INPUT;   // Needs to be initialized with InitGpioPins()
const uint16_t LOW_4_1_N_READ_4_2 =     GPIO_4_2_INPUT;   // Needs to be initialized with InitGpioPins()
const uint16_t LOW_5_2_N_READ_5_1 =     GPIO_5_1_INPUT;   // Needs to be initialized with InitGpioPins()
const uint16_t LOW_5_1_N_READ_5_2 =     GPIO_5_2_INPUT;   // Needs to be initialized with InitGpioPins()
const uint16_t LOW_6_2_N_READ_6_1 =     GPIO_6_1_INPUT;   // Needs to be initialized with InitGpioPins()
const uint16_t LOW_6_1_N_READ_6_2 =     GPIO_6_2_INPUT;   // Needs to be initialized with InitGpioPins()

const uint16_t MASK_ANALOG_PIN_READ =   0xffff;
const uint16_t MASK_GPIO_PIN_READ =     0xffff;


class NectisFlags {
public:
  NectisFlags();
  void ClearFlags(uint16_t *flags);
};
