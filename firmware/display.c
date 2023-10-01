/* 
 * File:   display.c
 * Author: sen
 * Description: Communication with ELW2106AA OLED display unit
 *
 * Created on September 30, 2023, 4:56 PM
 */

#include <xc.h>
#include "main.h"

int disp_init(void) {
    // hold the OLED in reset for now and 16V rail powered down as we set things up
    pin_low(OLED_nRESET_LAT, OLED_nRESET_PIN);
    pin_low(OLED_16V_LAT, OLED_16V_PIN);
    
    // set the pin directions for TRIS and nRESET as outputs
    pin_as_output(OLED_DC_TRIS, OLED_DC_PIN);
    pin_as_output(OLED_nRESET_TRIS, OLED_nRESET_PIN);
    pin_as_output(OLED_16V_TRIS, OLED_16V_PIN);

    // set up the SPI pins we need to talk to the OLED
    pps_unlock();    
    OLED_SCLK_PPS = 0x1E; // set up the OLED SCLK pin to SPI1 SCLK
    OLED_MOSI_PPS = 0x1F; // set up the OLED MOSI pin to SPI1 MOSI
    OLED_nSS_PPS  = 0x20; // set up the OLED nSS pin to SPI1 nSS
    pps_lock();
    
    // set up the SPI peripheral
    SPI1CON0bits.LSBF = 0;  // MSB first
    SPI1CON0bits.MST = 1;   // SPI host mode
    
    SPI1CON1bits.CKE = 1;   // data changes on active->idle clock transition
    SPI1CON1bits.CKP = 1;   // SCLK idle state is high - NOT 100% SURE ABOUT THIS
    SPI1CON1bits.FST = 0;   // delay to first SCK should be at least 1/2 baud period
    SPI1CON1bits.SSP = 1;   // SS is active-low
    SPI1CON1bits.SDOP = 0;  // MOSI is active-high
    
    SPI1CON2bits.SSET = 0;  // drive SS active only when transmitting
    
    SPI1CLK = 0;            // SPI1 CLK driven from FOSC
    SPI1BAUD = 8;           // SPI1 CLK is divide-by-8 (should be able to run 1:1 with FOSC, but no need to run that fast here)
    
    // enable SPI!
    SPI1CON0bits.EN = 1;
    
    return 0;
}

void disp_power_on(void) {
    // bring the panel out of reset and initialize it
    // (sequence from SSD1362 datasheet section 7.9)
    
    pin_high(OLED_nRESET_LAT, OLED_nRESET_PIN); // reset deasserted
    __delay_us(100);                            // wait 100uS
    pin_high(OLED_16V_LAT, OLED_16V_PIN);       // turn on 16.5v rail
    __delay_us(500);                            // let the rail come up
                                                // TODO: tune the rail-up time
    disp_send_cmd(DISPCMD_POWER_ON);        // ask the display to turn on
}

void disp_power_off(void) {
    // shut the panel down
    // (sequence from SSD1362 datasheet section 7.9)
    
    disp_send_cmd(DISPCMD_POWER_OFF);       // ask the display to turn off
    __delay_us(50);                             // let it finish up
    pin_low(OLED_16V_LAT, OLED_16V_PIN);        // shut down the 16.5v rail
    pin_low(OLED_nRESET_LAT, OLED_nRESET_PIN);  // hold the display in reset
}

void disp_send_cmd(uint8_t cmd) {
    pin_low(OLED_DC_LAT, OLED_DC_PIN);  // we're sending a command
    SPI1TXB = cmd;
    // TODO: probably need to wait after
}