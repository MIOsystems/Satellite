/*
 * validate_digital_out.h
 *
 *  Created on: 9 Apr 2021
 *      Author: Patrick
 */

#ifndef VALIDATE_DIGITAL_OUT_H_
#define VALIDATE_DIGITAL_OUT_H_

#include <DAVE.h>

#include <include/util/types.h>
#include <include/validation/validate_model.h>

void validate_digital_out_init();
void validate_digital_out_update(validate_dig_out_t *d_out);

#endif /* VALIDATE_DIGITAL_OUT_H_ */
