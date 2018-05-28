#ifndef __Texturing_H_
#define __Texturing_H_

#include "Application.h"
#include <SOIL.h>
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Texturing : public AIE_2ND_YEAR::Application
{
public:

	Texturing();
	virtual ~Texturing();

protected:
	// a basic vertex structure supporting position, colour and texture coordinate
	struct BasicVertex
	{
		glm::vec4 position;
		glm::vec4 colour;
		glm::vec2 texCoord;
	};

	unsigned int m_texture;

	unsigned int m_vao,m_vbo,m_ibo;

	unsigned int m_vertShader, m_fragShader, m_shader;

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __Texturing_H_