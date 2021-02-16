#pragma once
#include "Math/Ray.h"
#include "Material.h"
#include "Math/Mat4.h"

struct Intersection
{
	Vec3 pos;
	Vec3 norm;
	double t;
	Material mat;
};

class Hittable
{
public:
	// Members
	Mat4 transform;
	Mat4 inverse_transform;
	Mat3 normal_transform;

	// Constructors
	Hittable();

	// Methods
	virtual bool intersects(Ray& r, Intersection& i) const = 0;
};

