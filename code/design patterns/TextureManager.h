#pragma once
#include "Texture.h"
#include <map>
#include <string>

class TextureManager
{
protected:
	TextureManager();
	~TextureManager();

public:
	static void Create();
	static void Destroy();
	static TextureManager * Get();

	// This uses the path and file name ("./Images/background.png")
	void LoadTexture(std::string fileName);

	// This uses the path and file name ("./Images/background.png")
	Texture* GetTexture(std::string fileName);

protected:
	static TextureManager * m_instance;

	std::map<std::string, Texture*> m_textureMap;
};