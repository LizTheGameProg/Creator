#ifndef __RenderTargets_H_
#define __RenderTargets_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class RenderTargets : public AIE_2ND_YEAR::Application
{
public:

	RenderTargets();
	virtual ~RenderTargets();

protected:
	// this would be within your derived application class as a member variable
	unsigned int m_FBO;
	unsigned int m_FBO_texture;
	unsigned int m_FBO_depth;

	unsigned int m_vao, m_vbo, m_ibo;

	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	FBXFile * m_fbx;
	unsigned int m_shader;
	unsigned int m_shader_renderTargets;
	

	void InitFBXSceneResource(   FBXFile *a_pScene );
	void UpdateFBXSceneResource( FBXFile *a_pScene );
	void RenderFBXSceneResource( FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene );

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __RenderTargets_H_