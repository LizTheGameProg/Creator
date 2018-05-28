//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	18/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	20/08/2015
//--------------------------------

#include "Quad.h"

Quad::Quad()
{
	GLfloat vertices[] = 
	{	// Position Data		// Texture Coords
		 50.f,  50.f, 0.f, 1.f, 1.f, 0.f,			// Top Right
		 50.f, -50.f, 0.f, 1.f, 1.f, 1.f,			// Bottom Right
		-50.f, -50.f, 0.f, 1.f, 0.f, 1.f,			// Bottom Left
		-50.f,  50.f, 0.f, 1.f, 0.f, 0.f			// Top Left 
	};
	GLuint indices[] = 
	{				// Note that we start from 0!
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};  

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Quad::Render()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Quad::~Quad()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}