/*
 * Alternately blink two LEDs on the board.
 */


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_CONN, OUTPUT);
}

void loop() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(1000);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
}