#ifdef USING_SDL2
#include "Window_SDL2.h"
//#include "SDL_opengl.h"

Window_SDL2::Window_SDL2(WindowInfo a_windowInfo)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf_s("SDL was not initialised. SDL Error: %s\n", SDL_GetError());
		return;
	}

	m_window = nullptr;
	m_window = SDL_CreateWindow(a_windowInfo.title.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								a_windowInfo.windowWidth,
								a_windowInfo.windowHeight,
								a_windowInfo.fullScreen ? 
									SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP : 
									SDL_WINDOW_OPENGL);

	if(m_window == nullptr)
	{
		printf_s("SDL Window was not created. SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	int windowWidth = 0;
	int windowHeight = 0;

	SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

	m_windowSize_Cached = glm::vec2(windowWidth, windowHeight);

	m_glContext = SDL_GL_CreateContext(m_window);
}

Window_SDL2::~Window_SDL2()
{
	SDL_GL_DeleteContext(m_glContext);

	if(m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	SDL_Quit();
}

void Window_SDL2::SwapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

glm::vec2 Window_SDL2::GetWindowSize()
{
	return m_windowSize_Cached;
}

void Window_SDL2::WarpMouseInWindow(int a_x, int a_y)
{
	SDL_WarpMouseInWindow(m_window, a_x, a_y);
}

void Window_SDL2::SetWindowGrab(bool a_grabbed)
{
	SDL_SetWindowGrab(m_window, (SDL_bool)a_grabbed);
}

void Window_SDL2::ShowCursor(bool a_show)
{
	SDL_ShowCursor(a_show);
}
#endif