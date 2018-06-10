#pragma once
#include "IEntity.h"

class Input;

namespace AI_GAMES
{
	class Player : public IEntity
	{
	public:
		Player();
		virtual ~Player();

		virtual void Update(float deltaTime);

		static Input* input;
	};
}