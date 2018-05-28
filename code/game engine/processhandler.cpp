#include "processhandler.h"
#include "SDL.h"
#include "iostream"
#include "inputhandler.h"
GAME_ENGINE::InputHandler inputHandler;

ProcessHandler::ProcessHandler()
	: shouldExit(false)
{
	
}

ProcessHandler::~ProcessHandler()
{
	
}

bool ProcessHandler::OnInitialize()
{
	bool ret = false;
	
	bool sdlInit = SDL_Init(0) == 0;
	bool inputInit = inputHandler.Initialize();
	return sdlInit && inputInit;
}

void ProcessHandler::OnDeInitialize()
{
	inputHandler.DeInitialize();
	SDL_Quit();
}

bool ProcessHandler::ShouldExit()
{
	return shouldExit;
}

void ProcessHandler::ProcessEvents()
{
	SDL_Event e;
	int ret = 1;
	while(ret == 1)
	{
		ret = SDL_PollEvent(&e);
		switch(e.type)
		{
			case SDL_FIRSTEVENT:
			/**< Unused (do not remove) */
			{
				break;
			}
			
/* Application events */
			case SDL_QUIT:
			/**< User-requested quit */
			{
				shouldExit = true;
				break;
			}

/* These application events have special meaning on iOS, see README-ios.md for details */
			case SDL_APP_TERMINATING:
			/**< The application is being terminated by the OS
				Called on iOS in applicationWillTerminate()
				Called on Android in onDestroy() */
			{
				shouldExit = true;
				break;
			}
				
			case SDL_APP_LOWMEMORY:
			/**< The application is low on memory, free memory if possible.
				Called on iOS in applicationDidReceiveMemoryWarning()
				Called on Android in onLowMemory() */
			{
				break;
			}
			
			case SDL_APP_WILLENTERBACKGROUND:
			/**< The application is about to enter the background
				Called on iOS in applicationWillResignActive()
				Called on Android in onPause() */
			{
				break;
			}
			
			case SDL_APP_DIDENTERBACKGROUND:
			/**< The application did enter the background and may not get CPU for some time
				Called on iOS in applicationDidEnterBackground()
				Called on Android in onPause() */
			{
				break;
			}
			
			case SDL_APP_WILLENTERFOREGROUND:
			/**< The application is about to enter the foreground
				Called on iOS in applicationWillEnterForeground()
				Called on Android in onResume() */
			{
				break;
			}
			
			case SDL_APP_DIDENTERFOREGROUND:
			/**< The application is now interactive
				Called on iOS in applicationDidBecomeActive()
				Called on Android in onResume() */
			{
				break;
			}
			
/* Window events */
			case SDL_WINDOWEVENT:
			/**< Window state change */
			{
				break;
			}
			
			case SDL_SYSWMEVENT:
			/**< System specific event */
			{
				break;
			}
			
/* Keyboard events */
			case SDL_KEYDOWN:
			/**< Key pressed */
			{
				break;
			}
			
			case SDL_KEYUP:
			/**< Key released */
			{
				break;
			}
			
			case SDL_TEXTEDITING:
			/**< Keyboard text editing (composition) */
			{
				break;
			}
			
			case SDL_TEXTINPUT:
			/**< Keyboard text input */
			{
				break;
			}
			
			//case SDL_KEYMAPCHANGED:
			///**< Keymap changed due to a system event such as an
			//	input language or keyboard layout change. */
			//{
			//	break;
			//}
			
/* Mouse events */
			case SDL_MOUSEMOTION:
			/**< Mouse moved */
			{
				break;
			}
			
			case SDL_MOUSEBUTTONDOWN:
			/**< Mouse button pressed */
			{
				break;
			}
			
			case SDL_MOUSEBUTTONUP:
			/**< Mouse button released */
			{
				break;
			}
			
			case SDL_MOUSEWHEEL:
			/**< Mouse wheel motion */
			{
				break;
			}
			
/* Joystick events */
			case SDL_JOYAXISMOTION:
			/**< Joystick axis motion */
			{
				break;
			}
			
			case SDL_JOYBALLMOTION:
			/**< Joystick trackball motion */
			{
				break;
			}
			
			case SDL_JOYHATMOTION:
			/**< Joystick hat position change */
			{
				break;
			}
			
			case SDL_JOYBUTTONDOWN:
			/**< Joystick button pressed */
			{
				break;
			}
			
			case SDL_JOYBUTTONUP:
			/**< Joystick button released */
			{
				break;
			}
			
			case SDL_JOYDEVICEADDED:
			/**< A new joystick has been inserted into the system */
			{
				break;
			}
			
			case SDL_JOYDEVICEREMOVED:
			/**< An opened joystick has been removed */
			{
				break;
			}
			
/* Game controller events */
			case SDL_CONTROLLERAXISMOTION:
			/**< Game controller axis motion */
			{
				break;
			}
			
			case SDL_CONTROLLERBUTTONDOWN:
			/**< Game controller button pressed */
			{
				break;
			}
			
			case SDL_CONTROLLERBUTTONUP:
			/**< Game controller button released */
			{
				break;
			}
			
			case SDL_CONTROLLERDEVICEADDED:
			/**< A new Game controller has been inserted into the system */
			{
				break;
			}
			
			case SDL_CONTROLLERDEVICEREMOVED:
			/**< An opened Game controller has been removed */
			{
				break;
			}
			
			case SDL_CONTROLLERDEVICEREMAPPED:
			/**< The controller mapping was updated */
			{
				break;
			}
			
/* Touch events */
			case SDL_FINGERDOWN:
			{
				break;
			}
			
			case SDL_FINGERUP:
			{
				break;
			}
			
			case SDL_FINGERMOTION:
			{
				break;
			}

/* Gesture events */
			case SDL_DOLLARGESTURE:
			{
				break;
			}
			
			case SDL_DOLLARRECORD:
			{
				break;
			}
			
			case SDL_MULTIGESTURE:
			{
				break;
			}
			
/* Clipboard events */
			case SDL_CLIPBOARDUPDATE:
			/**< The clipboard changed */
			{
				break;
			}

/* Drag and drop events */
			case SDL_DROPFILE:
			/**< The system requests a file open */
			{
				break;
			}

/* Audio hotplug events */
			//case SDL_AUDIODEVICEADDED:
			///**< A new audio device is available */
			//{
			//	break;
			//}
			//
			//case SDL_AUDIODEVICEREMOVED:
			///**< An audio device has been removed. */
			//{
			//	break;
			//}
			
/* Render events */
			case SDL_RENDER_TARGETS_RESET:
			/**< The render targets have been reset and their contents need to be updated */
			{
				break;
			}
			
			//case SDL_RENDER_DEVICE_RESET:
			///**< The device has been reset and all textures need to be recreated */
			//{
			//	break;
			//}
			
/** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
*  and should be allocated with SDL_RegisterEvents() */
			case SDL_USEREVENT:
			{
				break;
			}
   		
/* This last event is only for bounding internal arrays */
			case SDL_LASTEVENT:
			{
				break;
			}
			
			default:
				break;
		}
	}
}

double ProcessHandler::GetCurrentTime()
{
	return SDL_GetTicks();
}