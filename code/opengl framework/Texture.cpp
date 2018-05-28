#include "Texture.h"
#include "SOIL.h"

Texture::Texture(std::string a_filePath)
{
	int width = 0;
	int height = 0;
	unsigned char * imageData = SOIL_load_image(a_filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	
	m_dimensions.x = (float) width;
	m_dimensions.y = (float) height;

	glGenTextures(1, &m_textureID);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(imageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{

}

glm::vec2 Texture::GetDimensions()
{
	return m_dimensions;
}

GLuint Texture::GetTextureID()
{
	return m_textureID;
}