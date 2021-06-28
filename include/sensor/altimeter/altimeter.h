/*
 * altimeter.h
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#ifndef ALTIMETER_H_
#define ALTIMETER_H_

#include <DAVE.h>
#include <include/util/model.h>
#include <include/satellite.h>

typedef struct
{
	u32 recvCounter;
	u32 altimeterSum;
	u16 altimeterCurValue;
	BitNumbering_t bitNumber;
	u16 altimeterAvg;
} AltimeterData_t;

void altimeterInit(AltimeterData_t* data);
void altimeterUpdate(AltimeterData_t* data);

#endif /* INCLUDE_SENSOR_ALTIMETER_ALTIMETER_H_ */
