#ifndef __Compilation_H_
#define __Compilation_H_

#include "Application.h"
#include <glm/glm.hpp>
#include <map>
#include <FBXFile.h>

class ParticleSystem;

struct OGL_FBXRenderData
{
	unsigned int VBO; // vertex buffer object
	unsigned int IBO; // index buffer object
	unsigned int VAO; // vertex array object
};

// Derived application class that wraps up all globals neatly
class Compilation : public AIE_2ND_YEAR::Application
{
public:

	Compilation(){};
	virtual ~Compilation(){};

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	// map to store unsigned int's for all the 
	// shader programs that are created
	std::map<const char *, unsigned int> m_shaderMap;
	// function to encapsulate the creation of shaders
	void createShaderPrograms();

	void InitFBXSceneResource	(FBXFile *a_pScene );
	void UpdateFBXSceneResource	(FBXFile *a_pScene );
	void RenderFBXSceneResource	(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene );

	FBXFile * m_fbx;

	ParticleSystem * m_emitter;
};

#endif // __Compilation_H_