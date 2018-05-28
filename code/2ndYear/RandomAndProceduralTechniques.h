#ifndef __RandomAndProceduralTechniques_H_
#define __RandomAndProceduralTechniques_H_

#include "Application.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class RandomAndProceduralTechniques : public AIE_2ND_YEAR::Application
{
public:

	RandomAndProceduralTechniques();
	virtual ~RandomAndProceduralTechniques();

protected:
	// Template stuff
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	// My variables
	unsigned int m_vao, m_vbo, m_ibo;
	unsigned int m_shader;
	float * m_height;
	glm::ivec2 m_dimensions;
	unsigned int m_texture;

};

#endif // __RandomAndProceduralTechniques_H_