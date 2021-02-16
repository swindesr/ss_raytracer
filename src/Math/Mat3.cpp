#include "Mat3.h"

Mat3::Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	x[0] = a;
	x[1] = b;
	x[2] = c;
	y[0] = d;
	y[1] = e;
	y[2] = f;
	z[0] = g;
	z[1] = h;
	z[2] = i;
}

Mat3::Mat3(float n)
{
	x[0] = n;
	x[1] = 0;
	x[2] = 0;
	y[0] = 0;
	y[1] = n;
	y[2] = 0;
	z[0] = 0;
	z[1] = 0;
	z[2] = n;
}

Mat3::Mat3(const Mat4& m)
{
	x[0] = m.x[0];
	x[1] = m.x[1];
	x[2] = m.x[2];
	y[0] = m.y[0];
	y[1] = m.y[1];
	y[2] = m.y[2];
	z[0] = m.z[0];
	z[1] = m.z[1];
	z[2] = m.z[2];
}

Mat3::Mat3()
{
	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
	y[0] = 0;
	y[1] = 0;
	y[2] = 0;
	z[0] = 0;
	z[1] = 0;
	z[2] = 0;
}

Mat3 Mat3::operator+(const Mat3& other) const
{
	return Mat3(x[0] + other.x[0], x[1] + other.x[1], x[2] + other.x[2],
				y[0] + other.y[0], y[1] + other.y[1], y[2] + other.y[2],
				z[0] + other.z[0], z[1] + other.z[1], z[2] + other.z[2]);
}

Vec3 Mat3::operator*(const Vec3& other) const
{
	return Vec3(x[0] * other.x + x[1] * other.y + x[2] * other.z,
				y[0] * other.x + y[1] * other.y + y[2] * other.z,
				z[0] * other.x + z[1] * other.y + z[2] * other.z);
}

Mat3 Mat3::inverse() const
{
	// computes the inverse of a matrix m
	float det = x[0] * (y[1] * z[2] - z[1] * y[2]) -
				x[1] * (y[0] * z[2] - y[2] * z[0]) +
				x[2] * (y[0] * z[1] - y[1] * z[0]);

	float invdet = 1 / det;

	return Mat3((y[1] * z[2] - z[1] * y[2]) * invdet,
				(x[2] * z[1] - x[1] * z[2]) * invdet,
				(x[1] * y[2] - x[2] * y[1]) * invdet,
				(y[2] * z[0] - y[0] * z[2]) * invdet,
				(x[0] * z[2] - x[2] * z[0]) * invdet,
				(y[0] * x[2] - x[0] * y[2]) * invdet,
				(y[0] * z[1] - z[0] * y[1]) * invdet,
				(z[0] * x[1] - x[0] * z[1]) * invdet,
				(x[0] * y[1] - y[0] * x[1]) * invdet);
}

Mat3 Mat3::transpose() const
{
	return Mat3(x[0], y[0], z[0],
				x[1], y[1], z[1],
				x[2], y[2], z[2]);
}

Mat3 operator*(float lhs, const Mat3& rhs)
{
	return Mat3(lhs * rhs.x[0], lhs * rhs.x[1], lhs * rhs.x[2],
				lhs * rhs.y[0], lhs * rhs.y[1], lhs * rhs.y[2],
				lhs * rhs.z[0], lhs * rhs.z[1], lhs * rhs.z[2]);
}
