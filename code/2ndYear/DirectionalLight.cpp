#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(void)
{
	direction = glm::vec3(10,10,10);
	position = -direction;
	colour = glm::vec3(0.1, 1, 0.5);
	specular = colour;
}


DirectionalLight::~DirectionalLight(void)
{
}
