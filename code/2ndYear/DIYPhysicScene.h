#ifndef DIYPhysicScene_H
#define DIYPhysicScene_H

#include "Application.h"
#include <glm/glm.hpp>

class Scene;

// Derived application class that wraps up all globals neatly
class DIYPhysicScene : public AIE_2ND_YEAR::Application
{
public:

	DIYPhysicScene();
	virtual ~DIYPhysicScene();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	Scene * m_scene;

};

#endif // ___2DPhysicsEngine_H_