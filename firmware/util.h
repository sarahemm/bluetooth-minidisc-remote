/* 
 * File:   util.h
 * Author: sen
 * Description: Small utilities used by other modules
 * 
 * Created on September 30, 2023, 5:03 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define pin_as_input(tris,pin)  (tris &= ~(1 << pin))
#define pin_as_output(tris,pin) (tris |= 1 << pin)
    
#define pin_low(lat,pin)        (lat &= ~(1 << pin))
#define pin_high(lat,pin)       (lat |= 1 << pin)


#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

