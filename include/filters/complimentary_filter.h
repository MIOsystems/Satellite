/*
 * complimentary_filter.h
 *
 *  Created on: 23 Mar 2021
 *      Author: Patrick
 */

#ifndef COMPLIMENTARY_FILTER_H_
#define COMPLIMENTARY_FILTER_H_

#include <include/util/types.h>

#define ALPHA 	(f32) 0.1
#define DT		(f32) 0.001


void complimentary_process(const f32 Ax, const f32 Ay, const f32 Az,
							const f32 Gx, const f32 Gy, const f32 Gz,
							f32 *roll, f32 *pitch, f32 *yaw);



#endif /* COMPLIMENTARY_FILTER_H_ */
