#pragma once

#include <string>
#include "glm\vec2.hpp"

// GLEW
#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

namespace openGL
{
	class Texture
	{
	public:
		Texture() = delete; // = delete makes it so that this cannot be called under any circumstances
		Texture(std::string filePath); // Use this instead of the default constructor
		~Texture();

		glm::vec2	GetDimensions();
		GLuint		GetTextureID();

	private:
		glm::vec2	m_dimensions;
		GLuint		m_textureID;
	};
}