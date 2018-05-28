#pragma once

#include <map>

using std::map;

// GLEW
#define GLEW_STATIC
#include "GL/glew.h"

// GLFW
#include "GLFW/glfw3.h"

#include "glm\vec2.hpp"
namespace openGL
{
	class InputHandler
	{
	public:
		friend class Window;
	private:
		InputHandler();
		virtual ~InputHandler();

	public:
		static void Create();
		static void Destroy();
		static InputHandler * Get();

		GLboolean IsKeyDown(GLint glfwKeyCode);
		GLboolean IsMouseButtonDown(GLint glfwMouseButtonCode);
		glm::vec2 GetMousePosition();

	private:
		static void keyCallback(GLFWwindow * window, GLint key, GLint scancode, GLint action, GLint mode);
		static void mouseCursorCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos);
		static void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);

		static InputHandler * m_instance;

		// Map of keys and states
		map<GLint, GLint> m_keyStates;

		// Map of mouse buttons and states
		map<GLint, GLint> m_mouseStates;

		// Position of the mouse in the window
		glm::vec2 m_mousePosition;
	};
}