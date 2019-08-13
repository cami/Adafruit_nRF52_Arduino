void setup() {
  Serial.begin(115200);
  Serial.println("setup");
}

void loop() {
  float lipo_voltage_level_mv;
  lipo_voltage_level_mv = readVbat();

  Serial.printf("%f[mV]\n", lipo_voltage_level_mv);

  delay(5000);
}

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
