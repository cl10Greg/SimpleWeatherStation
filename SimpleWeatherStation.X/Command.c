#include "userMacro.h"
#include "Bluetooth.h"
#include <htc.h>
#include "Temperature.h"



void allCommands(){
    unsigned char tempVal;
    unsigned char tempHiByte;
    unsigned char tempLoByte;
    unsigned char curTemp[2];

    tempVal = eeprom_read(cmdByteAddr);
    switch(tempVal){
        //Get temperature
        case 0x30:
            tempHiByte = eeprom_read(tempValHAddr);
            tempLoByte = eeprom_read(tempValLAddr);
            curTemp[0] = tempHiByte;
            curTemp[1] = tempLoByte;
            writeString(curTemp);
            break;
        case 0x03:
            tempHiByte = eeprom_read(tempValHAddr);
            tempLoByte = eeprom_read(tempValLAddr);
            curTemp[0] = tempHiByte;
            curTemp[1] = tempLoByte;
            writeString(curTemp);
            break;
        //Get temp high
        case 0x31:
            //writeByte('T');
            //writeByte('H');
            writeByte(eeprom_read(tempHiAddr));
            break;
        //Get temp low
        case 0x32:
            //writeByte('T');
            //writeByte('L');
            writeByte(eeprom_read(tempLoAddr));
            break;
        //Get humidity
        case 0x41:
            writeByte('H');
            break;
        //Get humidity high
        case 0x42:
            writeByte('H');
            writeByte('H');
            break;
        //Get humidity low
        case 0x43:
            writeByte('H');
            writeByte('L');
            break;
        //Error
        default:
            writeByte('E');
            break;
    }
}
