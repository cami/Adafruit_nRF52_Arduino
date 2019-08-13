void setup() {
  Serial.begin(115200);
  Serial.println("setup");
}

void loop() {
  float usb_voltage_level_mv;
  usb_voltage_level_mv = readVusb();

  Serial.printf("%f[mV]\n",usb_voltage_level_mv);

  delay(5000);
}

float readVusb() {
  float mv_per_lsb = 3600.0F/1024.0F; // 10-bit ADC with 3.6V input range

  int adc_value = 0;
  float battery_level_mv = 0;

  // Get a fresh ADC value
  adc_value = analogRead(USB_VOLTAGE_PIN);
  battery_level_mv = (float)adc_value * mv_per_lsb;

  return battery_level_mv;
}
