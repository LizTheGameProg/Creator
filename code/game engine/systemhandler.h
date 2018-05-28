#pragma once
#include "handler.h"
namespace GAME_ENGINE
{
	class SystemHandler : public Handler<SystemHandler>
	{
	public:
		SystemHandler();
		~SystemHandler();

		bool OnInitialize();
		void OnDeInitialize();

		bool ShouldExit();
		double GetCurrentTime();
		void ProcessEvents();
		void Flip();
	};
}