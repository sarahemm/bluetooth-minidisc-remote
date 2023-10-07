/* 
 * File:   bluetooth.c
 * Author: sen
 * Description: Communication with CC256x Bluetooth chipset
 *
 * Created on September 30, 2023, 4:55 PM
 */

#include <xc.h>
#include "main.h"

int bt_init(void) {
    // keep the BT module shut down until we're ready
    pin_low(BT_nSHUTD_LAT, BT_nSHUTD_PIN);
    pin_as_output(BT_nSHUTD_TRIS, BT_nSHUTD_PIN);
    
    // set up the PPS pins we need for BT:
    //  NCO1 for BT SLOW_CLK
    //  TX1 for HCI_TO_BT
    //  RTS1 for HCI_RTS
    pps_unlock();    
    BT_SLOWCLK_PPS = 0x26;  // set up the NCO1 output on the BT SLOW_CLK pin
    BT_TX_PPS = 0x13;       // set up the TX1 output on the BT HCI_TO_BT pin
    BT_RTS_PPS = 0x15;      // set up the RTS1 output on the BT HCI_RTS pin
    pps_lock();
    
    // set up the NCO that generates the 32.768KHz clock needed by the BT chipset
    NCO1CLKbits.CKS = 3;    // clock NCO from MFINTOSC (500KHz)
    // set up the NCO to output 32.768KHz
    NCO1INCU = 0x02;
    NCO1INCH = 0x18;
    NCO1INCL = 0xDF;
    NCO1CONbits.PFM = 0;    // run the NCO in fixed duty cycle mode
    NCO1CONbits.EN = 1;     // start outputting the clock

    // set up the UART to talk to the BT module
    U1CON0bits.BRGS = 1;    // high speed mode (to get accurate 115200)
    U1CON0bits.MODE = 0x00; // async 8-bit UART mode
    U1CON2bits.FLO = 0x2;   // RTS/CTS flow control
    U1BRGH = 0x00;          // 115200bps
    U1BRGL = 0x0F;          // 115200bps
    U1CON0bits.TXEN = 1;    // enable transmitter
    U1CON0bits.RXEN = 1;    // enable receiver
    U1CON1bits.ON = 1;      // enable the UART
    
    // wait 10uS between clock starting and bringing BT out of shutdown
    __delay_us(10);
    
    // start up the BT module
    pin_high(BT_nSHUTD_LAT, BT_nSHUTD_PIN);
    
    return 0;
}