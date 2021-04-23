/*
 * Proximity_IO35.h
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#ifndef PROXIMITY_IO35_H_
#define PROXIMITY_IO35_H_

#include <DAVE.h>

#include <include/sensor/proximity/proximity_switch.h>

void proximity_io35_init(proximity_switch_t* data);
void proximity_io35_update(proximity_switch_t* data);

#endif /* INCLUDE_SENSOR_PROXIMITY_PROXIMITY_IO35_H_ */
