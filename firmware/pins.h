/* 
 * File:   pins.h
 * Author: sen
 * Description: Definitions of what pins are used for what
 * 
 * Created on September 30, 2023, 4:24 PM
 */

#ifndef PINS_H
#define	PINS_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ------- */
/* BUTTONS */
/* ------- */

#define BTN_VOL_PRESS_PIN   0
#define BTN_VOL_PRESS_PORT  PORTA

#define BTN_VOL_UP_PIN      5
#define BTN_VOL_UP_PORT     PORTB

#define BTN_VOL_DOWN_PIN    4
#define BTN_VOL_DOWN_PORT   PORTB

#define BTN_DISP_ON_PIN     1
#define BTN_DISP_ON_PORT    PORTA

#define BTN_MODE_PIN        2
#define BTN_MODE_PORT       PORTA

#define BTN_TRK_BACK_PIN    3
#define BTN_TRK_BACK_PORT   PORTA

#define BTN_TRK_FWD_PIN     4
#define BTN_TRK_FWD_PORT    PORTA

#define BTN_DISPLAY_PIN     2
#define BTN_DISPLAY_PORT    PORTE

#define BTN_PLAYPAUSE_PIN   2
#define BTN_PLAYPAUSE_PORT  PORTC


/* ----------- */
/* HOLD SWITCH */
/* ----------- */

#define HOLD_EXCEPT_VOL_PIN     1
#define HOLD_EXCEPT_VOL_PORT    PORTD

#define HOLD_ALL_PIN            1
#define HOLD_ALL_PORT           PORTE


/* ------------ */
/* MD INTERFACE */
/* ------------ */

#define REMOTE_TAKEOVER_PIN     4
#define REMOTE_TAKEOVER_TRIS    TRISD
#define REMOTE_TAKEOVER_LAT     LATD

#define REMOTE_SEND_PIN         7
#define REMOTE_SEND_TRIS        TRISD
#define REMOTE_SEND_LAT         LATD

#define MD_LCD_DIR_PIN          3
#define MD_LCD_DIR_TRIS         TRISD
#define MD_LCD_DIR_LAT          LATD

#define MD_LCD_PIN              5
#define MD_LCD_TRIS             TRISD
#define MD_LCD_LAT              LATD
#define MD_LCD_PORT             PORTD


/* ------- */
/* DISPLAY */
/* ------- */
#define OLED_DC_PIN             2
#define OLED_DC_TRIS            TRISD
#define OLED_DC_LAT             LATD

#define OLED_FR_PIN             3
#define OLED_FR_PORT            PORTB

#define OLED_nRESET_PIN         6
#define OLED_nRESET_TRIS        TRISD
#define OLED_nRESET_LAT         LATD

// per Rev001 ECO A
#define OLED_16V_PIN            5
#define OLED_16V_TRIS           TRISB
#define OLED_16V_LAT            LATB

#define OLED_SCLK_PPS           RC3PPS
#define OLED_MOSI_PPS           RC4PPS
#define OLED_nSS_PPS            RA5PPS


/* --------- */
/* BLUETOOTH */       
/* --------- */

#define BT_nSHUTD_PIN           0
#define BT_nSHUTD_TRIS          TRISC
#define BT_nSHUTD_LAT           LATC
    
#define BT_SLOWCLK_PPS          RD0PPS
#define BT_TX_PPS               RC5PPS
#define BT_RTS_PPS              RC1PPS
    
#ifdef	__cplusplus
}
#endif

#endif	/* PINS_H */

