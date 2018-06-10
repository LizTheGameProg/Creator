#pragma once
#include "GameObject.h"

namespace LML
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Update(float deltaTime);
		virtual void Render();

	protected:
		//Texture * turret;
		//LML::transform2D barrelTransform;
	};
}