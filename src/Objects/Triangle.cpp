#include "Triangle.h"
#include "Math/Vec4.h"

Triangle::Triangle(const Vec3& a, const Vec3& b, const Vec3& c, const Material& mat)
	: a(a), b(b), c(c), mat(mat)
{
	norm = ((b - a) * (c - a)).normalize();
}

bool Triangle::intersects(Ray& r, Intersection& i) const
{
	// Intersect ray with plane encompassing triangle
	float t = (a.dot(norm) - r.p.dot(norm)) / (r.dir.dot(norm));
	if (isinf(t)) return false;
	
	Vec3 intesect_point = r.at(t);

	// Check if point is inside triangle
	// Here is some explanation: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	if (((b - a) * (intesect_point - a)).dot(norm) < 0) return false;
	if (((c - b) * (intesect_point - b)).dot(norm) < 0) return false;
	if (((a - c) * (intesect_point - c)).dot(norm) < 0) return false;

	// Only count intersection if closest yet and outside min range
	// Populate the intersection record 
	if (t < r.t_max && t > r.t_min) {
		i.t = t;
		i.pos = transform * Vec4(intesect_point, 1.0f);
		i.norm = (normal_transform * norm).normalize();
		i.mat = mat;
		return true;
	}

	return false;
}
