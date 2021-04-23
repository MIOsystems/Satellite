/*
 * proximity.h
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#ifndef PROXIMITY_SWITCH_H_
#define PROXIMITY_SWITCH_H_

#include <include/util/types.h>

#include <include/satellite.h>

typedef struct proximity_switch_t
{
	u16 distance;
} proximity_switch_t;

void proximity_init(proximity_switch_t *proximity);
void proximity_update(proximity_switch_t *proximity);

#endif /* PROXIMITY_H_ */
