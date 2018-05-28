#ifndef __Animation_H_
#define __Animation_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Animation : public AIE_2ND_YEAR::Application
{
public:

	Animation();
	virtual ~Animation();

protected:
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	FBXFile * m_fbx;
	unsigned int m_shader;

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	void InitFBXSceneResource(FBXFile * a_pScene);
	void DestroyFBXSceneResource(FBXFile * a_pScene);
	void UpdateFBXSceneResource(FBXFile * a_pScene);
	void RenderFBXSceneResource(FBXFile * a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
};

#endif // __Animation_H_