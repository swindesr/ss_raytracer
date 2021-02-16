#include "Material.h"

Material::Material()
	: diffuse(Color()), specular(Color()), emission(Color()), shininess(0) 
{
	ambient = Color(.2f, .2f, .2f);
}

Material::Material(const Color& diffuse, const Color& specular, const Color& emission, float shininess)
	: diffuse(diffuse), specular(specular), emission(emission), shininess(shininess) 
{
	ambient = Color(.2f, .2f, .2f);
}

Material::Material(const Material& mat)
	: diffuse(mat.diffuse), 
	specular(mat.specular), 
	emission(mat.emission), 
	ambient(mat.ambient), 
	shininess(mat.shininess) {}
