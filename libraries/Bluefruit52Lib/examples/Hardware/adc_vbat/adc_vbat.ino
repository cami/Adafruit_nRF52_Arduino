void setup() {
  Serial.begin(115200);
  Serial.println("setup");
}

void loop() {
  float lipo_voltage_level_mv;
  lipo_voltage_level_mv = readVbat();

  Serial.printf("%f[mV]\n", lipo_voltage_level_mv);

#ifdef NRF52840_XXAA
#define VBAT_DIVIDER      (0.5F)          // 150K + 150K voltage divider on VBAT
#define VBAT_DIVIDER_COMP (2.0F)          // Compensation factor for the VBAT divider
#else
#define VBAT_DIVIDER      (0.71275837F)   // 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
#define VBAT_DIVIDER_COMP (1.403F)        // Compensation factor for the VBAT divider
#endif

float readVbat(void) {
#define VBAT_MV_PER_LSB   (1.171875F)       // 1.2V ADC range and 10-bit ADC resolution = 1200mV/1024
#define VBAT_DIVIDER      (0.25F)           // From IC: RP124N334E

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, HIGH);

  int adc_value = 0;

  // Set the analog reference to 1.2V (default = 3.6V)
  analogReference(AR_INTERNAL_1_2);

  // Set the resolution to 10-bit (0..1023)
  analogReadResolution(10); // Can be 8, 10, 12 or 14

  // Let the ADC settle
  delay(100);

  // Get the raw 10-bit, 0..1200mV ADC value
  adc_value = analogRead(BATTERY_VOLTAGE_PIN);
  while ((adc_value < 0) || (adc_value > 1023)) {
    adc_value = analogRead(BATTERY_VOLTAGE_PIN);
  }

  Serial.printf("adc_value: %d\n", adc_value);

  // Convert the raw value to compensated mv, taking the resistor-
  // divider into account (providing the actual LIPO voltage)
  float battery_voltage_mv = (float)adc_value * VBAT_MV_PER_LSB * (1 / VBAT_DIVIDER);

  // Set the ADC back to the default settings
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  digitalWrite(BATTERY_LEVEL_ENABLE_PIN, LOW);

  return battery_voltage_mv;
}

void loop() {
  // Get a raw ADC reading
  float vbat_mv = readVBAT();

  // Convert from raw mv to percentage (based on LIPO chemistry)
  uint8_t vbat_per = mvToPercent(vbat_mv);

  // Display the results

  Serial.print("LIPO = ");
  Serial.print(vbat_mv);
  Serial.print(" mV (");
  Serial.print(vbat_per);
  Serial.println("%)");

  delay(1000);
}

