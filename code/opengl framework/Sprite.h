#pragma once
//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	18/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	19/08/2015
//--------------------------------

class Quad;
class Shader;
class Texture;

#include "Transform2D.h"

// GLEW
#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Update(GLfloat deltaTime);
	void Render(glm::mat4 projectionView);

	Quad *		quad;
	Shader *	defaultShader;
	Transform2D transform;
	Texture *	texture;
};