#pragma once
#include "Math/Ray.h"
#include "Sampler.h"

class Camera
{
public:
	// Constructors
	Camera(const Vec3 eye, const Vec3 center, const Vec3 up, float fovy, float aspect);
	Camera();

	// Methods
	void makeRay(const Sample s, Ray& r) const;

private:
	// Members
	Vec3 origin_, horizontal_, vertical_, lower_left_;
};

