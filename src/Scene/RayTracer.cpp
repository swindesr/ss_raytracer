#include "RayTracer.h"
#include "variables.h"
#include <algorithm>

RayTracer::RayTracer(const HittableList& world, const std::vector<Light> lights, int maxDepth)
	: world_(world), lights_(lights), max_depth_(maxDepth) {}

void RayTracer::traceRay(Ray& r, Color& c)
{
	Intersection i;
	if (world_.intersects(r, i)) {
		c = i.mat.ambient + i.mat.emission + getColor(r, i, max_depth_);

		// FOR DEBUGGING: Color according to normals
		// c =  Color(i.norm.x + 1, i.norm.y + 1, i.norm.z + 1) * .5;
	}
}

Color RayTracer::getColor(const Ray& r, Intersection i, int depth)
{
	// Initialize as black, build up from here
	Color col(0);

	// Exit if max ray depth achieved
	if (depth <= 0) return col;

	Vec3 eye_pos = r.p;
	Vec3 eye_direction = (eye_pos - i.pos).normalize();

	// Add color from every light
	for (const Light light : lights_) {
		Vec3 light_direction = light.type == 'p' ?
			(light.pos - i.pos) :
			light.pos;

		float dist = light_direction.length();
		light_direction = light_direction.normalize();

		// Check light visibility by sending ray at light
		Ray shadowRay(i.pos + i.norm * EPSILON, light_direction, 0, dist);
		if (light.type == 'd') {
			shadowRay.t_max = INFINITY_F;
		}
		Intersection i2;
		bool visible = !world_.intersects(shadowRay, i2);

		// Only process if light is visible
		if (visible) {
			Vec3 half_theta = (light_direction + eye_direction).normalize();
			Color computed_color = computeLight(i.norm, light_direction, half_theta, i.mat);

			// Point lights need attenuation
			if (light.type == 'p') {
				float attenuation = (light.attenuation.constant + light.attenuation.linear * dist + light.attenuation.quad * (dist * dist));
				col += light.color / attenuation * computed_color;
			}
			else {
				col += light.color * computed_color;
			}
		}
	}	

	// Reflect ray over intersection and get reflections based on specular strength
	Ray reflected_ray = getReflectedRay(i, r);
	Intersection i3;
	if (world_.intersects(reflected_ray, i3)) {
		col += i.mat.specular * getColor(reflected_ray, i3, depth-1);
	}

	return col;
}

// Compute diffuse and specular components
Color RayTracer::computeLight(const Vec3& normal, const Vec3& direction, const Vec3& half_angle, const Material& material) const
{
	float n_dot_l = normal.dot(direction);
	Color lambert = material.diffuse * std::max(n_dot_l, 0.0f);

	float n_dot_h = normal.dot(half_angle);
	Color phong = material.specular * pow(std::max(n_dot_h, 0.0f), material.shininess);

	return lambert + phong;
}

// Reflect ray across intersection normal
Ray RayTracer::getReflectedRay(const Intersection& i, const Ray& r) const
{
	Vec3 direction(r.dir - 2 * r.dir.dot(i.norm) * i.norm);
	return Ray(i.pos + i.norm * EPSILON, direction.normalize(), 0, INFINITY_F);
}
