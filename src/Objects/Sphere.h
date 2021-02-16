#pragma once
#include "Math/Vec3.h"
#include "Math/Ray.h"
#include "Material.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	// Members
	float radius;
	Vec3 center;
	Material mat;

	// Constructors
	Sphere();
	Sphere(float rad, const Vec3& center, const Material& mat);

	// Methods
	virtual bool intersects(Ray& r, Intersection& i) const override;
};

