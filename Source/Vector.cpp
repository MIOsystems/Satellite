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

std::string Vector3::to_string()
{
	std::stringstream ss;
	ss << this->x;
	std::string x_s = ss.str();
	ss << this->y;
	std::string y_s = ss.str();
	ss << this->z;
	std::string z_s = ss.str();

	std::string data = "X: " + x_s + " Y: " + y_s+ " Z:" + z_s;
	return data;
}

Vector2::Vector2(i32 _x, i32 _y)
{
	this->x = _x;
	this->y = _y;
}

std::string Vector2::to_string()
{
	std::stringstream ss;
	ss << this->x;
	std::string x_s = ss.str();
	ss << this->y;
	std::string y_s = ss.str();

	std::string data = "X: " + x_s + " Y: " + y_s;
	return data;
}

StatisticVector::StatisticVector(i32 _max, i32 _min, i32 _avg)
{
	this->max = _max;
	this->min = _min;
	this->avg = _avg;
}

std::string StatisticVector::to_string()
{
	std::stringstream ss;
	ss << this->max;
	std::string max_s = ss.str();
	ss << this->min;
	std::string min_s = ss.str();
	ss << this->avg;
	std::string avg_s = ss.str();
	std::string data = "MAX: " + max_s + " MIN: " + min_s + " AVG:" + avg_s;
	return data;
}

