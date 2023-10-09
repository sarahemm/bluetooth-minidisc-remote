/* 
 * File:   fuelgauge.c
 * Author: sen
 * Description: Communication with MAX17260 fuel gauge IC
 *
 * Created on September 30, 2023, 4:55 PM
 */

#include <xc.h>
#include "main.h"

// TODO: error handling

uint8_t fg_init(void) {
    uint8_t por_status;
    
    // check if the fuel gauge has been reset since last initialization
    if((fg_read_reg(FG_REG_STATUS) & FG_MASK_STATUS_POR) > 0)
        fg_reconfigure();
    
    return 0;
}

void fg_reconfigure(void) {
    // reconfigure the fuel gauge after a POR, from document UG6595
    
    uint16_t hib_cfg;
    
    // wait until the Not Ready flag is cleared (710ms after power-up)
    // TODO: implement some kind of timeout-and-fail if DNR=0 never happens
    while((fg_read_reg(FG_REG_FSTAT) & FG_MASK_FSTAT_DNR) > 0)
        __delay_ms(10);
    
    // save current hibernation config then exit hibernation mode so we can reconfig
    hib_cfg = fg_read_reg(FG_REG_HIBCFG);
    fg_write_reg(FG_REG_SOFTWAKE, FG_CMD_SOFTWAKE_SOFTWAKE_NOW);
    fg_write_reg(FG_REG_HIBCFG,   FG_CMD_HIBCFG_EXIT_HIB);
    fg_write_reg(FG_REG_SOFTWAKE, FG_CMD_SOFTWAKE_CLEAR);
    
    // TODO: probably makes sense to make the battery/charge specs #defines
    fg_write_reg(FG_REG_DESIGNCAP,  400);   // design capacity is 200mAh (maybe) (400 * 0.5mAh)
    fg_write_reg(FG_REG_ICHGTERM,   48);    // charge termination current is 7.5mA (48 * 156.25uA)
    fg_write_reg(FG_REG_VEMPTY,     42240); // empty voltage is 3.3V (42240 * 0.078125mV)
    
    fg_write_reg(FG_REG_MODELCFG, 0x8000);  // charge voltage is 4.2V, and request refresh with new config info
    
    // wait for refresh/reconfiguration to be complete
    while((fg_read_reg(FG_REG_MODELCFG) & FG_MASK_MODELCFG_REFRESH) > 0)
        __delay_ms(10);
    
    // restore previous hibernation config
    fg_write_reg(FG_REG_HIBCFG, hib_cfg);
}

uint8_t fg_percent_left(void) {
    return (uint8_t)(fg_read_reg(FG_REG_REPCAP) * 256);
}

long fg_minutes_left(void) {
    return (long)fg_read_reg(FG_REG_TTE) * 5625 / 60000;
}

// TODO: this is unproven and almost certainly has errors
uint16_t fg_read_reg(uint8_t addr) {
    uint16_t buf;
    
    i2c_wait_for_bus_free();

    // write the register we want
    I2C_CNT = 1;  // one byte of register address
    I2C_ADDR = FG_I2C_ADDR;
    I2C_TXB = addr;
    
    i2c_start();
    i2c_wait_for_tx_done();
    if(!i2c_ack_received())
        while(1) {} // TODO: something better than hanging forever
    
    // read the value from the register
    I2C_CNT = 2;     // all registers are 16-bits (I think?)
    I2C_ADDR = FG_I2C_ADDR | 0x40;   // set read bit
    i2c_start();
    i2c_wait_for_rx_ready();
    buf = I2C_RXB;
    i2c_wait_for_rx_ready();
    buf = (uint16_t)I2C_RXB << 8;
    
    return buf;
}

// TODO: this is unproven and almost certainly has errors
uint8_t fg_write_reg(uint8_t addr, uint16_t val) {
    i2c_wait_for_bus_free();
    
    I2C_CNT = 3;   // one byte of register address, two bytes of data
    I2C_ADDR = FG_I2C_ADDR;
    I2C_TXB = addr;
    I2C_TXB = val & 0xff;
    I2C_TXB = val >> 8 & 0xff;
    
    i2c_start();
    i2c_wait_for_tx_done();
    return i2c_ack_received();
}