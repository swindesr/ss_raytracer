#pragma once
#include "Math/Vec3.h"
#include "Sampler.h"
#include "Painter.h"
#include "Camera.h"
#include "RayTracer.h"
#include "Objects/Sphere.h"

class Scene
{
public:
	// Constructors
	Scene(const Sampler& sampler, const Painter& painter, const Camera& camera, const RayTracer& rt);

	// Methods
	void render();

private:
	// Members
	Sampler sampler_;
	Painter painter_;
	Camera camera_;
	RayTracer ray_tracer_;
};