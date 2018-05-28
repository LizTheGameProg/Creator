#ifndef __SceneManagement_H_
#define __SceneManagement_H_

#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class SceneManagement : public AIE_2ND_YEAR::Application
{
public:

	SceneManagement();
	virtual ~SceneManagement();

protected:
	// Standard Template stuff
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	// My variables
	

	// My Functions
	int planeSphereTest(const glm::vec4 & a_plane, 
						const glm::vec3 & a_centre, 
						float a_radius);
	void getFrustumPlanes(const glm::mat4 & a_transform, glm::vec4 * a_planes);
};

#endif // __SceneManagement_H_