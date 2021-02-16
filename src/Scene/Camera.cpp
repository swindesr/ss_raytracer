#include "Camera.h"
#include "Sampler.h"
#include "variables.h"

Camera::Camera(const Vec3 eye, const Vec3 center, const Vec3 up, float fovy, float aspect)
{
	float theta = degreesToRadians(fovy);
	float h = tan(theta / 2);
	float view_height = 2 * h;
	float view_width = aspect * view_height;

	// Basis for coordinate frame
	const Vec3 w = (eye - center).normalize();
	const Vec3 u = (up * w).normalize();
	const Vec3 v = u * w;

	// Set eye location and viewport size
	origin_ = eye;
	horizontal_ = u * view_width;
	vertical_ = v * view_height;

	// Hold onto lower left corner of viewport
	// Method described at: https://raytracing.github.io/books/RayTracingInOneWeekend.html#rays,asimplecamera,andbackground/sendingraysintothescene
	lower_left_ = origin_ - (horizontal_ / 2.0f) - (vertical_ / 2.0f) - w;
}

Camera::Camera() {}

// Shoot ray from eye to pixel location defined by sample
void Camera::makeRay(const Sample s, Ray& r) const
{
	Vec3 dir = lower_left_ + (horizontal_ * s.x) + (vertical_ * s.y) - origin_;
	r = Ray(origin_, dir, 0, INFINITY_F);
}
