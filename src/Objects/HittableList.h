#pragma once
#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
	// Members
	std::vector<shared_ptr<Hittable>> objects;

	// Constructors
	HittableList();
	HittableList(shared_ptr<Hittable> object);

	// Methods
	void clear();
	void add(shared_ptr<Hittable> object);

	virtual bool intersects(Ray& r, Intersection& i) const override;
};

