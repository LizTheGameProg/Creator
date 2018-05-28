#ifndef __Tutorial_10_H_
#define __Tutorial_10_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>
#include "RenderSphere.h"

// Derived application class that wraps up all globals neatly
class Tutorial_11 : public AIE_2ND_YEAR::Application
{
public:

	Tutorial_11();
	virtual ~Tutorial_11();
	void InitFBXSceneResource	(	FBXFile *a_pScene );
	void UpdateFBXSceneResource	(	FBXFile *a_pScene );
	void RenderFBXSceneResource	(	unsigned int a_iShader, FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(	FBXFile *a_pScene );

protected:

	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	struct PlaneRenderData
	{
		unsigned int VBO;
		unsigned int IBO;
		unsigned int VAO;
	};

	PlaneRenderData		m_plane;
	PlaneRenderData		m_FullScreenQuad;

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	unsigned int	m_gPassFBO;
	unsigned int	m_lPrePassFBO;

	//Store as RGBA colour valuse for scene geometry
	unsigned int	m_DiffuseTexture;
	//Normal Texture for GPass Shader
	// RG Channels - Store Spehrical coordinates for Normals in view space
	// B  Channel  - Store Depth for ViewSpace
	// A  Channel  - Store speular/roughness in alpha
	unsigned int	m_NormalTexture;
	//Light Pre-Pass Texture
	// RGB - Diffuse Light color and brightness
	// A   - Specular intensity
	unsigned int	m_LightTexture;
	unsigned int	m_LightDepthTexture;
	unsigned int	m_FBODepth;

	unsigned int	m_gPassShader;
	unsigned int	m_cPassShader;
	unsigned int	m_lPassShader;

	FBXFile*		m_fbx;
	CRenderSphere*	m_pPointLight;

	float			m_fTime;
	glm::mat4		m_cameraMatrix;
	glm::mat4		m_projectionMatrix;
	glm::mat4		m_reflectionMatrix;
};

#endif // __Tutorial_10_H_