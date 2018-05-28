#ifndef __Week1Colaboration_H_
#define __Week1Colaboration_H_

#include "Application.h"
#include "FBXFile.h"
#include <glm/glm.hpp>

// Derived application class that wraps up all globals neatly
class Week1Colaboration : public AIE_2ND_YEAR::Application
{
public:

	Week1Colaboration();
	virtual ~Week1Colaboration();

protected:
	// Texture tutorial
	// a basic vertex structure supporting position, colour and texture coordinate
	struct BasicVertex
	{
		glm::vec4 position;
		glm::vec4 colour;
		glm::vec2 texCoord;
	};
	
	unsigned int m_textureGrid;
	
	unsigned int m_vao,m_vbo,m_ibo;
	
	unsigned int m_vertShader, m_fragShader, m_shaderTexturing;
	
	// FBX Tutorial
	struct OGL_FBXRenderData
	{
		unsigned int VBO; // vertex buffer object
		unsigned int IBO; // index buffer object
		unsigned int VAO; // vertex array object
	};

	float m_time;

	FBXFile * m_fbx;

	unsigned int m_shader;
	unsigned int m_DeformShader;

	void InitFBXSceneResource(   FBXFile *a_pScene );
	void UpdateFBXSceneResource( FBXFile *a_pScene );
	void RenderFBXSceneResource( FBXFile *a_pScene, glm::mat4 a_view, glm::mat4 a_projection);
	void DestroyFBXSceneResource(FBXFile *a_pScene );

	void createOpenGLBuffers(FBXFile * a_fbx);
	void cleanupOpenGLBuffers(FBXFile* a_fbx);

	void InitSingleMeshFromFile( FBXFile *a_pScene, unsigned int a_meshNum);



	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;
};

#endif // __Week1Colaboration_H_