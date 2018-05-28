#ifndef __Planner_H_
#define __Planner_H_

#include "Application.h"
#include <glm/glm.hpp>

#include "HTN.h"

// Derived application class that wraps up all globals neatly
class Planner : public AIE_2ND_YEAR::Application
{
public:

	Planner();
	virtual ~Planner();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	Agent * m_agent;
	Task * m_task;

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __Planner_H_