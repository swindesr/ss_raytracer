#include "Ray.h"

Ray::Ray()
	: p(Vec3()), dir(Vec3()), t_min(0), t_max(0) {}

Ray::Ray(Vec3 p, Vec3 dir, float min, float max)
	: p(p), dir(dir), t_min(min), t_max(max) {}

Vec3 Ray::at(float t) const
{
	return p + dir * t;
}
