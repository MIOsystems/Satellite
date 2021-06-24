/*
 * sf30.h
 *
 *  Created on: 23 Apr 2021
 *      Author: Patrick
 */

#ifndef SF30_H_
#define SF30_H_

#include <DAVE.h>
#include <include/satellite.h>
#include <include/util/types.h>
#include <include/sensor/altimeter/altimeter.h>

void sf30_init(AltimeterData_t* data);
void sf30_update(AltimeterData_t* data);
void sf30_rx_handle();
void sf30_get_distance(AltimeterData_t* data);
void sf30_reset(AltimeterData_t* data);

#endif /* SF30_H_ */
