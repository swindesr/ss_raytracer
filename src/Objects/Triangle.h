#pragma once
#include "Hittable.h"

class Triangle : public Hittable
{
public:
	// Members
	Vec3 a, b, c;
	Vec3 norm;
	Material mat;

	// Constructors
	Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Material& mat);

	// Methods
	virtual bool intersects(Ray& r, Intersection& i) const override;
};

