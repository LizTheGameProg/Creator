#ifndef __Particle_Systems_H_
#define __Particle_Systems_H_

#include "Application.h"
#include "ParticleEmitter.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Particle_Systems : public AIE_2ND_YEAR::Application
{
public:

	Particle_Systems();
	virtual ~Particle_Systems();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	ParticleEmitter * m_emitter;
	unsigned int m_textureGrid;
	unsigned int m_vertShader;
	unsigned int m_fragShader;
	unsigned int m_shader;
};

#endif // __Particle_Systems_H_