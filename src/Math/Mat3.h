#pragma once
#include "Vec3.h"
#include "Mat4.h"

class Mat4;
class Mat3
{
public:
	// Members
	float x[3], y[3], z[3];

	// Constructors
	Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	Mat3(float n);
	Mat3(const Mat4& m);
	Mat3();

	// Methods
	Mat3 operator + (const Mat3& other) const;
	Vec3 operator * (const Vec3& other) const;
	friend Mat3 operator * (float lhs, const Mat3& rhs);
	
	Mat3 inverse() const;
	Mat3 transpose() const;
};

