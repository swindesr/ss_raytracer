#include "Color.h"

Color::Color()
	: r(0), g(0), b(0) {}

Color::Color(float v)
	: r(v), g(v), b(v) {}

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b) {}

Color Color::operator+(const Color& other) const
{
	return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator-(const Color& other) const
{
	return Color(r - other.r, g - other.g, b - other.b);
}

Color Color::operator*(const Color& other) const
{
	return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator*(const float scalar) const
{
	return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator/(const float scalar) const
{
	return *this * (1/scalar);
}

Color& Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}
