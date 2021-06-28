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

void proximityIo35Init(proximity_switch_t* data);
void proximityIo35Update(proximity_switch_t* data);

#endif /* INCLUDE_SENSOR_PROXIMITY_PROXIMITY_IO35_H_ */
