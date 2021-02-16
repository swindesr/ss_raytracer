#include "Scene.h"
#include "Light/Color.h"
#include "variables.h"

Scene::Scene(const Sampler& sampler, const Painter& painter, const Camera& camera, const RayTracer& rt)
    : sampler_(sampler), painter_(painter), camera_(camera), ray_tracer_(rt) {}

// Loop through every pixel, trace its ray, and paint it
void Scene::render()
{
	Sample s(0, 0);
    int pixel_number = 0;

	while (sampler_.getSample(s)) {       
        Ray r(Vec3(), Vec3(), 0, INFINITY_F);
        Color c(0);

        camera_.makeRay(s, r);
        ray_tracer_.traceRay(r, c);
        painter_.paint(pixel_number, c);

        pixel_number++;
	}
}