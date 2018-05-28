#ifndef __Tutorial2_H_
#define __Tutorial2_H_

#include "Application.h"
#include <glm/glm.hpp>



// Derived application class that wraps up all globals neatly
class Tutorial2 : public AIE_2ND_YEAR::Application
{
public:

	Tutorial2();
	virtual ~Tutorial2();

protected:
	//\============================================================================
	//\ A Simple Vertex Structure
	//\  - Two integers for position
	//\  - Four floats for colour (colour is required to be a float array of 16 bytes 
	//\    length in all recent versions of openGL)
	//\============================================================================
	struct V_4v_4c
	{
	    glm::vec4 position;
	    glm::vec4 colour;
	};

	//Our vertex and index buffers
	unsigned int	m_VAO;
	unsigned int 	m_VBO;
	unsigned int	m_IBO;

	unsigned int	m_programID;

	unsigned int	m_rows;
	unsigned int	m_cols;

	float			m_time;

	virtual void GenerateGrid(unsigned int rows, unsigned int cols);

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __Tutorial2_H_