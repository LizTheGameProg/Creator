#pragma once

#include "Application.h"

struct GLFWwindow;
class Camera;

class TextureApp : public Application {
public:

	TextureApp() : m_window(nullptr), m_camera(nullptr) {}
	virtual ~TextureApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();

private:

	struct Vertex {
		float x, y, z, w;
		float nx, ny, nz, nw;
		float tx, ty, tz, tw;
		float s, t;
	};

	GLFWwindow*	m_window;
	Camera*		m_camera;

	unsigned int	m_program;
	unsigned int	m_vao, m_vbo, m_ibo;
	unsigned int	m_texture, m_normalmap;
};