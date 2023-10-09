/*
 * File:   main.c
 * Author: sen
 *
 * Created on September 30, 2023, 4:21 PM
 */


#include <xc.h>

#include "confreg.h"
#include "main.h"

void main(void) {
    // initialize the I2C module ourself since lots of different things use it
    RB1I2Cbits.SLEW   = 0x1;    // SCL pin should have I2C slew control
    RB1I2Cbits.TH     = 0x1;    // SCL pin should have I2C thresholds
    RB2I2Cbits.SLEW   = 0x1;    // SDA pin should have I2C slew control
    RB2I2Cbits.TH     = 0x1;    // SDA pin should have I2C thresholds
    ODCONBbits.ODCB1  = 0x1;    // SCL pin should be open-drain for I2C use
    ODCONBbits.ODCB2  = 0x1;    // SDA pin should be open-drain for I2C use
    I2C2CON0bits.MODE = 0x4;    // I2C Host mode, 7-bit addressing
    I2C2CON0bits.RSEN = 0x0;    // disable restart
    I2C2CON0bits.CSTR = 0x0;    // not holding the clock, operate SCL normally
    I2C2CON2bits.FME  = 0x0;    // disable Fast Mode
    I2C2CON2bits.ABD  = 0x0;    // use address buffers, not legacy mode
    I2C2CLKbits.CLK   = 0x3;    // I2C clocked from MFINTOSC (500KHz))
    I2C2CON0bits.EN   = 0x1;    // enable the I2C module
    
    // initialize all the modules
    fg_init();      // fuel gauge
    disp_init();    // display
    bt_init();      // bluetooth
    
    disp_power_on();
    return;
}
