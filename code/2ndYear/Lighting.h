#ifndef __Lighting_H_
#define __Lighting_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Lighting : public AIE_2ND_YEAR::Application
{
public:

	Lighting();
	virtual ~Lighting();

protected:
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};


	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	unsigned int m_shader;

	FBXFile * m_fbx;

	void InitFBXSceneResource	(FBXFile *a_pScene );
	void UpdateFBXSceneResource	(FBXFile *a_pScene );
	void RenderFBXSceneResource	(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene );
};

#endif // __Lighting_H_