#ifndef __Tessellation_H_
#define __Tessellation_H_

#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Tessellation : public AIE_2ND_YEAR::Application
{
public:

	Tessellation();
	virtual ~Tessellation();

protected:

	unsigned int m_vao, m_vbo, m_ibo;

	unsigned int m_texture;
	unsigned int m_displacement;

	unsigned int m_shader;
	
	float m_time;

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __Tessellation_H_