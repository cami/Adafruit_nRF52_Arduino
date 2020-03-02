constexpr uint8_t INPUT_BUFFER_SIZE = 64;
int input[INPUT_BUFFER_SIZE];
uint8_t inputSize;


void WaitForInput() {
  Serial.println("### Please input number");
}

void ClearBuffer() {
  memset(input, 0x00, INPUT_BUFFER_SIZE);
}

void InitVariables() {
  inputSize = 0;
}

void PrintInput(int *buf) {
  for (uint8_t i = 0; i < inputSize; i++) {
    Serial.printf("%c", input[i]);
  }
  Serial.println();
}


void setup() {
  Serial.begin(115200);
  ClearBuffer();
  InitVariables();

  delay(4000);
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");
  
  WaitForInput();
}

void loop() {  
  while (Serial.available() > 0) {
    int inputInt = Serial.read();
    input[inputSize++] = inputInt;

    // After Serial.read(), Serial.available() is subtracted by 1.
    /*
      Serial.print(inputInt);
      Serial.print(" ");
      Serial.print(inputInt, HEX);
      Serial.print(" ");
      Serial.printf("%c\n", inputInt);
     */

    if (inputSize == INPUT_BUFFER_SIZE - 1) {
      PrintInput(&input[0]);
      delay(10);
      ClearBuffer();
      InitVariables();
    }

    /*
      Please select "CR and LF" on the serial monitor of ArduinoIDE
      if (Serial.available() == 1) then Serial.read() = CR
      if (Serial.available() == 0) then Serial.read() = LF
     */

    if (Serial.available() == 2) {
      PrintInput(&input[0]);
      delay(10);
      ClearBuffer();
      InitVariables();

      Serial.read();
      Serial.read();

      WaitForInput();
    }
      
    delay(1);
  }
}
