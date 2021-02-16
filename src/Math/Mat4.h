#pragma once
#include "Mat3.h"

class Mat3;
class Mat4
{
public:
	// Members
	float x[4], y[4], z[4], w[4];

	// Constructors
	Mat4(float aa, float ab, float ac, float ad, 
		 float ba, float bb, float bc, float bd, 
		 float ca, float cb, float cc, float cd,
		 float da, float db, float dc, float dd);
	Mat4(float n);
	Mat4(const Mat3& m);
	Mat4();

	// Methods
	Mat4 operator * (const Mat4& other) const;

	Mat4 transpose() const;
	Mat4 inverse() const;
};

