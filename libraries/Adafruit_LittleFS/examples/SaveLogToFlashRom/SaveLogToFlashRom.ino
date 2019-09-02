#include "NectisCellular.h"
#include "NectisCellularExternalFlash.h"

NectisCellular Nectis;
File file(ExternalFS);
Stopwatch sw;

#define MAX_LEVEL   2
#define FILENAME    "/nectis.txt"
#define CONTENTS    "Nectis Cellular's file contents"

#define INPUT_BUFFER_SIZE       (64)
char input[INPUT_BUFFER_SIZE];
char inputFilename[INPUT_BUFFER_SIZE];
char contents[64];


void setup() {
    Serial.begin(115200);
  delay(4000);
    Serial.println("");
    Serial.println("--- START ---------------------------------------------------");
    
    Serial.println("### I/O Initialize.");
    Nectis.Init();
    delay(100);
    Serial.println("### Power supply cellular ON.");
    Nectis.PowerSupplyCellular(true);
    delay(100);
    Serial.println("### Power supply ON.");
    // Make sure that the MODULE_PWR_PIN is set to HIGH.
    Nectis.PowerSupplyGrove(true);
    delay(100);
    
    
    // Get the current time.
    Nectis.Bg96Begin();
    Nectis.InitLteM();
    
    //    // Enter BG96 into sleep mode with AT command
    //    Nectis.Bg96TurnOff();
    //    // End the Uart between nRF52840 and BG96
    //    Nectis.Bg96End();
    
    
    // External Flash ROM
    Serial.println("ExternalFS List Files Example");
    
    // Initialize Internal File System
    ExternalFS.begin();
    
    Serial.println("");
    Serial.println("Please input number");
    Serial.println("1: Format the external flash rom.");
    Serial.println("2: List all the files in the external flash rom.");
    Serial.println("3: Make new files in the external flash rom.");
    Serial.println("4: Choose to which file to open");
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
                input[INPUT_SIZE++] = inputOneByte;
                
                if (INPUT_SIZE == INPUT_BUFFER_SIZE) {
                    input[INPUT_SIZE] = 0x00;
                    Serial.flush();
                    break;
                }
            }
        } else if (Serial.available() == 0) {
            input[INPUT_SIZE] = 0x00;
        }
    }
    
    if (strlen(input) == 1) {
        //        "input" is in ASCII.
        uint8_t inputNumberDecimal = uint8_t(input[0]-'0');
        
        if (inputNumberDecimal == 1) {
            Serial.println('1');
            
            Serial.print("Formatting ...");
            // Format without erase
            // Pass true for full external flash erasing (take time)
            ExternalFS.format(false);
            
            Serial.println("Done");
        } else if (inputNumberDecimal == 2) {
            Serial.println('2');
            
            Serial.println("Listing files ...");
            printTreeDir("/", 0);
            
            Serial.println("Done");
        } else if (inputNumberDecimal == 3) {
            Serial.println('3');
    
            struct tm currentTime;
            char currentTimeStr[64];
    
            memset(&currentTimeStr[0], 0x00, sizeof(currentTimeStr));
            memset(&contents[0], 0x00, sizeof(contents));
    
            Nectis.GetCurrentTime(&currentTime);
            strftime(currentTimeStr, sizeof(currentTimeStr), "%Y%m%d_%H%M%S", &currentTime);
            memcpy(&contents[0], currentTimeStr, strlen(currentTimeStr));
    
            Serial.print("JST:");
            Serial.println(currentTimeStr);
    
            char filename[strlen(currentTimeStr) + 6];
            memset(&filename[0], 0x00, sizeof(filename));
            snprintf(filename, (sizeof(filename)), "/%s.txt", currentTimeStr);
    
            file.open(filename, FILE_READ);
    
            // file existed
            if (file) {
                Serial.printf("%s file exists\n", filename);
        
                uint32_t readlen;
                char buffer[64] = {0};
                readlen = file.read(buffer, sizeof(buffer));
        
                buffer[readlen] = 0;
                Serial.println(buffer);
                file.close();
            } else {
                Serial.printf("Open %s file to write ... \n", filename);
        
                if (file.open(filename, FILE_WRITE)) {
                    Serial.println("OK");
                    file.write(contents, strlen(contents));
                    file.close();
                } else {
                    Serial.println("Failed!");
                }
            }
            Serial.println("Done");
        } else if (inputNumberDecimal == 4) {
            Serial.println('4');
            
            Serial.println("Listing files ...");
            printTreeDir("/", 0);
    
            sw.Restart();
            Serial.println("Please select which file to open (Timeout is 1 minute)");
    
            //ToDO: Enable to wait until the file name is input through serial monitor in order to open any file.
//            Serial.setTimeout(60000);
//            int inputFileNameByte = Serial.timedRead();
            file.open(inputFilename, FILE_READ);
        } else {
        }
        memset(&input[0], 0x00, sizeof(input));
        Serial.println();
        Serial.println("Please input number");
        Serial.println("1: Format the external flash rom.");
        Serial.println("2: List all the files in the external flash rom.");
        Serial.println("3: Make new files in the external flash rom.");
        Serial.println("4: Choose to which file to open");
    }
}


/**************************************************************************/
/*!
    @brief  Print out whole directory tree of an folder
            until the level reach MAX_LEVEL

    @note   Recursive call
*/
/**************************************************************************/
void printTreeDir(const char* cwd, uint8_t level) {
    // Open the input folder
    File dir(cwd, FILE_READ, ExternalFS);
    
    // Print root
    if (level == 0) Serial.println("root");
    
    // File within folder
    File item(ExternalFS);
    
    // Loop through the directory
    while( (item = dir.openNextFile(FILE_READ)) ) {
        // Indentation according to dir level
        for(int i=0; i<level; i++) Serial.print("|  ");
        
        Serial.print("|_ ");
        Serial.print( item.name() );
        
        if ( item.isDirectory() ) {
            Serial.println("/");
            
            // ATTENTION recursive call to print sub folder with level+1 !!!!!!!!
            // High number of MAX_LEVEL can cause memory overflow
            if ( level < MAX_LEVEL ) {
                printTreeDir( item.path(), level+1 );
            }
        } else {
            // Print file size starting from position 30
            int pos = level*3 + 3 + strlen(item.name());
            
            // Print padding
            for (int i=pos; i<30; i++) Serial.print(' ');
            
            // Print at least one extra space in case current position > 50
            Serial.print(' ');
            
            Serial.print( item.size() );
            Serial.println( " Bytes");
        }
        
        item.close();
    }
    
    dir.close();
}

