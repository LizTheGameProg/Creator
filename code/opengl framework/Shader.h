#pragma once
//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	18/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	08/09/2015
//--------------------------------

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	
	// Loads the shaders from file, generates a program which is bound to programID
	void Load(const GLchar * vertexPath, const GLchar* fragmentPath);
    
	// Uses the current shader
	void Use();
	
	// ID of the shader program assigned by glfw (openGL)
	GLuint programID;
};