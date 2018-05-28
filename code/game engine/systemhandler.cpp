#include "systemhandler.h"

#include "processhandler.h"
ProcessHandler processHandler;

#include "SDL_video.h"
SDL_Window * window = nullptr;
SDL_GLContext glContext;

#if defined(_WINDOWS)
#include "SDL_opengl.h"
#elif defined(ANDROID) || defined(APPLE)
#include "SDL_opengles.h"
#endif

namespace GAME_ENGINE
{
	SystemHandler::SystemHandler()
	{

	}

	SystemHandler::~SystemHandler()
	{

	}

	bool SystemHandler::OnInitialize()
	{
		bool ret = false;
		ret = processHandler.Initialize();

		if(ret)
		{
			window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
			if(window)
			{
				glContext = SDL_GL_CreateContext(window);
			}
			else
			{
				ret = false;
			}
		}


		return ret;
	}

	void SystemHandler::OnDeInitialize()
	{
		if(window)
		{
			SDL_GL_DeleteContext(glContext);
			SDL_DestroyWindow(window);
		}
		processHandler.DeInitialize();
	}

	bool SystemHandler::ShouldExit()
	{
		return processHandler.ShouldExit();
	}

	//double SystemHandler::GetCurrentTime()
	//{
	//	return processHandler.GetCurrentTime();
	//}

	void SystemHandler::ProcessEvents()
	{
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		processHandler.ProcessEvents();
	}

	void SystemHandler::Flip()
	{
		SDL_GL_SwapWindow(window);
	}
}