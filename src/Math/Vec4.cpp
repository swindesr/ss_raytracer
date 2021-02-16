#include "Vec4.h"
#include <math.h>
#include <iostream>

Vec4::Vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {}

Vec4::Vec4(float x)
	: x(x), y(x), z(x), w(x) {}

Vec4::Vec4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vec4::Vec4(const Vec4* v)
	: x(v->x), y(v->y), z(v->z), w(v->w) {}

Vec4::Vec4(const Vec3& v, float w)
	: x(v.x), y(v.y), z(v.z), w(w) {}

Vec4 Vec4::operator+(const Vec4& other) const
{
	return Vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

Vec4 Vec4::operator-(const Vec4& other) const
{
	return Vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

Vec4 Vec4::operator*(float other) const
{
	return Vec4(this->x * other, this->y * other, this->z * other, this->w * other);
}

Vec4 Vec4::operator/(float other) const
{
	return Vec4(this->x / other, this->y / other, this->z / other, this->w / other);
}

float Vec4::length() const
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float Vec4::dot(const Vec4& other) const
{
	return (
		this->x * other.x +
		this->y * other.y +
		this->z * other.z +
		this->w * other.w
		);
}

Vec4 Vec4::normalize() const
{
	Vec4 v(this);
	return v / length();
}

Vec3 operator*(const Mat4& lhs, const Vec4& rhs)
{
	return Vec3(lhs.x[0] * rhs.x + lhs.x[1] * rhs.y + lhs.x[2] * rhs.z + lhs.x[3] * rhs.w,
				lhs.y[0] * rhs.x + lhs.y[1] * rhs.y + lhs.y[2] * rhs.z + lhs.y[3] * rhs.w,
				lhs.z[0] * rhs.x + lhs.z[1] * rhs.y + lhs.z[2] * rhs.z + lhs.z[3] * rhs.w);
}

std::ostream& operator<<(std::ostream& os, const Vec4& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}
