/* 
 * File:   fuelgauge.h
 * Author: sen
 *
 * Created on October 7, 2023, 3:10 PM
 */

#ifndef FUELGAUGE_H
#define	FUELGAUGE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define FG_I2C_ADDR         0x6C

#define FG_REG_STATUS       0x00    // Status - status of the device
#define FG_REG_FSTAT        0x3D    // FStat - status of the algorithm
#define FG_REG_HIBCFG       0xBA    // HibCfg - hibernation configuraiton
#define FG_REG_SOFTWAKE     0x60    // SoftWake - manually wake up the device
#define FG_REG_MODELCFG     0xDB    // ModelCfg - configuration of model
#define FG_REG_DESIGNCAP    0x18    // DesignCap - design capacity of battery
#define FG_REG_ICHGTERM     0x1E    // IChgTerm - charge termination voltage
#define FG_REG_VEMPTY       0x3A    // Vempty - voltage at empty
#define FG_REG_REPCAP       0x05    // RepCap - remaining capacity
#define FG_REG_TTE          0x11    // TTE - time to empty

#define FG_MASK_STATUS_POR          0x2000
#define FG_MASK_FSTAT_DNR           0x01
#define FG_MASK_MODELCFG_REFRESH    0x8000

#define FG_CMD_HIBCFG_EXIT_HIB          0x0000
#define FG_CMD_SOFTWAKE_CLEAR           0x0000
#define FG_CMD_SOFTWAKE_SOFTWAKE_NOW    0x0090
    
    uint8_t fg_init(void);
    void fg_reconfigure(void);
    uint16_t fg_read_reg(uint8_t);
    uint8_t fg_write_reg(uint8_t, uint16_t);
    uint8_t fg_write_reg_with_verify(uint8_t, uint16_t);
    

#ifdef	__cplusplus
}
#endif

#endif	/* FUELGAUGE_H */

