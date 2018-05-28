#pragma once

#include <glm/glm.hpp>

class PointLight
{
public:
	PointLight(void);
	~PointLight(void);
	void attenuation(glm::vec3 p);

	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 specular;
};

