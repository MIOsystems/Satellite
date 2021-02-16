/*
 * Vector.h
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <Header/Types.h>
namespace Satellite {

class Vector3 {
	private:
		f32 x;
		f32 y;
		f32 z;
	public:
		Vector3(f32 _x, f32 _y, f32 _z);

};

class Vector2 {
	private:
		f32 x;
		f32 y;
	public:
		Vector2(f32 _x, f32 _y);
};

class StatisticVector {
	private:
		f32 max;
		f32 min;
		f32 avg;

	public:
		StatisticVector(f32 _max, f32 _min, f32 _avg);

};
} /* namespace Satellite */

#endif /* VECTOR3_H_ */
