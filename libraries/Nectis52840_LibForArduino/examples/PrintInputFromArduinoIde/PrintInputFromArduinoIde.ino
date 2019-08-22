#define INPUT_BUFFER_SIZE       (64)
char input[INPUT_BUFFER_SIZE];


void setup() {
  delay(4000);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");
  
  Serial.println("Please input number");
}

void loop() {
  unsigned int INPUT_SIZE = 0;
  
  while (Serial.available() > 0) {
    // After Serial.read(), Serial.available() is subtracted by 1.
    int inputOneByte = Serial.read();
    //    Serial.print(inputOneByte);
    //    Serial.print(" ");
    //    Serial.println(inputOneByte, HEX);
    
    input[INPUT_SIZE++] = inputOneByte;
    
    if (INPUT_SIZE == INPUT_BUFFER_SIZE-1) {
      input[INPUT_SIZE] = 0x00;
      Serial.println(input);
      delay(10);
      
      memset(&input[0], 0x00, sizeof(input));
      INPUT_SIZE = 0;
    }
    
    // Please select "CR and LF" on the serial monitor of ArduinoIDE
    // if (Serial.available() == 1) then Serial.read() = CR
    // if (Serial.available() == 0) then Serial.read() = LF
    if (Serial.available() == 2) {
      input[INPUT_SIZE] == 0x00;
      Serial.println(input);
      delay(10);
      memset(&input[0], 0x00, sizeof(input));
      
      Serial.read();
      Serial.read();
      
      Serial.println("Please input number");
    }
    delay(1);
  }
}
