#include "Window_GLFW.h"
#include "InputHandler.h"

using ANGINE::InputHandler;

Window_GLFW::Window_GLFW(WindowInfo & a_windowInfo)
{
	if(glfwInit() == GL_FALSE)
	{
		printf_s("GLFW was not initialised.");
		return;
	}

	m_window = nullptr;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    a_windowInfo.resizeable ? 
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE) :
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	if(monitor == nullptr)
	{
		printf_s("GLFW could not find a monitor.");
		return;
	}
	const GLFWvidmode * mode = glfwGetVideoMode(monitor);

	m_window = glfwCreateWindow(a_windowInfo.windowWidth, 
								a_windowInfo.windowHeight, 
								a_windowInfo.title.c_str(), 
								a_windowInfo.fullScreen ? 
									monitor :
									nullptr,
								nullptr);

	if(m_window == nullptr)
	{
		printf_s("GLFW window was not created.");
		return;
	}

	glfwMakeContextCurrent(m_window);

	int windowWidth = 0;
	int windowHeight = 0;

	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	m_windowSize_Cached = glm::vec2(windowWidth, windowHeight);

	InputHandler::Create();
}

Window_GLFW::~Window_GLFW()
{
	InputHandler::Destroy();

	glfwDestroyWindow(m_window);

	glfwTerminate();
}

void Window_GLFW::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

glm::vec2 Window_GLFW::GetWindowSize()
{
	return m_windowSize_Cached;
}

void Window_GLFW::WarpMouseInWindow(int x, int y)
{
	glfwSetCursorPos(m_window, (double)x, (double)y);
}

void Window_GLFW::SetWindowGrab(bool grabbed)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window_GLFW::ShowCursor(bool show)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, show ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}