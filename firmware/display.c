/* 
 * File:   display.c
 * Author: sen
 * Description: Communication with ELW2106AA OLED display unit
 *
 * Created on September 30, 2023, 4:56 PM
 */

#include <xc.h>
#include "pins.h"
#include "util.h"

int disp_init(void) {
    pin_low(OLED_nRESET_LAT, OLED_nRESET_PIN);

    pin_as_output(OLED_DC_TRIS, OLED_DC_PIN);
    pin_as_output(OLED_nRESET_TRIS, OLED_nRESET_PIN);

    return 0;
}