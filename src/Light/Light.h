#pragma once
#include "Color.h"
#include "Math/Vec3.h"

struct Attenuation {
	float constant = 1.0f;
	float linear = 0;
	float quad = 0;
};

class Light
{
public:
	// Members
	Color color;
	Vec3 pos;
	char type;
	Attenuation attenuation;

	// Constructors
	Light(const Vec3 position, const Color color, char type);
};

