/************************************************************************
 * HTC.h:   The header file for the Hi-tech compiler                    *
 * pic.h:   The header file for pic interuppts and registers            *
 * Bluetooth.h: The header file for the UART communication              *
 * userMacro.h: The header file for user definitions                    *
 * pic16f877a.h:    The header file for the mapping of the pic16f877A   *
 *                  registers and memory.                               *
 ***********************************************************************/
#include <htc.h>
#include "Bluetooth.h"
#include "userMacro.h"
#include "Temperature.h"
#include "customADC.h"
#include "Packet.h"
#include "Command.h"
//#include "16x4LCD.h"
//#include "LCD.h"
//#include <pic.h>


/*************************************************************************
 * Configuration Bits                                                    *
 * WDTE:    Watchdog Timer                                               *
 *      Value:  Off                                                      *
 * LVP:     Low voltage in circuit serial programming enable bit         *
 *      Value:  Off                                                      *
 * BOREN:   Brown out reset enable bit                                   *
 *      Value:  Off                                                      *
 * FOSC:    Oscillator selection bits                                    *
 *      Value:  HS (high speed)                                          *
 * PWRTE:   Power up timer enable bit                                    *
 *      Value:  OFF                                                      *
 ************************************************************************/
__CONFIG(WDTE_OFF & LVP_OFF & BOREN_OFF & FOSC_HS & PWRTE_OFF) ;
//XT for 4MHZ
//HS for 20MHz

unsigned char rxFlag = 0;
unsigned char tempRx;

static void interrupt isr(void){
    if(RCIF && RCIE){
        if(OERR){
            CREN = 0;
            CREN = 1;
        }
        tempRx = readByte();
        if(tempRx != newLineChar){
            //Send back the right data
            eeprom_write(cmdByteAddr, tempRx);
            rxFlag = 1;
        }
    }
}
/************************************************************************
 * Function:    Main                                                    *
 * Type:        Int                                                     *
 * Arguments:   None                                                    *
 * Return:      None                                                    *
 * Purpose:     The purpose of this function is the main loop of the    *
 *              software.  The program will all be contained and called *
 *              from this function.                                     *
 ***********************************************************************/
int main()
{
    //unsigned char welcome[] = "Welcome";
    TRISB = 0x00;
    RB1 = 1;
    //writeString(welcome);
    //Used to setup the ADC
    initADC();
    //User to setup temperature
    initTemp();
    //Used to setup the UART connection for bluetooth
    initUSART();

    
    //Infinite loop.  Will look for communication and get analog values. Will
    //send and receive data in this loop
    while(1){
        readTemp();
            //Update error LEDs
            __delay_ms(10);
            //getHum();
            //Update error LEDs
            //Update LCD
            if(rxFlag == 1){
                allCommands();
                rxFlag = 0;
           }
    }

    //Should never get to this part of the program.  If it does, there was an
    //error.
    return 0;
}

