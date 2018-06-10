#include "textureManager.h"
TextureManager* TextureManager::m_instance = nullptr;

#ifdef _DEBUG
#include <iostream>
#endif

TextureManager::TextureManager()
{
	m_textureMap = std::map<std::string, openGL::Texture*>();
}

TextureManager::~TextureManager()
{
	for (auto iter = m_textureMap.begin(); iter != m_textureMap.end(); ++iter)
	{
		delete (*iter).second;
	}
}

void TextureManager::Create()
{
	if(m_instance == nullptr)
	{
		m_instance = new TextureManager();
	}
}

void TextureManager::Destroy()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

TextureManager* TextureManager::Get()
{
	return m_instance;
}

void TextureManager::LoadTexture(std::string a_fileName)
{
#ifdef _DEBUG
	if(m_textureMap[a_fileName])
		std::cout << "A texture has already been loaded from";
#endif
	m_textureMap[a_fileName] = new openGL::Texture(a_fileName.c_str());
}

openGL::Texture* TextureManager::GetTexture(std::string a_fileName)
{
	return m_textureMap[a_fileName];
}