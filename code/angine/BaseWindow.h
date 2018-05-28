#pragma once

#include <string>
#include "glm\vec2.hpp"

// Window creation information with defaults
struct WindowInfo
{
	int windowWidth = 1600;
	int windowHeight = 900;
	std::string title = "Angin: An Engine";
	bool fullScreen = false;
	bool resizeable = false;
};

class BaseWindow
{
public:
	 BaseWindow() : m_windowSize_Cached(glm::vec2()) { m_baseWindow = this; }
	 virtual ~BaseWindow() {};

	 virtual	void			SwapBuffers			() = 0;
	 virtual	glm::vec2		GetWindowSize		() = 0;
	 virtual	void			WarpMouseInWindow	(int x, int y) = 0;
	 virtual	void			SetWindowGrab		(bool grabbed) = 0;
	 virtual	void			ShowCursor			(bool show) = 0;
	 static	BaseWindow *	Get					() { return m_baseWindow; }

protected:
	static BaseWindow *	m_baseWindow;
	glm::vec2			m_windowSize_Cached;

};