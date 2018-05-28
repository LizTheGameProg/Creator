#include "Quad.h"
#include "openGLBindings.h"
#include "glm\vec3.hpp"
#include "glm\ext.hpp"

Quad::Quad()
{
	programID = 0;
	textureID = 0;

	init();
}

Quad::Quad(unsigned int a_programID, unsigned int a_textureID)
{
	programID = a_programID;
	textureID = a_textureID;

	init();
}

Quad::~Quad()
{
	//glDeleteBuffers(1, &ibo);
	//glDeleteBuffers(1, &vbo);
	//glDeleteVertexArrays(1, &vao);
}

void Quad::update(float a_deltaTime)
{
	
}

void Quad::render(glm::mat4 a_projectionView)
{
	if(vertexDataHasChanged)
	{
		vertexDataHasChanged = false;

		//glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, vertexData, GL_STATIC_DRAW);
	}

	//glUseProgram(programID);
	//
	//int location = glGetUniformLocation(programID, "ProjectionView");
	//glUniformMatrix4fv(location, 1, GL_FALSE, &a_projectionView[0][0]);
	//
	//location = glGetUniformLocation(programID, "model");
	//glUniformMatrix4fv(location, 1, GL_FALSE, &transform[0][0]);
	//
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//
	//location = glGetUniformLocation(programID, "diffuse");
	//glUniform1i(location, GL_TEXTURE0);
	//
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Quad::SetProgram(unsigned int a_programID)
{
	programID = a_programID;
}

void Quad::SetTexture(unsigned int a_textureID)
{
	textureID = a_textureID;
}

void Quad::SetDimensions(float a_width, float a_height)
{
	//transform = glm::scale(glm::vec3(a_width, a_height, 1));
	
	float widthOn2 = a_width / 2;
	float heightOn2 = a_height / 2;

	vertexData[0] = -widthOn2;
	vertexData[1] = heightOn2;

	vertexData[6] = widthOn2;
	vertexData[7] = heightOn2;

	vertexData[12] = widthOn2;
	vertexData[13] = -heightOn2;

	vertexData[18] = -widthOn2;
	vertexData[19] = -heightOn2;

	vertexDataHasChanged = true;
}

void Quad::SetDimensions(glm::vec2 a_dimensions)
{
	SetDimensions(a_dimensions.x, a_dimensions.y);
}

void Quad::init()
{	
	vertexDataHasChanged = false;

	float localData[24] = 
	{
		-1, 1, 0, 1, 0, 0,
		 1, 1, 0, 1, 1, 0,
		 1,-1, 0, 1, 1, 1,
		-1,-1, 0, 1, 0, 1
	};

	for(unsigned int i = 0; i < 24; i++)
	{
		vertexData[i] = localData[i];
	}

	unsigned int indexData[] = 
	{
		0, 1, 2,
		0, 2, 3
	};

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	//
	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, vertexData, GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &ibo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexData, GL_STATIC_DRAW);
	//
	//// Position + Texture
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//
	//// Index
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, ((char *) 0) + 16);
	//
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}