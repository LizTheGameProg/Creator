#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <glm/glm.hpp>
#include <list>

class ParticleSystem
{
public:
	ParticleSystem(void);
	~ParticleSystem(void);

	void initalise(	unsigned int maxParticles,		unsigned int emitRate, 
					float lifetimeMin,				float lifetimeMax, 
					float velocityMin,				float velocityMax, 
					float startSize,				float endSize, 
					const glm::vec4& startColour,	const glm::vec4& endColour);

	void update(float deltaTime, const glm::mat4& cameraTransform);
	void draw();

private:
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

	void emit();

	std::list<Particle*>	m_aliveParticles;
	std::list<Particle*>	m_deadParticles;
	Particle*		m_particles;

	unsigned int	m_vao, m_vbo, m_ibo;
	ParticleVertex*	m_vertexData;
	unsigned int*	m_indexData;

	glm::vec3	m_position;

	float		m_emitTimer;
	float		m_emitRate;

	float		m_lifespanMin;
	float		m_lifespanMax;

	float		m_velocityMin;
	float		m_velocityMax;

	float		m_startSize;
	float		m_endSize;

	glm::vec4	m_startColour;
	glm::vec4	m_endColour;
};

#endif