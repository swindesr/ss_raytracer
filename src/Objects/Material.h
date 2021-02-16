#pragma once
#include "Light/Color.h"

class Material
{
public:
	// Members
	Color diffuse, specular, emission, ambient;
	float shininess;

	// Constructors
	Material();
	Material(const Color& diffuse, const Color& specular, const Color& emission, float shininess);
	Material(const Material& mat);
};

