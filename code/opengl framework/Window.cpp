//================================
// Created By:		Elizabeth Rowlands
// Creation Date:	17/08/2015
// Updated By:		Elizabeth Rowlands
// Updated Date:	17/08/2015
//--------------------------------
#include "Window.h"
#include "Application.h"
#include "InputHandler.h"

namespace openGL
{
	Window * Window::m_window = nullptr;
	Window::Window(Application * a_application, WindowInfo a_windowInfo)
	{
		m_application = a_application;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWmonitor * monitor = glfwGetPrimaryMonitor();
		if(monitor == nullptr)
		{
			m_application->m_lastError = ERROR::GLFW_NO_MONITOR;
			return;
		}
		const GLFWvidmode * mode = glfwGetVideoMode(monitor);

		m_glfwWindow = glfwCreateWindow(a_windowInfo.windowWidth == 0 ? mode->width : a_windowInfo.windowWidth,
			a_windowInfo.windowHeight == 0 ? mode->height : a_windowInfo.windowHeight,
			a_windowInfo.windowTitle.c_str(),
			a_windowInfo.fullScreen == false ? nullptr : monitor,
			nullptr);

		if(m_glfwWindow == nullptr)
		{
			m_application->m_lastError = ERROR::GLFW_WINDOW_CREATION_FAILED;
			return;
		}

		glfwMakeContextCurrent(m_glfwWindow);

		InputHandler::Create();
		m_inputHandler = InputHandler::Get();

		glfwSetKeyCallback(m_glfwWindow, &InputHandler::keyCallback);
		glfwSetCursorPosCallback(m_glfwWindow, &InputHandler::mouseCursorCallback);
		glfwSetMouseButtonCallback(m_glfwWindow, &InputHandler::mouseButtonCallback);

		m_window = this;
	}

	Window::~Window()
	{
		InputHandler::Destroy();
	}
}