/*
 * proximity_switch.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#include <DAVE.h>
#include <include/sensor/proximity/proximity_switch.h>


#ifdef PROXIMITY_IO35
#include <include/sensor/proximity/IO35/proximity_IO35.h>
#endif

void proximitInit(proximity_switch_t *proximity)
{
#ifdef PROXIMITY_IO35
	proximity_io35_init(proximity);
#endif
}

void proximityUpdate(proximity_switch_t *proximity)
{
	DIGITAL_IO_SetOutputHigh(&LED_GREEN);
#ifdef PROXIMITY_IO35
	proximity_io35_update(proximity);
#endif
	DIGITAL_IO_SetOutputLow(&LED_GREEN);
}


