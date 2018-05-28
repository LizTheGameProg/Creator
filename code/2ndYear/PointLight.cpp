#include "PointLight.h"


PointLight::PointLight(void)
{
	position = glm::vec3(3,3,3);
	colour = glm::vec3(0.1, 1, 0.5);
	specular = colour;
}


PointLight::~PointLight(void)
{

}