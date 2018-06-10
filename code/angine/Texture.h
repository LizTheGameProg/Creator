#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>

using std::string;

namespace ANGINE
{
	class Texture
	{
	public:
		Texture(char * filePathName);
		Texture(string * filePathName);
		~Texture();
		unsigned int getID() { return textureID; }

	private:
		Texture();
		unsigned int textureID;

	public:
		int width;
		int height;

	private:
		int format;
	};
}