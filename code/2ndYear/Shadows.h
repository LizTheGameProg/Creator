#ifndef __Shadows_H_
#define __Shadows_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Shadows : public AIE_2ND_YEAR::Application
{
public:

	Shadows();
	virtual ~Shadows();

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

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	unsigned int m_shadowWidth;
	unsigned int m_shadowHeight;

	unsigned int m_shadowFramebuffer;
	unsigned int m_shadowTexture;

	glm::vec4 m_lightDirection;
	glm::mat4 m_shadowProjectionViewMatrix;

	unsigned int m_simpleShader;
	unsigned int m_shaderProgram;
	unsigned int m_RenderShadowMap;
	unsigned int m_DisplayShadowMap;

	FBXFile * m_fbx;
	OGL_FBXRenderData m_2dQuad;

	glm::vec3 m_lightPosition;

	void createShadowBuffer();
	void setUpLightAndShadowMatrix(float count);

	void create2DQuad();
	void displayShadowMap();
	void drawScene();
	void freeMovement(	glm::vec3& a_transform, 
						float a_deltaTime, 
						float a_speed, 
						const glm::vec3& a_up = glm::vec3(0,1,0));


	void InitFBXSceneResource	(FBXFile *a_pScene);
	void DestroyFBXSceneResource(FBXFile *a_pScene);
	void UpdateFBXSceneResource	(FBXFile *a_pScene);
	void RenderFBXSceneResource	(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void RenderFBXSceneResourceFromLight(FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
};

#endif // __Shadows_H_