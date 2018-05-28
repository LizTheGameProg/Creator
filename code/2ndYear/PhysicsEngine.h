#ifndef __PhysicsEngine_H_
#define __PhysicsEngine_H_

#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class PhysicsEngine : public AIE_2ND_YEAR::Application
{
public:

	PhysicsEngine();
	virtual ~PhysicsEngine();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __PhysicsEngine_H_