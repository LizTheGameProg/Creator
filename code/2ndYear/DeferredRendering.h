#ifndef __DeferredRendering_H_
#define __DeferredRendering_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class DeferredRendering : public AIE_2ND_YEAR::Application
{
public:

	DeferredRendering();
	virtual ~DeferredRendering();

protected:
	struct BasicVertex
	{
		glm::vec4 position;
		glm::vec4 colour;
		glm::vec2 texCoord;
	};
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	OGL_FBXRenderData m_ro;
	OGL_FBXRenderData m_quad;
	OGL_FBXRenderData m_lightQuad;

	FBXFile * m_fbx;

	glm::mat4 m_lightDir;
	glm::vec2 m_screenSize;
	glm::mat4 m_shadowProjectionViewMatrix;

	unsigned int m_FBO;
	unsigned int m_FBO_diffuse;
	unsigned int m_FBO_normal;
	unsigned int m_FBO_worldposition;
	unsigned int m_FBO_depth;

	unsigned int m_FBO_lightPass;
	unsigned int m_FBO_lightTexture;

	unsigned int m_geomPassShader;
	unsigned int m_quadShader;
	unsigned int m_LPPShader;

	unsigned int m_shadowWidth;
	unsigned int m_shadowHeight;

	unsigned int m_shadowFramebuffer;
	unsigned int m_shadowTexture;

	unsigned int m_simpleShader;
	unsigned int m_shaderProgram;
	unsigned int m_RenderShadowMap;
	unsigned int m_DisplayShadowMap;

	void InitFBXSceneResource	(FBXFile *a_pScene );
	void UpdateFBXSceneResource	(FBXFile *a_pScene );
	void RenderFBXSceneResource	(FBXFile *a_pScene, 
									glm::mat4 a_view, 
									glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene );
	
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	void freeMovement(	glm::mat4& a_transform, 
						float a_deltaTime, 
						float a_speed, 
						const glm::vec3& a_up = glm::vec3(0,1,0));

	void createGPassBuffer();
	void createLightingBuffer();
	void createShadowBuffer();

	void createShaderPrograms();
	void createQuads();

	void RenderGPass();
	void RenderLighting();
	void RenderShadows();
	void RenderToQuad();

	void setUpLightAndShadowMatrix(float count);

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __DeferredRendering_H_