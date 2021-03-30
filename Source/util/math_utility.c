/*
 * math_utility.c
 *
 *  Created on: 26 Mar 2021
 *      Author: Patrick
 */


#include <include/util/math_utility.h>


f32 inverse_sqrt(f32 x)
{
	f32 halfx = 0.5f * x;
	f32 y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(f32*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void validate_value(f32 *val, f32 max)
{
	if(*val > max) {
		*val = max;
	}
}
