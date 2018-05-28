#pragma once
#include "GameObject.h"

namespace LML
{
	class Tree : public GameObject
	{
	public:
		Tree();
		~Tree();

		virtual void Update(float deltaTime);
		virtual void Render();
	};
}