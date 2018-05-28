#pragma once

#include "BaseWindow.h"
#ifdef USING_SDL2
#include "SDL.h"

class Window_SDL2 : public BaseWindow
{
public:
	Window_SDL2() = delete;
	Window_SDL2(WindowInfo windowInfo);
	virtual ~Window_SDL2();

	virtual void		SwapBuffers();
	virtual glm::vec2 GetWindowSize();
	virtual void		WarpMouseInWindow(int x, int y);
	virtual void		SetWindowGrab(bool grabbed);
	virtual void		ShowCursor(bool show);

private:
	SDL_Window * m_window;
	SDL_GLContext m_glContext;
};
#endif