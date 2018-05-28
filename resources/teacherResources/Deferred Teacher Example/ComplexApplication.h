#pragma once

#include "BaseApplication.h"

// only needed for the camera picking
#define GLM_SWIZZLE
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <FBXFile.h>

class Camera;

class ComplexApplication : public BaseApplication {
public:

	ComplexApplication();
	virtual ~ComplexApplication();

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();
	
private:

	Camera*		m_camera;

	unsigned int	m_quadVAO, m_quadVBO;

	void createOpenGLBuffers(FBXFile* fbx);
	void cleanupOpenGLBuffers(FBXFile* fbx);

	FBXFile* m_fbx;

	unsigned int	m_gpassFBO;
	unsigned int	m_albedoTexture, m_normalTexture, m_positionTexture, m_gpassDepth;

	unsigned int	m_lightFBO;
	unsigned int	m_lightTexture;

	unsigned int	m_gpassShader;
	unsigned int	m_directionLightShader;
	unsigned int	m_pointLightShader;
	unsigned int	m_compositeShader;

	// draws a quad
	void drawDirectionalLight(const glm::vec3& direction, const glm::vec3& diffuse);

	// draws a ball
	void drawPointLight(const glm::vec3& poisition, float radius, const glm::vec3& diffuse);

};