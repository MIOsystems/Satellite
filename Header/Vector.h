/*
 * Vector.h
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <string>

#include <Header/Types.h>

class Vector3 {
	private:
		i32 x;
		i32 y;
		i32 z;
	public:
		Vector3(i32 _x, i32 _y, i32 _z);
		i32 getX() const;
		void setX(i32 x);
		i32 getY() const;
		void setY(i32 y);
		i32 getZ() const;
		void setZ(i32 z);
		std::string to_string();
};

class Vector2 {
	private:
		i32 x;
		i32 y;
	public:
		Vector2(i32 _x, i32 _y);
		std::string to_string();
};

class StatisticVector {
	private:
		i32 max;
		i32 min;
		i32 avg;

	public:
		StatisticVector(i32 _max, i32 _min, i32 _avg);
		std::string to_string();

};

#endif /* VECTOR3_H_ */
