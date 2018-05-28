#pragma once

#include <glm/ext.hpp>
class DirectionalLight
{
public:
	DirectionalLight(void);
	~DirectionalLight(void);

	
	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 specular;
};

