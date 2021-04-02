/*
 * math.h
 *
 *  Created on: 26 Mar 2021
 *      Author: Patrick
 */

#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include <include/util/types.h>
#include <math.h>

#define RAD_TO_DEG_CONST	(f32) (180 / M_PI)
#define DEG_TO_RAD_CONST	(f32) 0.01745329251f
void validate_value(f32 *val, f32 max);

#endif /* UTIL_MATH_H_ */
