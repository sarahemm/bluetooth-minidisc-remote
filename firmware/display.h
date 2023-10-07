/* 
 * File:   display.h
 * Author: sen
 * Description: Communication with ELW2106AA OLED display unit
 * 
 * Created on September 30, 2023, 5:05 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DISPCMD_POWER_ON    0xAF
#define DISPCMD_POWER_OFF   0xAE
#define DISPCMD_VDDREG      0xAB
    
#define DISPARG_VDDREG_EXT  0
#define DISPARG_VDDREG_INT  1
    
    int disp_init(void);
    void disp_power_on(void);
    void disp_power_off(void);
    void disp_send_cmd(uint8_t);
    void disp_send_2b_cmd(uint8_t, uint8_t);
    
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

