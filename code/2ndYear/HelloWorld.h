#ifndef __HelloWorld_H_
#define __HelloWorld_H_

#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class HelloWorld : public AIE_2ND_YEAR::Application
{
public:

	HelloWorld();
	virtual ~HelloWorld();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();
	virtual void translate(glm::mat4 &transform, float deltaTime);

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	glm::mat4	m_sphereMat4;
	glm::mat4	m_sphereSun;
	glm::mat4	m_sphereMercury;
	glm::mat4	m_sphereVenus;
	glm::mat4	m_VenusOffset;
	glm::mat4	m_sphereNeith;
	glm::mat4	m_NeithOffset;
};

#endif // __HelloWorld_H_