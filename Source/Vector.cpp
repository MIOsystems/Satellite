/*
 * Vector.cpp
 *
 *  Created on: 16 Feb 2021
 *      Author: Patrick
 */
#include <string>
#include <sstream>
#include <Header/Vector.h>

Vector3::Vector3(i32 _x, i32 _y, i32 _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


i32 Vector3::getX() const
{
	return x;
}

void Vector3::setX(i32 x)
{
	this->x = x;
}

i32 Vector3::getY() const
{
	return y;
}

void Vector3::setY(i32 y)
{
	this->y = y;
}

i32 Vector3::getZ() const
{
	return z;
}

void Vector3::setZ(i32 z)
{
	this->z = z;
}


Vector2::Vector2(i32 _x, i32 _y)
{
	this->x = _x;
	this->y = _y;
}

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

StatisticVector::StatisticVector()
{
	this->max = 0;
	this->min = 0;
	this->avg = 0;
}

StatisticVector::StatisticVector(i32 _max, i32 _min, i32 _avg)
{
	this->max = _max;
	this->min = _min;
	this->avg = _avg;
}

