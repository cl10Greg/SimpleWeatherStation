#include "Temperature.h"
#include "userMacro.h"
#include <htc.h>
#include "customADC.h"

void readTemp()
{
    selectTemp();
    
    //Turn on ADC
    ADON = 1;
    
    //Wait acquisition time
    //10ms
    __delay_ms(10);
    //Start conversion (set go/done bit)
    GO_nDONE = 1;
    
    //Wait for go/done bit to be cleared
    while(GO_nDONE);

    //Write lower 8 bits here
    eeprom_write(tempValLAddr,ADRESL);
     //Write higher 2 bits here
     eeprom_write(tempValHAddr,ADRESH);

}

void initTemp(){
    //Set the start value and the default hi and low temps
    eeprom_write(tempValHAddr,0x00);
    eeprom_write(tempValLAddr, 0x00);
    eeprom_write(tempHiAddr, tempStartHi);
    eeprom_write(tempLoAddr, tempStartLo);
    eeprom_write(tempUnitAddr, tempC);
}

void setTempUnit(){

}

void setTempHi(){

}

void setTempLo(){
    
}
/*unsigned char convertToTemp(){
    
}*/