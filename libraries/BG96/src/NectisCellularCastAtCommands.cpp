//
// Created by NaotoFujihiro on 2019-07-09.
//

#include <Uart.h>
#include "Internal/AtSerial.h"
#include "Internal/Debug.h"
#include "WioCellular.h"
#include "NectisCellularConfig.h"
#include "WioCellularHardware.h"
#include "NectisCellularCastAtCommands.h"
#include "NectisCellular.h"
#include <string.h>


#define RET_OK(val)                     (ReturnOk(val))
#define RET_ERR(val, err)               (ReturnError(__LINE__, val, err))


bool NectisCellularCastAtCommands::ReturnError(int lineNumber, bool value, NectisCellularCastAtCommands::ErrorCodeType errorCode) {
    _LastErrorCode = errorCode;
    
    char str[100];
    sprintf(str, "%d", lineNumber);
    DEBUG_PRINT("ERROR! ");
    DEBUG_PRINTLN(str);
    
    return value;
}

int NectisCellularCastAtCommands::ReturnError(int lineNumber, int value, NectisCellularCastAtCommands::ErrorCodeType errorCode) {
    _LastErrorCode = errorCode;
    
    char str[100];
    sprintf(str, "%d", lineNumber);
    DEBUG_PRINT("ERROR! ");
    DEBUG_PRINTLN(str);
    
    return value;
}

NectisCellularCastAtCommands::NectisCellularCastAtCommands() : _SerialAPI(&SerialUART), _AtSerial(&_SerialAPI, &_Wio) {
}

NectisCellularCastAtCommands::ErrorCodeType NectisCellularCastAtCommands::GetLastError() const {
    return _LastErrorCode;
}

void NectisCellularCastAtCommands::CastAllCommands(){
    
    _AtSerial.WriteCommandAndReadResponse("ATI", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+GMI", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+GMM", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+GMR", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGMI", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGMM", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGMR", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+GSN", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGSN", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT&V", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+IFC?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+ICF?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+IPR?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CPAS", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QCFG=?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QCFG=\"celevel\"", "^OK$", 10000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CIMI", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CLCK=?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CPIN?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QCCID", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QPINC?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QINISTAT", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QSIMDET?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QSIMSTAT?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CREG?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+COPS?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+COPS=?", "^OK$", 60000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CSQ", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CIND?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CPOL?", "^OK$", 10000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+COPN", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CTZU?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CPSMS?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QPSMS?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QPSMCFG?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QPSMEXTCFG?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QCSCON?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CEDRXS?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CEDRXRDP", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CTZR?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QLTS", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QNWINFO", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QCSQ", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QSPN", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CRLP?", "^OK$", 10000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CSMS?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGATT?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGDCONT?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGQREQ?", "^OK$", 10000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGQMIN?", "^OK$", 10000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGACT?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGREG?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGEREP?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CGSMS?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CEREG?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QGDCNT?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QAUGDCNT?", "^OK$", 10000, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CCLK?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+CBC", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QSCLK?", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QTEMP", "^OK$", 500, NULL);
}

void NectisCellularCastAtCommands::TurnOnBg96Gps() {
    _AtSerial.WriteCommandAndReadResponse("AT+QGPS=1", "^OK$", 500, NULL);
}

void NectisCellularCastAtCommands::TurnOffBg96Gps() {
    _AtSerial.WriteCommandAndReadResponse("AT+QGPSEND", "^OK$", 500, NULL);
}

void NectisCellularCastAtCommands::AcquireBg96Gps() {
    _AtSerial.WriteCommandAndReadResponse("AT+QGPSLOC=1", "^OK$", 500, NULL);
    _AtSerial.WriteCommandAndReadResponse("AT+QGPSGNMEA=\"GGA\"", "^OK$", 500, NULL);
}

//void NectisCellular::CheckMobileNetwork() {
//    _AtSerial.WriteCommandAndReadResponse("AT+COPS?", "^OK$", 500, NULL);
//}
//
//// CellId: Cell ID, LAC: Location Area Code
//void NectisCellular::SearchForCellIdAndLAC() {
//    _AtSerial.WriteCommandAndReadResponse("AT+CGREG=2", "^OK$", 500, NULL);
//    _AtSerial.WriteCommandAndReadResponse("AT+CGREG?", "^OK$", 500, NULL);
//}
//
//void NectisCellular::SearchForBaseStation() {
//    _AtSerial.WriteCommandAndReadResponse("AT+COPS=?", "^OK$", 1000000, NULL); // Search for Base Station
//}
//
//void NectisCellular::CheckSimStatus() {
//    _AtSerial.WriteCommandAndReadResponse("AT+CPIN?", "^OK$", 5000, NULL);
//}
