#pragma once
#include <iostream>
#include "Vec3.h"
#include "Mat4.h"

class Vec4
{
public:
	// Members
	float x, y, z, w;

	// Constructors
	Vec4(float x, float y, float z, float w);
	Vec4(float x);
	Vec4();
	Vec4(const Vec4* v);
	Vec4(const Vec3& v, float w);
	
	// Overloads
	Vec4 operator + (const Vec4& other) const;
	Vec4 operator - (const Vec4& other) const;
	Vec4 operator * (float other) const;
	Vec4 operator / (float other) const;
	friend Vec3 operator * (const Mat4& lhs, const Vec4& rhs);

	// Methods
	float length() const;
	float dot(const Vec4& other) const;
	Vec4 normalize() const;
};

std::ostream& operator<<(std::ostream& os, const Vec4& v);

