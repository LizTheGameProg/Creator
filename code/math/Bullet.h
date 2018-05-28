#pragma once
#include "GameObject.h"

#include "vec2.h"

namespace LML
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual void Update(float deltaTime);
		virtual void Render();
	};
}