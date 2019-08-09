#include "NectisCellular.h"

NectisCellular Nectis;

#define INPUT_BUFFER_SIZE       (64)
char input[INPUT_BUFFER_SIZE];


void setup() {
    delay(4000);
    
    Serial.begin(115200);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Serial.println("### I/O Initialize.");
    Nectis.Init();
    delay(100);
    
    Serial.println("Please input number");
}

void loop() {
    unsigned int INPUT_SIZE = 0;
    
    while (Serial.available() > 0) {
        int inputOneByte = Serial.read();
    
        if (Serial.available() > 0) {
            // Please select "CR and LF" on the serial monitor of ArduinoIDE
            // 0x0D: CR
            if (inputOneByte == 0x0D) {
            } else {
//                Serial.print(inputOneByte);
//                Serial.print(" ");
//                Serial.println(inputOneByte, HEX);
            
                input[INPUT_SIZE++] = inputOneByte;
                
                if (INPUT_SIZE == INPUT_BUFFER_SIZE) {
                    input[INPUT_SIZE] == 0x00;
                    Serial.flush();
                    Serial.println(input);
                    break;
                }
            }
        } else if (Serial.available() == 0) {
            input[INPUT_SIZE] = 0x00;
    
            Serial.println(input);
            Serial.print("");
            memset(&input[0], 0x00, SERIAL_BUFFER_SIZE);
            Serial.println("Please input number");
        }
    }
}