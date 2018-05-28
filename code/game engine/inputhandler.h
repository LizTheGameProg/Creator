#pragma once
#include "handler.h"
namespace GAME_ENGINE
{
	class InputHandler : public Handler<InputHandler>
	{
	public:
		InputHandler();
		~InputHandler();

		bool OnInitialize();
		void OnDeInitialize();

	};
}