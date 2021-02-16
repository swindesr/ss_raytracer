#pragma once
#include "Light/Color.h"
#include "Math/Ray.h"
#include "Objects/Sphere.h"
#include <vector>
#include "Light/Light.h"
#include "Objects/HittableList.h"

class RayTracer
{
public:
	// Constructors
	RayTracer(const HittableList& world, const std::vector<Light> lights, int maxDepth);

	// Methods
	void traceRay(Ray& r, Color& c);

private:
	// Members
	HittableList world_;
	std::vector<Light> lights_;
	int max_depth_;

	// Methods
	Color getColor(const Ray& r, Intersection i, int depth);
	Color computeLight(const Vec3& normal, const Vec3& direction, const Vec3& half_angle, const Material& material) const;
	Ray getReflectedRay(const Intersection& i, const Ray& r) const;
};

