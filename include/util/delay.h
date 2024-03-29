#ifndef DELAY_H_
#define DELAY_H_

#include <include/util/delay.h>
#include <include/util/types.h>

/**
 * Delays the system for the ms specified
 * @param ms the amount of milliseconds
 */
void delayMs(u32 ms);

/**
 * Delays the system for the sec specified
 * @param ms the amount of milliseconds
 */
void delaySec(u32 sec);


#endif
