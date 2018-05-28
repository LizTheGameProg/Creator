
#ifndef _DIYPhysics_
#define _DIYPhysics_
#include "SimpleAgent.h"
#include "Fuzzy Logic.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class FuzzyLogicTutorial : public AIE_2ND_YEAR::Application
{
public:
	FuzzyLogicTutorial();
	virtual ~FuzzyLogicTutorial();

protected:
	WorldController* worldController;
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();
	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
	void FuzzyLogicExample();
};

#endif // _DIYPhysics_