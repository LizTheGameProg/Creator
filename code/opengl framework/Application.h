#pragma once

//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	17/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	18/08/2015
//--------------------------------

// GLEW
#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

namespace openGL
{
	class Window;
	class Camera2D;
}
class Sprite;

enum class ERROR : GLint
{
	NONE = 0,
	GLFW_INIT_FAILED,
	GLFW_NO_MONITOR,
	GLFW_WINDOW_CREATION_FAILED,
	GLEW_INIT_FAILED
};

namespace openGL
{
	class Application
	{
		friend class Window;
	public:
		Application();
		virtual ~Application();

		// If windowWidth or windowHeight is 0 the window 
		// will default to screen width and height
		int		StartUp(GLuint windowWidth = 0, GLuint windowHeight = 0, GLboolean fullScreen = GL_FALSE, const GLchar * title = "Framework");
		void	Run();
		void	ShutDown();

		ERROR	GetLastError() { return m_lastError; }

	protected:
		virtual void Create();
		virtual void Destroy();

		virtual void Update(GLfloat deltaTime);
		virtual void Render();

	private:
		static void ErrorCallBack(GLint error, const GLchar * description);

		ERROR		m_lastError;
		Window *	m_window;
		Camera2D *	m_camera;
		GLdouble	m_lastFrameTime;
		GLdouble	m_deltaTime;

		// Testing
		Sprite *	m_testSprite;
	};
}