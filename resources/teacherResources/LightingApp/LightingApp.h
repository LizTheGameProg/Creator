#pragma once

#include "Application.h"

struct GLFWwindow;
class Camera;
class FBXFile;

class LightingApp : public Application {
public:

	LightingApp() : m_window(nullptr), m_camera(nullptr) {}
	virtual ~LightingApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();

private:

	void createOpenGLBuffers(FBXFile* fbx);
	void cleanupOpenGLBuffers(FBXFile* fbx);

	GLFWwindow*		m_window;
	Camera*			m_camera;
	FBXFile*		m_fbx;
	unsigned int	m_program;
};