#include "Vec3.h"
#include <math.h>
#include <iostream>

Vec3::Vec3(float x, float y, float z)
	: x(x), y(y), z(z) {}

Vec3::Vec3(float x)
	: x(x), y(x), z(x) {}

Vec3::Vec3()
	: x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(const Vec3* v)
	: x(v->x), y(v->y), z(v->z) {}

Vec3 Vec3::operator+(const Vec3& other) const
{
	return Vec3(this->x + other.x, this->y + other.y, this->z +other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const
{
	return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vec3 Vec3::operator*(const Vec3& other) const
{
	return cross(other);
}

Vec3 Vec3::operator*(float other) const
{
	return Vec3(this->x * other, this->y * other, this->z * other);
}


Vec3 Vec3::operator/(float other) const
{
	return Vec3(this->x / other, this->y / other, this->z / other);
}

float Vec3::length() const
{
	return sqrtf(lengthSquared());
}

float Vec3::lengthSquared() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vec3::dot(const Vec3& other) const
{
	return (
		this->x * other.x +
		this->y * other.y + 
		this->z * other.z
		);
}

Vec3 Vec3::cross(const Vec3& other) const
{
	return Vec3(
		this->y * other.z - this->z * other.y,
		this->z * other.x - this->x * other.z,
		this->x * other.y - this->y * other.x
		);
}

Vec3 Vec3::normalize() const
{
	Vec3 v(this);
	return v / length();
}

Vec3 operator*(float lhs, const Vec3& rhs)
{
	return rhs * lhs;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
