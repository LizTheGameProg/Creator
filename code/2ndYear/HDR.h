#ifndef __HDR_H_
#define __HDR_H_

#include "Application.h"
#include <glm/glm.hpp>

#include <FBXFile.h>

// Derived application class that wraps up all globals neatly
class HDR : public AIE_2ND_YEAR::Application
{
public:

	HDR();
	virtual ~HDR();

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	void	createOpenGLBuffers(FBXFile* a_fbx);
	void	cleanupOpenGLBuffers(FBXFile* a_fbx);

	void	createFullScreenQuad();
	void	createFrameBuffer(unsigned int a_width, unsigned int a_height,
							  unsigned int* a_fbo, unsigned int* a_fboTexture, 
							  unsigned int* a_fboDepth);

	void	renderFullScreenQuad();
	void	renderToBackBuffer();
	void	renderToFrameBuffer(unsigned int a_fbo, unsigned int a_width, unsigned int a_height);

	struct GLData
	{
		unsigned int	vao, vbo, ibo;
	};

	FBXFile*	m_spear;
	GLData		m_quad;	

	// shaders
	unsigned int	m_shader;	// the shader used to render to mesh

	unsigned int m_brightPassShader;
	unsigned int m_gaussianShader;
	unsigned int m_bloomShader;

	glm::mat4	m_cameraMatrix;
	glm::mat4	m_projectionMatrix;

	// size of downsampled targets
	glm::ivec2 m_downsampledSize;

	// the framebuffer that we render into in the first pass
	unsigned int m_fbo, m_fboTexture, m_fboDepth;

	// the downsampled framebuffers
	// we have two so that we can ping-pong a bilateral gaussian blur
	unsigned int m_downsampledFBO[2], m_downsampledTexture[2];

	float m_brightnessThreshold;
};

#endif // __HDR_H_