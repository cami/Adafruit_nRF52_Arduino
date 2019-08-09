#include "NectisCellular.h"
#include "WioCellLibforArduino.h"
#include "WioCellularHardware.h"
#include <Uart.h>
#include "NectisCellularHardwareTest.h"

#define VUSB_ADC_VALUE_PER_LSB      (2.929688F)     // 3.0V ADC range and 10-bit ADC resolution = 3000mV/1024
#define VBAT_ADC_VALUE_PER_LSB      (1.171875F)     // 1.2V ADC range and 10-bit ADC resolution = 1200mV/1024
#define GROVE_ADC_VALUE_PER_LSB     (3.515625F)     // 3.6V ADC range and 10-bit ADC resolution = 3600mV/1024

#define VUSB_DIVIDER                (0.5F)          // 220kOhm / (220kOhm + 220kOhm)
#define VBAT_DIVIDER                (0.25F)         // From IC: RP124N334E
#define GROVE_ADC_DIVIDER           (0.916667F)     // 3.6V / 3.3V

#define AD_USB                      USB_VOLTAGE_PIN
#define AD_LDO1                     BATTERY_VOLTAGE_PIN
#define AD1                         PIN_A2
#define AD2                         PIN_A3
#define AD3                         PIN_A4
#define AD4                         PIN_A5
#define AD5                         PIN_A6
#define AD6                         PIN_A7


NectisHardwareTest::NectisHardwareTest() {
}


void NectisHardwareTest::ReadAdcValues(void) {
    uint32_t rawAdcValues[8];
    memset(&rawAdcValues[0], 0x00, sizeof(rawAdcValues));
    float adcValues[8];
    memset(&adcValues[0], 0x00, sizeof(adcValues));
    
    uint32_t analogPinsToRead[8] = {AD_USB, AD_LDO1, AD1, AD2, AD3, AD4, AD5, AD6};
    
//    Read AD_USB Value
    // Set the analog reference to 3.0V (default = 3.6V)
    analogReference(AR_INTERNAL_3_0);
    // Set the resolution to 10-bit (0..1023)
    analogReadResolution(10); // Can be 8, 10, 12 or 14
    // Let the ADC settle
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);
    delay(10);
    
    rawAdcValues[0] = analogRead(analogPinsToRead[0]);
    
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);
    delay(100);
    
    
//    Read AD_LDO1 Value
    // Set the analog reference to 1.2V (default = 3.6V)
    analogReference(AR_INTERNAL_1_2);
    // Set the resolution to 10-bit (0..1023)
    analogReadResolution(10); // Can be 8, 10, 12 or 14
    // Let the ADC settle
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);
    delay(10);
    
    rawAdcValues[1] = analogRead(analogPinsToRead[1]);
    
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);
    
    delay(100);

    
//    Read Grove Analog ADC Value
    // Set the analog reference to 3.6V (default = 3.6V)
    analogReference(AR_DEFAULT);
    // Let the ADC settle
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);
    delay(10);
    
    // Get the raw 10-bit, 0..3600mV ADC value
    for (int i=2; i<8; i++) {
        rawAdcValues[i] = analogRead(analogPinsToRead[i]);
    }
    
    digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);
    
    delay(100);
    
    for (int i=0; i<8; i++){
        Serial.printf("Raw ADC value of %u: %u\n", analogPinsToRead[i], rawAdcValues[i]);
    }
    
    delay(100);
    
    // Convert the raw adc values to compensated values.
    adcValues[0] = (float)rawAdcValues[0] * VUSB_ADC_VALUE_PER_LSB * (1/VUSB_DIVIDER);
    Serial.printf("Adc value of %u: %f [Evaluate this value]\n", analogPinsToRead[0], adcValues[0]);
    // Convert the raw adc values to compensated values.
    adcValues[1] = (float)rawAdcValues[1] * VBAT_ADC_VALUE_PER_LSB * (1/VBAT_DIVIDER);
    Serial.printf("Adc value of %u: %f [Evaluate this value]\n", analogPinsToRead[1], adcValues[1]);
    
    // Convert the raw adc values to compensated values.
    for (int i=2; i<8; i++) {
        adcValues[i] = (float)rawAdcValues[i] * GROVE_ADC_VALUE_PER_LSB * (1/GROVE_ADC_DIVIDER);
        Serial.printf("Adc value of %u: %f [Evaluate this value]\n", analogPinsToRead[i], adcValues[i]);
    }
}