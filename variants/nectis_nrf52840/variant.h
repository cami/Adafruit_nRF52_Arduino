/*
 Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
 Copyright (c) 2016 Sandeep Mistry All right reserved.
 Copyright (c) 2018, Adafruit Industries (adafruit.com)
 Copyright (c) 2019, CAMI&Co. All rights reserved.


 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef NECTIS
#define NECTIS

/** Master clock frequency */
#define VARIANT_MCK                 (64000000ul)

#define USE_LFXO      // Board uses 32khz crystal for LF
// define USE_LFRC    // Board uses RC for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*
 * Analog pins
 */
#define PIN_A0                      (2)
#define PIN_A1                      (3)
#define PIN_A2                      (4)
#define PIN_A3                      (5)
#define PIN_A4                      (28)
#define PIN_A5                      (29)
#define PIN_A6                      (30)
#define PIN_A7                      (31)

#define ADC_RESOLUTION            (10)

// Other pins
#define PIN_AREF                    (2)
#define PIN_DFU                     (35)

#define PIN_NFC1                    (9)     // NFC電源側
#define PIN_NFC2                    (10)    // NFCグラウンド側

/*
 * Serial interfaces
 */
#define PIN_SERIAL_RX               (GROVE_UART_RX_PIN)
#define PIN_SERIAL_TX               (GROVE_UART_TX_PIN)

//#define PIN_SERIAL2_RX      (8)
//#define PIN_SERIAL2_TX      (6)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT      (1)

#define PIN_SPI_MISO              (21)
#define PIN_SPI_MOSI              (20)
#define PIN_SPI_SCK               (19)
#define PIN_SPI_CS                (24)

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT       (1)

#define PIN_WIRE_SDA                (GROVE_I2C_SDA_PIN)
#define PIN_WIRE_SCL                (GROVE_I2C_SCL_PIN)

/*
 * QSPI interface for external flash
 */
#define PIN_QSPI_SCK                (19)    // Quad SPIクロック, equals to PIN_QSPI_SCLK
#define PIN_QSPI_CS                 (24)    // Quad SPIチップセレクト
#define PIN_QSPI_IO0                (20)    // Quad SPIデータ入出力
#define PIN_QSPI_IO1                (21)    // Quad SPIデータ入出力
#define PIN_QSPI_IO2                (22)    // Quad SPIデータ入出力
#define PIN_QSPI_IO3                (23)    // Quad SPIデータ入出力

#define PIN_QSPI_DATA0              PIN_QSPI_IO0
#define PIN_QSPI_DATA1              PIN_QSPI_IO1
#define PIN_QSPI_DATA2              PIN_QSPI_IO2
#define PIN_QSPI_DATA3              PIN_QSPI_IO3

// Number of pins defined in PinDescription array
#define PINS_COUNT                  (48)
#define NUM_DIGITAL_PINS            (48)
#define NUM_ANALOG_INPUTS           (6)
#define NUM_ANALOG_OUTPUTS          (0)

// LEDs
#define LED_BLUE                    (33)    // Indicator_LED1
#define LED_RED                     (34)    // Indicator_LED2

#define PIN_LED1                    LED_BLUE
#define PIN_LED2                    LED_RED

#define LED_BUILTIN                 LED_BLUE
#define LED_CONN                    LED_RED

#define LED_STATE_ON                (0)     // State when LED is litted

#define BATTERY_VOLTAGE_PIN         (A0)
#define USB_VOLTAGE_PIN             (A1)
#define BATTERY_LEVEL_ENABLE_PIN    (45)

#define MODULE_PWR_PIN              (36)    // Power Supply to the BG96 and Grove sensors
#define MODULE_PWRKEY_PIN           (42)    // Turn On/Off BG96
#define GROVE_VCCB_PIN              (25)    // GROVE_PWR

#define MODULE_UART_CORE            (0)     // USART2 => USART1
//#define MODULE_UART_CORE          (1)     // USART2 => USART1
#define MODULE_UART_RX_PIN          (7)     // BG96への送信データ, BG96_RXD
#define MODULE_UART_TX_PIN          (6)     // BG96からの受信データ, BG96_TXD
#define MODULE_RTS_PIN              (26)    // BG96への送信要求, BG96_CTS
#define MODULE_CTS_PIN              (27)    // BG96からの送信許可, BG96_RTS
#define MODULE_DTR_PIN              (44)    // BG96のデータ端末レディ, BG96_DTR
#define MODULE_RESET_PIN            (43)    // BG96のリセット, BG96_RESET
#define MODULE_STATUS_PIN           (37)    // BG96のステータス, BG96_STATUS
#define BG96_AP_READY               (39)    // BG96のAP_READY

#define CRYSTAL_XL1                 (0)
#define CRYSTAL_XL2                 (1)

#define GROVE_ANALOG_1_1            (4)     // Analog in/out, GROVE_GPIO_1_1
#define GROVE_ANALOG_1_2            (5)     // Analog in/out, GROVE_GPIO_1_2
#define GROVE_ANALOG_2_1            (28)    // Analog in/out, GROVE_GPIO_2_1
#define GROVE_ANALOG_2_2            (29)    // Analog in/out, GROVE_GPIO_2_2
#define GROVE_ANALOG_3_1            (30)    // Analog in/out, GROVE_GPIO_3_1
#define GROVE_ANALOG_3_2            (31)    // Analog in/out, GROVE_GPIO_3_2
//#define GROVE_I2C_CORE		    (1)
#define GROVE_I2C_SCL_PIN           (12)    // I2C, GROVE_GPIO_4_1
#define GROVE_I2C_SDA_PIN           (11)    // I2C, GROVE_GPIO_4_2
#define GROVE_UART_CORE             (0)     // USART1
#define GROVE_UART_RX_PIN           (13)    // UART, GROVE_GPIO_5_1
#define GROVE_UART_TX_PIN           (14)    // UART, GROVE_GPIO_5_2
#define GROVE_GPIO_6_1              (15)    // GPIO, GROVE_GPIO_6_1
#define GROVE_GPIO_6_2              (16)    // GPIO, GROVE_GPIO_6_2

//#define DEBUG_UART_CORE           (2)   // USART3
//#define DEBUG_UART_TX_PIN         MODULE_UART_TX_PIN
//#define DEBUG_UART_RX_PIN         MODULE_UART_RX_PIN


static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

static const uint8_t AREF = PIN_AREF;

static const uint8_t SS = PIN_SPI_CS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;


// On-board QSPI Flash
// If EXTERNAL_FLASH_DEVICES is not defined, all supported devices will be used
#define EXTERNAL_FLASH_DEVICES   GD25Q16C

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
