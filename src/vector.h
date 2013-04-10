#ifndef _VECTOR_H
#define _VECTOR_H

#include "swizzle.hpp"

namespace cgutils
{

class Vector
{
public:
	union
	{
		struct {float x, y, z;};
		_GLM_SWIZZLE3_3_MEMBERS(float, Vector, x, y, z)
	};

	Vector();
	Vector(float x, float y, float z);

	Vector operator+(const Vector v);
	Vector operator-(const Vector v);
	Vector operator*(const float s);
	Vector operator/(const float s);

	float dot(const Vector v);
	float magnitude();
	Vector cross(const Vector v);
	
	float& operator[] (int x);
};

} /* namespace cgutils */

#endif /* _VECTOR_H */