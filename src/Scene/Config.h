#pragma once
#include "Camera.h"
#include <vector>
#include "Objects/HittableList.h"
#include "Light/Light.h"

class Config
{
public:
	// Members
	int width, height, max_ray_depth;
	std::string filename;
	Camera camera;
	std::vector<Light> lights;
	std::vector<Vec3> vertices;
	HittableList objects;
	Attenuation attenuation;
	Material mat;

	// Constructor
	Config();
};

