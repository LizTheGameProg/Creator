#pragma once

#include "BaseWindow.h"
#include "GLFW\glfw3.h"

class Window_GLFW : public BaseWindow
{
public:
	Window_GLFW() = delete;
	Window_GLFW(WindowInfo & windowInfo);
	virtual ~Window_GLFW();

	virtual void			SwapBuffers();
	virtual glm::vec2		GetWindowSize();
	virtual void			WarpMouseInWindow(int x, int y);
	virtual void			SetWindowGrab(bool grabbed);
	virtual void			ShowCursor(bool show);
	virtual GLFWwindow *	GetGLFWWindow() { return m_window; }
private:
	GLFWwindow * m_window;
};