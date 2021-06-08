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
	u32 recv_counter;
	u32 altimeter_sum;
	BitNumbering_t bitNumber;
	u16 altimeter_cur_val;
	u16 altimeter_avg;
} AltimeterData_t;
void altimeter_init(AltimeterData_t* data);
void altimeter_update(AltimeterData_t* data);

#endif /* INCLUDE_SENSOR_ALTIMETER_ALTIMETER_H_ */
