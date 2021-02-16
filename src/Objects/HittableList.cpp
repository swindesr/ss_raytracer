#include "HittableList.h"
#include "Vec4.h"

HittableList::HittableList() {}

HittableList::HittableList(shared_ptr<Hittable> object)
{
	add(object);
}

void HittableList::clear()
{
	objects.clear();
}

void HittableList::add(shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

// Find nearest object intersection, if exists.
// Note on intersection methodology: 
//	 We store objects in their own local space so we must transform 
//   the ray to move it into object space. This also results in needing 
//   to transform the intersection record, which we handle in each objects 
//   intersect implementation.
bool HittableList::intersects(Ray& r, Intersection& i) const
{
	Intersection tempI;
	bool found_hit = false;
	
	for (const auto& obj : objects) {
		// Apply inverse transforms to ray to move it into object space
		Vec3 transformed_origin = obj->inverse_transform * Vec4(r.p, 1.0f);
		Vec3 transformed_dir = obj->inverse_transform * Vec4(r.dir, 0);
		Ray tranformed_ray(transformed_origin, transformed_dir, r.t_min, r.t_max);

		// If intersection hit, store it
		if (obj->intersects(tranformed_ray, tempI)) {
			found_hit = true;
			r.t_max = tempI.t;
			i = tempI;
		}
	}

	return found_hit;
}
