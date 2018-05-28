#ifndef __UserInterfaces_H_
#define __UserInterfaces_H_

#include "Application.h"
#include <glm/glm.hpp>

class UIRectangle;

// Derived application class that wraps up all globals neatly
class UserInterfaces : public AIE_2ND_YEAR::Application
{
public:

	UserInterfaces();
	virtual ~UserInterfaces();

protected:
	// Template stuff
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	unsigned int m_texture;

	// My variables
	glm::mat4		m_guiProjectionMatrix;
	unsigned int	m_guiShader;
	UIRectangle *	m_button;
};

#endif // __UserInterfaces_H_