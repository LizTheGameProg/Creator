#ifndef __GPUbasedParticleSystems_H_
#define __GPUbasedParticleSystems_H_

#include "Application.h"
#include "GPUParticleEmitter.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class GPUbasedParticleSystems : public AIE_2ND_YEAR::Application
{
public:

	GPUbasedParticleSystems();
	virtual ~GPUbasedParticleSystems();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	GPUParticleEmitter * m_emitter;
};

#endif // __GPUbasedParticleSystems_H_