#include "Sphere.h"
#include <algorithm>
#include "Math/Vec4.h"

Sphere::Sphere()
	: radius(0.0f), center(Vec3(0.0f)), mat(Material()) {}

Sphere::Sphere(float rad, const Vec3& center, const Material& mat)
	: radius(rad), center(center), mat(mat) {}

bool Sphere::intersects(Ray& r, Intersection& i) const
{
	// Solve for root, quadratic formula
	Vec3 oc(r.p - center);
	float a = r.dir.lengthSquared();
	float halfb = oc.dot(r.dir);
	float c = oc.lengthSquared() - radius * radius;

	// Get discriminant, if negative sphere is behind us
	float disc = halfb * halfb - a * c;
	if (disc < 0) return false;

	// Find nearest root and record if within range limits
	float sqrt_d = sqrtf(disc);
	float root = (-halfb - sqrt_d) / a;

	// Only count intersection if closest yet and outside min range
	// Populate the intersection record
	if (root < r.t_max && root > r.t_min) {
		i.t = root;
		i.pos = r.at(root);
		i.norm = (normal_transform * (i.pos - center).normalize()).normalize();
		i.pos = transform * Vec4(i.pos, 1.0f);
		i.mat = mat;

		return true;
	}

	return false;
}
