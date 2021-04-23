/*
 * altimeter.h
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#ifndef ALTIMETER_H_
#define ALTIMETER_H_

#include <DAVE.h>
#include <include/satellite.h>

typedef struct
{
	u8 msb;
	u8 lsb;
	u32 recv_counter;
	u16 altimeter_cur_val;
	u32 altimeter_sum;
	u16 altimeter_avg;
} altimeter_data_t;
void altimeter_init(altimeter_data_t* data);
void altimeter_update(altimeter_data_t* data);

#endif /* INCLUDE_SENSOR_ALTIMETER_ALTIMETER_H_ */
