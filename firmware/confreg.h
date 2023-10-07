/* 
 * File:   confreg.h
 * Author: sen
 * Description: PIC configuration register settings
 *
 * Created on October 7, 2023, 11:20 AM
 */

// Configuration word 1L (30 0000h)
#pragma config RSTOSC   = 0x7   // default COSC is EXTOSC per FEXTOSC bits
#pragma config FEXTOSC  = 0x1   // XT - crystal between 500KHz and 8MHz

// Configuration word 1H (30 0001h)
#pragma config FCMEN    = 0x0   // we don't need the fail-safe clock monitor
#pragma config CSWEN    = 0x0   // don't allow NOSC/NDIV changes at runtime
#pragma config PR1WAY   = 0x1   // only allow one unlock/lock cycle for PRLOCKED

// Configuration word 2L (30 0002h)
#pragma config BOREN    = 0x0   // BOR off (not supported for 1.8v supply)
#pragma config LPBOREN  = 0x1   // LPBOR off (yes 1 means off for this one)
#pragma config IVT1WAY  = 0x1   // only allow one unlock/lock cycle for IVT
#pragma config MVECEN   = 0x1   // use vector table for interrupts
#pragma config PWRTS    = 0x2   // power-up timer set to 64ms

// Configuration word 2H (30 0003h)
#pragma config DEBUG    = 0x1   // debugger disabled
#pragma config STVREN   = 0x1   // reset on stack under/overflow
#pragma config PPS1WAY  = 0x0   // allow multiple unlock/lock cycles for PPS
#pragma config ZCD      = 0x1   // zero-crossing detector disabled

// Configuration word 3L (30 0004h)
#pragma config WDTE     = 0x0   // WDT disabled - TODO revisit this

// Configuration word 3H (30 0005h)
#pragma config WDTCCS   = 0x0   // WDT driven from LFINTOSC
#pragma config WDTCWS   = 0x6   // non-windowed WDT (window 100% open)

// Configuration word 4L (30 0006h)
#pragma config WRTAPP   = 0x0   // application block write-protected
#pragma config SAFEN    = 0x1   // disable storage area flash
#pragma config BBEN     = 0x1   // disable boot block (for now)

// Configuration word 4H (30 0007h)
#pragma config LVP      = 0x1   // enable low-voltage programming/MCLR pin
#pragma config WRTD     = 0x1   // data EEPROM not write-protected
#pragma config WRTC     = 0x0   // config register write-protected

// Configuration word 5L (30 0008h)
#pragma config CP       = 0x1   // code protection fully disabled

// Configuration word 5H (30 0009h)
// entire word is unimplemented