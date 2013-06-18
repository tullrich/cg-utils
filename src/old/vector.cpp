#include "vector.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace cgutils
{


Vector::Vector() : x(0.0), y(0.0), z(0.0) {}

Vector::Vector(float x) : x(x), y(0.0), z(0.0) {}

Vector::Vector(float x, float y) : x(x), y(y), z(0.0) {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector Vector::operator+(const Vector v)
{
	Vector temp;

	temp.x = x + v.x;
	temp.y = y + v.y;
	temp.z = z + v.z;

	return temp;
}

Vector Vector::operator-(const Vector v)
{
	Vector temp;

	temp.x = x - v.x;
	temp.y = y - v.y;
	temp.z = z - v.z;

	return temp;
}

Vector Vector::operator*(const float s)
{
	Vector temp;

	temp.x = x * s;
	temp.y = y * s;
	temp.z = z * s;

	return temp;
}

Vector Vector::operator/(const float s)
{
	Vector temp;

	temp.x = x / s;
	temp.y = y / s;
	temp.z = z / s;

	return temp;
}


float Vector::dot(const Vector v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::cross(const Vector v)
{	
	Vector temp;

	temp.x = y * v.z - z * v.y;
	temp.y = z * v.x - x * v.z;
	temp.z = x * v.y - y * v.x;

	return temp;
}

float Vector::magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float& Vector::operator[](int index)
{
	if (index == 0)
	{
		return x;
	} 
	else if (index == 1)
	{
		return y;
	}
	else if (index == 2)
	{
		return z;
	}

	throw std::out_of_range ("bad index " + index);
}

} /* namespace cgutils */