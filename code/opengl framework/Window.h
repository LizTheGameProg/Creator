#pragma once

//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	17/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	08/09/2015
//--------------------------------

#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

#include <string>
namespace openGL
{
	class Application;
	class InputHandler;

	struct WindowInfo
	{
		GLuint		windowWidth;
		GLuint		windowHeight;
		std::string	windowTitle;
		GLboolean	fullScreen;
	};

	class Window
	{
	public:
		Window() = delete; // = delete makes it so that this cannot be called under any circumstances
		Window(Application * application, WindowInfo windowInfo); // Use this instead of the default constructor
		~Window();

		inline static Window * Get() { return m_window; }

		inline GLFWwindow * GetWindow() { return m_glfwWindow; }

	private:
		static Window * m_window;

		GLFWwindow * m_glfwWindow;
		Application * m_application;
		InputHandler * m_inputHandler;
	};
}