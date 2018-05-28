#pragma once

#include <glm/glm.hpp>


struct Particle
	{
		glm::vec3	position;
		glm::vec3	velocity;
		glm::vec4	colour;
		float		size;
		float		lifetime;
		float		lifespan;
	};
	
	struct ParticleVertex
	{
		glm::vec4	position;
		glm::vec4	colour;
	};

class ParticleSystem
{
public:
	ParticleSystem(void);
	~ParticleSystem(void);

	

};

