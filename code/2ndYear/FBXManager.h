#ifndef FBXMANAGER_H
#define FBXMANAGER_H

#include "FBXSceneResource.h"

class FBXManager
{
public:
	// Singleton related functions
	static void Create();
	static void Destroy();
	static FBXManager & Get();

	void Update();
	void Render(glm::mat4 viewMatrix, glm::mat4 ProjectionMatrix, float a_time);
	void AddNewFBXSceneResource(const char * filePath, FBXFile::UNIT_SCALE unitScale, ShaderProgram * a_shaderProgram);
	void AddNewFBXSceneResource(FBXSceneResource * a_FBXSceneResource);
private:
	// Restricting access to these because it is a singleton class
	FBXManager(void);
	~FBXManager(void);
	FBXManager(FBXManager const&);
	FBXManager& operator=(FBXManager const&);
	static FBXManager * m_fbxManager;

	std::vector<FBXSceneResource *> m_FBXResources;

};

#endif