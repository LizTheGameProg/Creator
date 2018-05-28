#pragma once
//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	18/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	18/08/2015
//--------------------------------

#include "GL\glew.h"

class Quad
{
public:
	Quad();
	~Quad();

	void Render();

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};