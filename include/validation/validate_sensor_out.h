/*
 * validate_sensor_out.h
 *
 *  Created on: 22 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_SENSOR_OUT_H_
#define VALIDATE_SENSOR_OUT_H_

#include <DAVE.h>
#include <include/util/types.h>
#include <include/validation/validate_model.h>

void validate_sensor_out_init();
void validate_sensor_out_update(validate_sout_t* data);

#endif /* VALIDATE_SENSOR_OUT_H_ */
