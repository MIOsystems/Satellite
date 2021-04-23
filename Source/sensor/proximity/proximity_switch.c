/*
 * proximity_switch.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#include <DAVE.h>
#include <include/sensor/proximity/proximity_switch.h>


#ifdef IO35
#include <include/sensor/proximity/IO35/proximity_IO35.h>
#endif

void proximity_init(proximity_switch_t *proximity)
{
#ifdef IO35
	proximity_io35_init(proximity);
#endif
}

void proximity_update(proximity_switch_t *proximity)
{
#ifdef IO35
	proximity_io35_update(proximity);
#endif
}


