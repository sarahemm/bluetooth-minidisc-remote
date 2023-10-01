/*
 * File:   util.c
 * Author: sen
 * Description: Small utilities used by other modules
 *
 * Created on September 30, 2023, 4:59 PM
 */

#include <xc.h>
#include "util.h"

void pps_unlock(void) {
    // unlock the PPS for changes, per datasheet section 17.4
    interrupts_off();
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00;
}

void pps_lock(void) {
    // lock the PPS to prevent changes, per datasheet section 17.4
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01;
    
    interrupts_on();
}