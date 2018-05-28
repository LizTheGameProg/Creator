#pragma once

#include <glm/ext.hpp>
#include <list>

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
		glm::vec2	texCord;
	};

class ParticleEmitter
{
public:

	ParticleEmitter();
	virtual ~ParticleEmitter();
	void initalise(unsigned int a_maxParticles, unsigned int a_emitRate, 
								float a_lifetimeMin, float a_lifetimeMax, 
								float a_velocityMin, float a_velocityMax, 
								float a_startSize, float a_endSize, 
								const glm::vec4& a_startColour, const glm::vec4& a_endColour,
								char * texturePath, char * vertPath, char * fragPath, const char* inputs[], const char * outputs[]);
	void emit();
	void update(float a_deltaTime, const glm::mat4& a_cameraTransform);
	void draw(glm::mat4 a_viewMatrix, glm::mat4 a_projectionMatrix);
protected:

	std::list<Particle*>	m_aliveParticles;
	std::list<Particle*>	m_deadParticles;
	Particle*		m_particles;

private:

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

	unsigned int m_texture;
	unsigned int m_shader;
	
};

