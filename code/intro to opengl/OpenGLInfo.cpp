#include "OpenGLInfo.h"
#include "gl_core_4_4.h"

OpenGLInfo::OpenGLInfo() : VAO(0), VBO(0), IBO(0)
{
	
}

OpenGLInfo::~OpenGLInfo()
{

}

void OpenGLInfo::generateOpenGLInfo()
{
	// Vertex Array Object:	VBOs and IBOs are bound to this object 
	// (I like the name Vertex Attribute Object as it defines attributes)
	glGenVertexArrays(1, &VAO);

	// Vertex Buffer Object: Vertex Information is bound to this object 
	// For example Position, Normals, TexCoords
	glGenBuffers(1, &VBO);

	// Index Buffer Object: Information about indicies is bound to this object
	glGenBuffers(1, &IBO);
}

void OpenGLInfo::deleteOpenGLInfo()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}