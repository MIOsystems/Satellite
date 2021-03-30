/*
 * math.h
 *
 *  Created on: 26 Mar 2021
 *      Author: Patrick
 */

#ifndef MATH_UTILITY_H_
#define MATH_UTILITY_H_

#include <include/util/types.h>

typedef struct {
  f32         q0,q1,q2,q3;
} quaternion_t;


f32 inverse_sqrt(f32 x);
void validate_value(f32 *val, f32 max);

#endif /* UTIL_MATH_H_ */
