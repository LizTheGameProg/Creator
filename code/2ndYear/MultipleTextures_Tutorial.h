#ifndef _MultipleTextures_Tutorial_H_
#define _MultipleTextures_Tutorial_H_

#include "Application.h"
#include "FBXFile.h"
#include "SOIL.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class MultipleTextures_Tutorial : public AIE_2ND_YEAR::Application
{
public:

	MultipleTextures_Tutorial();
	virtual ~MultipleTextures_Tutorial();

protected:
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	float m_time;

	FBXFile * m_fbx;

	unsigned int m_shader;
	unsigned int m_decayTexture;
	float m_decayValue;

	void InitFBXSceneResource(   FBXFile *a_pScene );
	void UpdateFBXSceneResource( FBXFile *a_pScene );
	void RenderFBXSceneResource( FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene );

	void InitSingleMeshFromFile( FBXFile *a_pScene, unsigned int a_meshNum);

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif