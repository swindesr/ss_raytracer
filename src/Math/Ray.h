#pragma once
#include "Vec3.h"

class Ray
{
public:
	// Members
	Vec3 p;
	Vec3 dir;
	float t_min, t_max;

	// Constructors
	Ray();
	Ray(Vec3 p, Vec3 dir, float min, float max);

	// Methods
	Vec3 at(float t) const;
};

