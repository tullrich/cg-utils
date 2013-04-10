#ifndef _VECTOR_H
#define _VECTOR_H

class Vector
{
public:
	float x, y, z;

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

#endif // _VECTOR_H
