#include "Texture.h"
#include "openGLBindings.h"

Texture::Texture()
{

}

Texture::Texture(char * a_filePathName)
{
	width = 0;
	height = 0;

	//stbi__context context;
	//int x;
	//int y;
	//int comp;
	//
	//unsigned char * data = stbi__tga_load(&context, &x, &y, &comp, STBI_default);
	unsigned char * data = stbi_load(a_filePathName, &width, &height, &format, STBI_default);

	//glGenTextures(1, &textureID);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

Texture::Texture(string * a_filePathName)
{
	unsigned char * data = stbi_load(a_filePathName->c_str(), &width, &height, &format, STBI_default);

	//glGenTextures(1, &textureID);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

Texture::~Texture()
{

}