#include "FBXManager.h"
#include "FBXFile.h"

FBXManager * FBXManager::m_fbxManager = nullptr;

FBXManager::FBXManager(void)
{

}

FBXManager::~FBXManager(void)
{
	for(FBXSceneResource * f_FBXResources : m_FBXResources)
	{
		delete f_FBXResources;
		f_FBXResources = nullptr;
	}
	m_FBXResources.clear();
}

void FBXManager::Create()
{
	if(m_fbxManager == nullptr)
		m_fbxManager = new FBXManager();
}

void FBXManager::Destroy()
{
	delete m_fbxManager;
	m_fbxManager = nullptr;
}

FBXManager & FBXManager::Get()
{
	if(m_fbxManager == nullptr)
		Create();
	return *m_fbxManager;
}

void FBXManager::Update()
{
	for (FBXSceneResource * f_FBXSceneResource : m_FBXResources)
	{
		f_FBXSceneResource->Update();
	}
}

void FBXManager::Render(glm::mat4 a_viewMatrix, glm::mat4 a_ProjectionMatrix, float a_time)
{
	for (FBXSceneResource * f_FBXSceneResource : m_FBXResources)
	{
		f_FBXSceneResource->Render(a_viewMatrix, a_ProjectionMatrix, a_time);
	}
}

void FBXManager::AddNewFBXSceneResource(const char * a_filePath, FBXFile::UNIT_SCALE a_unitScale, ShaderProgram * a_shaderProgram)
{
	m_FBXResources.push_back(new FBXSceneResource(a_filePath, a_unitScale, a_shaderProgram));
}

void FBXManager::AddNewFBXSceneResource(FBXSceneResource * a_FBXSceneResource)
{
	m_FBXResources.push_back(a_FBXSceneResource);
}