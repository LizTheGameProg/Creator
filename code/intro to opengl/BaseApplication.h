#pragma once

#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include <glm\mat4x4.hpp>

namespace INTRO_OPENGL
{
	class FlyCamera3D;
}

class BaseApplication
{
public:
	BaseApplication();
	virtual ~BaseApplication();

	virtual bool startUp();
	virtual void shutDown();
	virtual bool update();
	virtual void render();

protected:
	glm::mat4 view;
	glm::mat4 projection;
	GLFWwindow * window;
	float deltaTime;
	INTRO_OPENGL::FlyCamera3D * camera;

private:
	double lastFrameTime;
	double thisFrameTime;
};