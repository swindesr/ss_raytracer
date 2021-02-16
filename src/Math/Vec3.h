#pragma once
#include <iostream>

class Vec3
{
public:
	// Members
	float x, y, z;
	
	// Constructors
	Vec3(float x, float y, float z);
	Vec3(float x);
	Vec3();
	Vec3(const Vec3* v);
		
	// Overloads
	Vec3 operator + (const Vec3& other) const;
	Vec3 operator - (const Vec3& other) const;
	Vec3 operator * (const Vec3& other) const;
	Vec3 operator * (float other) const;
	friend Vec3 operator * (float lhs, const Vec3& rhs);
	Vec3 operator / (float other) const;

	// Methods
	float length() const;
	float lengthSquared() const;
	float dot(const Vec3& other) const;
	Vec3 cross(const Vec3& other) const;
	Vec3 normalize() const;
};

std::ostream& operator<<(std::ostream& os, const Vec3& v);

