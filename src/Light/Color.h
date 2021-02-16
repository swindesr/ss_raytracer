#pragma once
class Color
{
public:
	// Members
	float r, g, b;

	// Constructors
	Color();
	Color(float v);
	Color(float r, float g, float b);

	// Methods
	Color operator + (const Color& other) const;
	Color operator - (const Color& other) const;
	Color operator * (const Color& other) const;
	Color operator * (const float scalar) const;
	Color operator / (const float scalar) const;
	Color& operator += (const Color& other);
};

