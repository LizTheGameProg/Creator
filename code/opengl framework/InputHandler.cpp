#include "InputHandler.h"
#include <iostream>
namespace openGL
{
	InputHandler * InputHandler::m_instance = nullptr;

	InputHandler::InputHandler()
	{
		m_keyStates = map<GLint, GLint>();
		m_mouseStates = map<GLint, GLint>();
		m_mousePosition = glm::vec2();
	}

	InputHandler::~InputHandler()
	{

	}

	void InputHandler::Create()
	{
		m_instance = new InputHandler();
	}

	void InputHandler::Destroy()
	{
		delete m_instance;
	}

	InputHandler * InputHandler::Get()
	{
		return m_instance;
	}

	GLboolean InputHandler::IsKeyDown(GLint a_glfwKeyCode)
	{
		if(m_keyStates[a_glfwKeyCode] == GLFW_PRESS || m_keyStates[a_glfwKeyCode] == GLFW_REPEAT)
			return true;

		return false;
	}

	GLboolean InputHandler::IsMouseButtonDown(GLint a_glfwMouseButtonCode)
	{
		if(m_mouseStates[a_glfwMouseButtonCode] == GLFW_PRESS || m_mouseStates[a_glfwMouseButtonCode] == GLFW_REPEAT)
			return true;

		return false;
	}

	glm::vec2 InputHandler::GetMousePosition()
	{
		return m_mousePosition;
	}

	void InputHandler::keyCallback(GLFWwindow * a_window, GLint a_key, GLint a_scancode, GLint a_action, GLint a_mode)
	{
		m_instance->m_keyStates[a_key] = a_action;
	}

	void InputHandler::mouseCursorCallback(GLFWwindow* a_window, GLdouble a_xpos, GLdouble a_ypos)
	{
		m_instance->m_mousePosition = glm::vec2(a_xpos, a_ypos);
	}

	void InputHandler::mouseButtonCallback(GLFWwindow* a_window, GLint a_button, GLint a_action, GLint a_mods)
	{
		m_instance->m_mouseStates[a_button] = a_action;
	}
}