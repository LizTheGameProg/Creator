//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	18/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	20/08/2015
//--------------------------------

#include "Sprite.h"
#include "Quad.h"
#include "Shader.h"
#include "Texture.h"
#include "InputHandler.h"

#include "glm\ext.hpp"

Sprite::Sprite()
{
	quad = new Quad();
	defaultShader = new Shader();
	defaultShader->Load("./shaders/default.vert", "./shaders/default.frag");

	transform.SetTranslation(glm::vec2(0.f, 0.f));

	texture = new Texture("./textures/awesomeface.png");
}

Sprite::~Sprite()
{
	delete quad;
	delete defaultShader;
	delete texture;
}

void Sprite::Update(GLfloat a_deltaTime)
{

}

void Sprite::Render(glm::mat4 a_projectionView)
{
	defaultShader->Use();

	int location = glGetUniformLocation(defaultShader->programID, "uniform_texture");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
	glUniform1i(location, 0);

	location = glGetUniformLocation(defaultShader->programID, "uniform_transform");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr( a_projectionView * transform.GetTransform()));

	quad->Render();

	glUseProgram(0);
}