/*
 * File:   main.c
 * Author: sen
 *
 * Created on September 30, 2023, 4:21 PM
 */


#include <xc.h>

#include "main.h"

void main(void) {
    // initialize all the modules
    disp_init();
    bt_init();
    
    disp_power_on();
    return;
}
