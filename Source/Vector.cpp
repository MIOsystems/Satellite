/*
 * Vector.cpp
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#include <Header/Vector.h>

namespace Satellite {

Vector3::Vector3(f32 _x, f32 _y, f32 _z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector2::Vector2(f32 _x, f32 _y) {
	this->x = x;
	this->y = y;
}

StatisticVector::StatisticVector(f32 _max, f32 _min, f32 _avg) {
	this->max = _max;
	this->min = _min;
	this->avg = _avg;
}

} /* namespace Satellite */
